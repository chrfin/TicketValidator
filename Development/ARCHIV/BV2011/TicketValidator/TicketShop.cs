using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Data.SqlServerCe;

namespace TicketValidator
{
    public class TicketShop
    {
        /// <summary>
        /// Gets the db connection.
        /// </summary>
        /// <value>The db connection.</value>
        internal SqlCeConnection DbConnection { get; private set; }
        internal string Filename { get; set; }

        public int SoldCount
        {
            get
            {
                SqlCeCommand cmd = DbConnection.CreateCommand();
                cmd.CommandText = "SELECT COUNT(card_id) FROM cards WHERE card_redeemed = 0";
                return SqlCE.ExecuteScalar<int>(cmd).Value;
            }
        }
        public int RedeemedCount
        {
            get
            {
                SqlCeCommand cmd = DbConnection.CreateCommand();
                cmd.CommandText = "SELECT COUNT(card_id) FROM cards WHERE card_redeemed = 1";
                return SqlCE.ExecuteScalar<int>(cmd).Value;
            }
        }

        public TicketShop(string filename)
        {
            if (!File.Exists(filename))
                filename = SqlCE.CreateNewDB(filename, false);

            Filename = filename;
            DbConnection = new SqlCeConnection(SqlCE.GetConnectionString(filename));
            DbConnection.Open();
        }

        public CardStatus CheckCardStatus(Card card)
        {
            if (card == null)
                return CardStatus.UNKNOWN;
            return CheckCardStatus(card.Code); 
        }
        public CardStatus CheckCardStatus(string code)
        {
            SqlCeCommand cmd = DbConnection.CreateCommand();
            cmd.CommandText = "SELECT card_redeemed FROM cards WHERE card_code = @code";
            cmd.Parameters.Add("code", code);
            SqlCeDataReader reader = SqlCE.ExecuteReader(cmd);

            try
            {
                while (reader.Read())
                {
                    if (Convert.ToBoolean(reader["card_redeemed"]))
                        return CardStatus.Redeemed;
                    return CardStatus.Sold;
                }

                return CardStatus.UNKNOWN;
            }
            finally
            {
                reader.Close();
            }
        }

        public CardAddResult AddCard(Card card)
        {
            if (card == null)
                return CardAddResult.ERROR;

            CardStatus status = CheckCardStatus(card);
            if (status == CardStatus.Sold)
                return CardAddResult.AlreadyInSold;
            if (status == CardStatus.Redeemed)
                return CardAddResult.AlreadyRedeemed;

            SqlCeCommand cmd = DbConnection.CreateCommand();
            cmd.CommandText = "INSERT INTO cards (card_id, card_code, card_name, card_address, card_zip, card_city, card_phone, card_mail, card_redeemed) " +
                "VALUES(@id, @code, @name, @address, @zip, @city, @phone, @mail, @redeemed)";
            cmd.Parameters.Add("id", card.Id);
            cmd.Parameters.Add("code", card.Code);
            cmd.Parameters.Add("name", card.Name);
            cmd.Parameters.Add("address", card.Address);
            cmd.Parameters.Add("zip", card.Zip);
            cmd.Parameters.Add("city", card.City);
            cmd.Parameters.Add("phone", card.Phone);
            cmd.Parameters.Add("mail", card.EMail);
            cmd.Parameters.Add("redeemed", false);
            SqlCE.ExecuteNonQuery(cmd);

            return CardAddResult.Added;
        }
        public bool RedeemCard(Card card)
        {
            CardStatus status = CheckCardStatus(card);
            if (status != CardStatus.Sold)
                return false;

            card.Redeemed = true;
            card.RedeemDate = DateTime.Now;

            SqlCeCommand cmd = DbConnection.CreateCommand();
            cmd.CommandText = "UPDATE cards SET card_redeemed = @redeemed, card_redeem_date = @date WHERE card_id=@id";
            cmd.Parameters.Add("id", card.Id);
            cmd.Parameters.Add("redeemed", card.Redeemed);
            cmd.Parameters.Add("date", card.RedeemDate);
            SqlCE.ExecuteNonQuery(cmd);

            return true;
        }

        public Card GetCard(int id) { return new Card(id, this); }
        public Card GetCard(string code)
        {
            SqlCeCommand cmd = DbConnection.CreateCommand();
            cmd.CommandText = "SELECT card_id FROM cards WHERE card_code = @code";
            cmd.Parameters.Add("code", code);
            return new Card(SqlCE.ExecuteScalar<int>(cmd).Value, this);
        }

        public void Reset()
        {
            CreateBackup();

            SqlCeCommand cmd = DbConnection.CreateCommand();
            cmd.CommandText = "UPDATE cards SET card_redeemed = @redeemed";
            cmd.Parameters.Add("redeemed", false);
            SqlCE.ExecuteNonQuery(cmd);
        }
        public void Clear()
        {
            CreateBackup();

            SqlCeCommand cmd = DbConnection.CreateCommand();
            cmd.CommandText = "DELETE FROM cards";
            SqlCE.ExecuteNonQuery(cmd);
        }
        public void CreateBackup()
        {
            DbConnection.Close();
            File.Copy(Filename, Filename.Replace(".tickets", "_" + DateTime.Now.ToString("yyyyMddHHmm") + ".tickets"), true);
            DbConnection.Open();
        }

        public List<BasicCard> GetCardsList()
        {
            List<BasicCard> cards = new List<BasicCard>();
            SqlCeCommand cmd = DbConnection.CreateCommand();
            cmd.CommandText = "SELECT card_id, card_name, card_redeemed FROM cards ORDER BY card_id ASC";
            SqlCeDataReader reader = SqlCE.ExecuteReader(cmd);
            while (reader.Read())
            {
                cards.Add(new BasicCard()
                {
                    Id = Convert.ToInt32(reader["card_id"]),
                    Name = reader["card_name"].ToString(),
                    Redeemed = Convert.ToBoolean(reader["card_redeemed"])
                });
            }
            reader.Close();

            return cards;
        }
    }

    public struct BasicCard
    {
        public int Id;
        public string Name;
        public bool Redeemed;

        public override string ToString()
        {
            return (Redeemed ? "√ " : "") + string.Format("{0} - {1}", Id, Name);
        }
    }

    public enum CardAddResult
    {
        Added,
        AlreadyInSold,
        AlreadyRedeemed,
        ERROR
    }

    public enum CardStatus
    {
        Sold,
        Redeemed,
        UNKNOWN
    }
}
