using System;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DNWA.BHTCL;
using System.IO;
using TicketValidator.Properties;
using System.Reflection;

namespace TicketValidator
{
    public partial class mainForm : Form
    {
        Beep beep;
        Scanner scanner;
        TicketShop ticketShop;

        Card currentCard = null;
        Timer autoRedeemTimer;

        public string StartupPath
        {
            get
            {
                string appPath = Assembly.GetExecutingAssembly().GetName().CodeBase;
                return Path.GetDirectoryName(appPath);
            }
        }

        public mainForm()
        {
            InitializeComponent();

            ticketShop = new TicketShop(Path.Combine(StartupPath, "ticketShop.tickets"));
            UpdateLists();

            autoRedeemTimer = new Timer();
            autoRedeemTimer.Interval = 1000;
            autoRedeemTimer.Tick += new EventHandler(autoRedeemTimer_Tick);

            try
            {
                scanner = new Scanner();
                scanner.RdMode = "MB";
                scanner.RdType = "A";
                scanner.OnDone += new EventHandler(scanner_OnDone);
                scanner.PortOpen = true;

                beep = new Beep();
                beep.OnTime = 1;
                beep.OffTime = 1;
            }
            catch (Exception e) { labelCodeInfo.Text = e.ToString(); }
        }

        void scanner_OnDone(object sender, EventArgs e)
        {
            HandleCodeInput(scanner.Input(Scanner.ALL_BUFFER));
        }

        private void buttonImport_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                Card cCard;
                int cardsAdded = 0;
                int cardsAlreadyInSold = 0;
                int cardsAlreadyRedeemed = 0;
                string cardsPath = ofd.FileName;
                StreamReader reader = File.OpenText(cardsPath);
                string header = reader.ReadLine();
                while (!reader.EndOfStream)
                {
                    string line = reader.ReadLine();
                    string[] items = line.Split(';');
                    if (items.Length > 1)
                    {
                        cCard = new Card(items);
                        CardAddResult result = ticketShop.AddCard(cCard);
                        if (result == CardAddResult.AlreadyInSold)
                            cardsAlreadyInSold++;
                        else if (result == CardAddResult.AlreadyRedeemed)
                            cardsAlreadyRedeemed++;
                        else
                            cardsAdded++;

                        buttonImport.Text = string.Format("{0} Karten", (cardsAdded + cardsAlreadyInSold + cardsAlreadyRedeemed));
                        Application.DoEvents();
                    }
                }
                reader.Close();

                buttonImport.Text = "Lade CSV";

                MessageBox.Show(string.Format("{0} Karten hinzugefügt.\n{1} Karten bereits vorhanden.\n{2} Karten bereits eingelöst.",
                    cardsAdded, cardsAlreadyInSold, cardsAlreadyRedeemed), "Karten importiert",
                    MessageBoxButtons.OK, MessageBoxIcon.None, MessageBoxDefaultButton.Button1);

