using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlServerCe;

namespace TicketValidator
{
    public class Card
    {
        public int Id { get; set; }
        public string Code { get; set; }
        public string Name { get; set; }
        public string Address { get; set; }
        public string Zip { get; set; }
        public string City { get; set; }
        public string Phone { get; set; }
        public string EMail { get; set; }
        public bool Redeemed { get; set; }
        public DateTime RedeemDate { get; set; }

        public Card() { Id = -1; }
        public Card(int id, TicketShop shop)
        {
            SqlCeCommand cmd = shop.DbConnection.CreateCommand();
            cmd.CommandText = "SELECT * FROM cards WHERE card_id=@id";
            cmd.Parameters.Add("id", id);
            SqlCeDataReader reader = SqlCE.ExecuteReader(cmd);

            while (reader.Read())
            {
                Dictionary<string, object> columns = new Dictionary<string, object>();
                for (int i = 0; i < reader.FieldCount; i++)
                    columns.Add(reader.GetName(i), reader[i]);
                Id = Convert.ToInt32(columns["card_id"]);
                Code = columns["card_code"].ToString();
                Name = columns["card_name"].ToString();
                Address = columns["card_address"].ToString();
                Zip = columns["card_zip"].ToString();
                City = columns["card_city"].ToString();
                Phone = columns["card_phone"].ToString();
                EMail = columns["card_mail"].ToString();
                Redeemed = Convert.ToBoolean(columns["card_redeemed"]);
                if (Redeemed)
                    RedeemDate = Convert.ToDateTime(columns["card_redeem_date"]);
            }
            reader.Close();
        }
        public Card(string[] row)
        {
            Code = row[1];
            Name = row[5];
            Address = row[6];
            Zip = row[9];
            City = row[10];
            Phone = row[11];
            EMail = row[12];

            Id = Convert.ToInt32(Code.Substring(7));
        }

        public override bool Equals(object obj)
        {
            return (obj is Card && (obj as Card).Id == this.Id) || (obj is string && ((string)obj) == this.Code);
        }
        public override int GetHashCode()
        {
            return Convert.ToInt32(Code);
        }
    }
}
