using System;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;
using System.Threading;
using TicketValidator.Properties;
using TicketValidator.TicketServiceReference;
using System.Net;
using System.Diagnostics;
using TicketValidator.Interfaces;

namespace TicketValidator
{
    public partial class MainForm : Form
    {
        IScanner scanner;

        TicketService service;
        Ticket currentTicket;

        int timeToAutoRedeem;
        Thread autoRedeemThread;

        /// <summary>
        /// Gets the startup path.
        /// </summary>
        public static string StartupPath
        {
            get
            {
                string appPath = Assembly.GetExecutingAssembly().GetName().CodeBase;
                return Path.GetDirectoryName(appPath);
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="mainForm"/> class.
        /// </summary>
        public MainForm(IScanner scanner)
        {
            InitializeComponent();

            if (!SelectService())
                return;
            labelCodeInfo.Invoke((Action)delegate() { labelCodeInfo.Text = Resources.ServiceConnected; });
            
            try
            {
                scanner.Init();
                scanner.OnScan += new EventHandler(scanner_OnScan);
                this.scanner = scanner;
            }
            catch (Exception e) { labelCodeInfo.Text = e.ToString(); }
        }

        /// <summary>
        /// Handles the OnScan event of the scanner control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected void scanner_OnScan(object sender, EventArgs e)
        {
            string code = (e as ScanEventArgs).Code;
            GetTicket(code.Contains("-") ? code : code.Substring(0, code.Length - 1));

            scanner.StartScan();
        }

        /// <summary>
        /// Starts the auto redeem timer.
        /// </summary>
        private void StartAutoRedeemTimer()
        {
            timeToAutoRedeem = 4;
            autoRedeemThread = new Thread(new ThreadStart(delegate()
            {
                while (timeToAutoRedeem > 0)
                {
                    Thread.Sleep(1000);
                    timeToAutoRedeem--;
                    buttonRedeem.Invoke((Action)delegate() { buttonRedeem.Text = string.Format(Resources.RedeemTime, timeToAutoRedeem); });
                }
                Invoke((Action)delegate() { RedeemCurrentTicket(); });
            }));
            autoRedeemThread.IsBackground = true;
            autoRedeemThread.Name = "Auto Redeem Thread";
            autoRedeemThread.Start();
        }

        /// <summary>
        /// Stops the auto redeem timer.
        /// </summary>
        private void StopAutoRedeemTimer()
        {
            if (autoRedeemThread == null)
                return;

            autoRedeemThread.Abort();
            autoRedeemThread = null;
        }

        /// <summary>
        /// Selects the service.
        /// </summary>
        /// <returns></returns>
        private bool SelectService()
        {
            service = new TicketService();

            ServiceSelection selectionForm = new ServiceSelection();
            if (selectionForm.ShowDialog() == DialogResult.OK)
                service.Url = selectionForm.ServiceUri;

            try
            {
                ServiceStatus status = service.GetServiceState();
                if (status != ServiceStatus.Running)
                    MessageBox.Show(Resources.InitialConnectionFaild_Content, Resources.InitialConnectionFaild_Title,
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
            }
            catch (WebException exp)
            {
                labelCodeInfo.Invoke((Action)delegate()
                {
                    switch (exp.Status)
                    {
                        case WebExceptionStatus.ConnectFailure:
                        case WebExceptionStatus.ConnectionClosed:
                            labelCodeInfo.Text = Resources.ConnectionError_Failed;
                            break;
                        case WebExceptionStatus.Timeout:
                            labelCodeInfo.Text = Resources.ConnectionError_Timeout;
                            break;
                        default:
                            labelCodeInfo.Text = Resources.ConnectionError_Unknown + exp.Status.ToString();
                            break;
                    }
                });

                return false;
            }

            return true;
        }

        /// <summary>
        /// Handles the Activated event of the mainForm control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void mainForm_Activated(object sender, EventArgs e)
        {
            scanner.StartScan();
        }

        /// <summary>
        /// Handles the Click event of the buttonSelectService control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonSelectService_Click(object sender, EventArgs e) { SelectService(); }

        /// <summary>
        /// Gets the ticket and shows the received information.
        /// </summary>
        /// <param name="code">The code.</param>
        private void GetTicket(string code)
        {
            if (currentTicket != null)
            {
                if (!RedeemCurrentTicket())
                    return;
            }

            labelCodeInfo.Invoke((Action)delegate()
            {
                labelCodeInfo.Text = Resources.Code + ": " + code + Environment.NewLine;
            });

            RequestTicket(code);

            if (currentTicket == null)
            {
                scanner.Beep(BeepType.Error);
                labelCodeInfo.Invoke((Action)delegate()
                {
                    labelCodeInfo.Text = Resources.TicketNotFound;
                    labelCodeInfo.ForeColor = Color.Red;
                    buttonCancel.Enabled = true;
                });
                return;
            }

            string type = string.Empty;

            switch (currentTicket.Type)
            {
                case TicketType.Free:
                    type = Resources.CardType_Free;
                    break;
                case TicketType.Normal:
                    type = Resources.CardType_Normal;
                    break;
                case TicketType.Special:
                    type = Resources.CardType_Special;
                    break;
                default:
                    type = Resources.CardType_Unknown;
                    break;
            }

            type += " " + (currentTicket.IsOnlineTicket ? Resources.CardVersion_Online : Resources.CardVersion_Offline);

            labelCodeInfo.Invoke((Action)delegate()
            {
                labelCodeInfo.Text += Resources.Type + ": " + type + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.Name + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.Street + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.Zip + " " + currentTicket.City + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.Phone + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.EMail + Environment.NewLine;
                buttonCancel.Enabled = true;
                if (currentTicket.IsRedeemed)
                {
                    labelCodeInfo.Text += Resources.Redeemed + ": " + currentTicket.RedeemDate.Value.ToString("T");
                    labelCodeInfo.ForeColor = Color.Red;

                    scanner.Beep(BeepType.Error);
                }
                else if (currentTicket.Type == TicketType.Special)
                {
                    buttonRedeem.Enabled = true;
                    scanner.Beep(BeepType.Attention);
                }
                else
                {
                    buttonRedeem.Enabled = true;
                    StartAutoRedeemTimer();
                }
            });
        }

        /// <summary>
        /// Gets the ticket from the ticket service.
        /// </summary>
        /// <param name="code">The code.</param>
        private void RequestTicket(string code)
        {
            try
            {
                currentTicket = service.GetTicket(code);
            }
            catch (WebException exp)
            {
                MessageBox.Show(Resources.ConnectionLost_Content + exp.Status.ToString(), Resources.ConnectionLost_Title,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                if (SelectService())
                    RequestTicket(code);
                else
                    Close();
            }
        }

        /// <summary>
        /// Redeems the current ticket.
        /// </summary>
        private bool RedeemCurrentTicket()
        {
            StopAutoRedeemTimer();
            if (currentTicket == null)
                return false;

            ResetUI();

            if (currentTicket.IsRedeemed)
            {
                currentTicket = null;
                return true;
            }
            try
            {
                RedeemResult result = service.RedeemTicket(currentTicket.Id);
                currentTicket = null;
                if (result.Type == RedeemResultType.Redeemed)
                {
                    scanner.Beep(BeepType.TicketRedeemed);
                    return true;
                }
                else if (result.Type == RedeemResultType.AlreadyRedeemed)
                    labelCodeInfo.Invoke((Action)delegate() { labelCodeInfo.Text = Resources.AlreadyRedeemed; });
                else
                    labelCodeInfo.Invoke((Action)delegate() { labelCodeInfo.Text = result.Error; });
            }
            catch (WebException exp)
            {
                MessageBox.Show(Resources.ConnectionLost_Content + exp.Status.ToString(), Resources.ConnectionLost_Title,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                if (SelectService())
                    return RedeemCurrentTicket();

                Close();
            }

            scanner.Beep(BeepType.Error);
            return false;
        }

        /// <summary>
        /// Resets the UI.
        /// </summary>
        private void ResetUI()
        {
            buttonRedeem.Invoke((Action)delegate()
            {
                labelCodeInfo.Text = Resources.ServiceConnected;
                labelCodeInfo.ForeColor = Color.Black;
                buttonRedeem.Text = Resources.Redeem;
                buttonRedeem.Enabled = false;
                buttonCancel.Enabled = false;
            });
        }

        /// <summary>
        /// Handles the Click event of the buttonRedeem control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonRedeem_Click(object sender, EventArgs e) { RedeemCurrentTicket(); }

        /// <summary>
        /// Handles the Click event of the buttonCancel control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonCancel_Click(object sender, EventArgs e)
        {
            StopAutoRedeemTimer();
            currentTicket = null;
            ResetUI();
        }

        /// <summary>
        /// Handles the Click event of the buttonClose control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonClose_Click(object sender, EventArgs e) { Close(); }
        /// <summary>
        /// Handles the Deactivate event of the mainForm control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void mainForm_Deactivate(object sender, EventArgs e) { CloseOpenConnections(false); }
        /// <summary>
        /// Handles the Closing event of the mainForm control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
        private void mainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e) { CloseOpenConnections(true); }
        /// <summary>
        /// Handles the Closed event of the mainForm control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void mainForm_Closed(object sender, EventArgs e) { CloseOpenConnections(true); Process.GetCurrentProcess().Kill(); }
        /// <summary>
        /// Closes the open connections.
        /// </summary>
        /// <param name="dispose">if set to <c>true</c> the scanner is disposed.</param>
        public void CloseOpenConnections(bool dispose)
        {
            if (scanner != null)
            {
                scanner.StopScan(dispose);
            }
        }
    }
}