                if (cardsAdded > 0)
                    UpdateLists();
            }
        }
        
        private void tabControlMain_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateLists();
        }
        private void UpdateLists()
        {
            if (tabControlMain.SelectedIndex != 1)
                return;

            labelOpen.Text = string.Format("Offen: {0} Karten", ticketShop.SoldCount);
            labelRedeemed.Text = string.Format("Eingelöst: {0} Karten", ticketShop.RedeemedCount);

            listBoxCards.BeginUpdate();

            listBoxCards.Items.Clear();
            ticketShop.GetCardsList().ForEach(c => listBoxCards.Items.Add(c));

            listBoxCards.EndUpdate();
        }

        private void listBoxCards_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBoxCards.SelectedItem is BasicCard)
            {
                MessageBox.Show(GetInfoText(ticketShop.GetCard(((BasicCard)listBoxCards.SelectedItem).Id)), "Details",
                    MessageBoxButtons.OK, MessageBoxIcon.None, MessageBoxDefaultButton.Button1);
            }
        }
        private string GetInfoText(Card card)
        {
            return string.Format("Karten-Nr.: {0}\n{1}\n{2}\n{3} {4}\n{5}\n{6}", card.Id, card.Name, card.Address, card.Zip,
                card.City, card.Phone, card.EMail) + (card.Redeemed ? string.Format("\nEngelöst: {0}", card.RedeemDate.ToString("dd.M. HH:mm")) : "");
        }

        private void HandleCodeInput(string code)
        {
            if (currentCard != null)
                RedeemCard();

            string realCode = code.StartsWith("000") ? code.Substring(3, code.Length - 4) : code.Substring(2, code.Length - 3);

            CardStatus status = ticketShop.CheckCardStatus(realCode);
            if (status == CardStatus.Sold)
            {
                currentCard = ticketShop.GetCard(realCode);
                labelCodeInfo.Text = GetInfoText(currentCard);
                labelCodeInfo.ForeColor = Color.Black;
                buttonRedeem.Enabled = true;
                buttonCancel.Enabled = true;

                timeToAutoRedeem = 5;
                autoRedeemTimer.Enabled = true;

                buttonCancel.Focus();
            }
            else if (status == CardStatus.Redeemed)
            {
                labelCodeInfo.Text = "BEREITS EINGELÖST!\n" + GetInfoText(ticketShop.GetCard(realCode));
                labelCodeInfo.ForeColor = Color.Red;

                beep.Count = 1;
                beep.Frequency = 0;
                beep[Beep.Settings.EN_DEVICE.BUZZER] = Beep.EN_CTRL.ON;
            }
            else
            {
                labelCodeInfo.Text = "UNBEKANNTER CODE";
                labelCodeInfo.ForeColor = Color.Red;

                beep.Count = 3;
                beep.Frequency = 0;
                beep[Beep.Settings.EN_DEVICE.BUZZER] = Beep.EN_CTRL.ON;
            }
        }

        int timeToAutoRedeem;
        void autoRedeemTimer_Tick(object sender, EventArgs e)
        {
            timeToAutoRedeem--;
            buttonRedeem.Text = string.Format("EINLÖSEN ({0})", timeToAutoRedeem);

            if (timeToAutoRedeem <= 0)
            {
                RedeemCard();
                beep.Count = 3;
                beep.Frequency = 2;
                beep[Beep.Settings.EN_DEVICE.BUZZER] = Beep.EN_CTRL.ON;

                GC.Collect();
            }
        }
        private void buttonRedeem_Click(object sender, EventArgs e)
        {
            RedeemCard();
        }
        private void buttonCancel_Click(object sender, EventArgs e)
        {
            if (currentCard == null && labelCodeInfo.Text.Length == 0 && scanner == null)
                HandleCodeInput("0056472621830");
            else
                CancelCard();
        }
        private void RedeemCard()
        {
            autoRedeemTimer.Enabled = false;

            if (ticketShop.RedeemCard(currentCard))
            {
                UpdateLists();
            }

            currentCard = null;

            labelCodeInfo.Text = string.Empty;
            buttonRedeem.Text = "EINLÖSEN";
            buttonRedeem.Enabled = false;
            if (scanner != null)
                buttonCancel.Enabled = false;
        }
        private void CancelCard()
        {
            currentCard = null;
            autoRedeemTimer.Enabled = false;
            labelCodeInfo.Text = string.Empty;
            buttonRedeem.Text = "EINLÖSEN";
            buttonRedeem.Enabled = false;
            if (scanner != null)
                buttonCancel.Enabled = false;
        }

        private void buttonResetRedeemed_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Sollen wirklich ALLE Karten von der Eingelöst-Liste gelöscht werden?", "Karten zurücksetzen?",
                 MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button3) == DialogResult.Yes)
            {
                ticketShop.Reset();
                UpdateLists();
            }
        }
        private void buttonClear_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Sollen wirklich ALLE Karten gelöscht werden?", "Karten löschen?",
                 MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button3) == DialogResult.Yes)
            {
                ticketShop.Clear();
                UpdateLists();
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Close();
        }
        private void mainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            CloseOpenConnections();
        }
        private void mainForm_Closed(object sender, EventArgs e)
        {
            CloseOpenConnections();
        }
        private void CloseOpenConnections()
        {

            if (scanner != null)
            {
                if (scanner.PortOpen)
                {
                    scanner.PortOpen = false;
                    scanner.Dispose();
                }
            }
            ticketShop.DbConnection.Close();
            ticketShop.DbConnection.Dispose();
        }
    }
}