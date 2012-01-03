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

using Symbol.Barcode2;
using Symbol.Notification;
using Symbol.WPAN.Bluetooth;
using TicketValidator.TicketServiceReference;
using System.Net;

namespace TicketValidator
{
    public partial class mainForm : Form
    {
        Beeper beep;
        Barcode2 scanner;

        TicketService service;
        Ticket currentTicket;

        int timeToAutoRedeem;
        Thread autoRedeemThread;

        /// <summary>
        /// Gets the startup path.
        /// </summary>
        public string StartupPath
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
        public mainForm()
        {
            InitializeComponent();

            if (!SelectService())
                return;
            labelCodeInfo.Invoke((Action)delegate() { labelCodeInfo.Text = Resources.ServiceConnected; });

            try
            {
                scanner = new Barcode2(Symbol.Barcode2.Devices.SupportedDevices[0]);
                scanner.Config.Reader.ReaderSpecific.LaserSpecific.AimType = AIM_TYPE.AIM_TYPE_TRIGGER;
                scanner.Config.Reader.Set();
                scanner.OnScan += new Barcode2.OnScanHandler(scanner_OnScan);
                scanner.Scan();

                beep = new Beeper(Symbol.Notification.Device.AvailableDevices.First(d => d.ObjectType == NotifyType.BEEPER));
                beep.Duration = 500;
                beep.Frequency = 3000;
                beep.Volume = 5;
                beep.State = NotifyState.OFF;
            }
            catch (Exception e) { labelCodeInfo.Text = e.ToString(); }
        }

        /// <summary>
        /// Starts the auto redeem timer.
        /// </summary>
        private void StartAutoRedeemTimer()
        {
            timeToAutoRedeem = 5;
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
                bool specified;
                ServiceStatus status;
                service.GetServiceState(out status, out specified);
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
            if (scanner != null)
                scanner.Scan();
        }

        /// <summary>
        /// Handles the Click event of the buttonSelectService control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonSelectService_Click(object sender, EventArgs e) { SelectService(); }

        /// <summary>
        /// Scanner_s the on scan.
        /// </summary>
        /// <param name="scancollection">The scancollection.</param>
        protected void scanner_OnScan(ScanDataCollection scancollection)
        {
            GetTicket(scancollection.GetFirst.Text);

            scanner.Scan();
        }

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
                buttonRedeem.Enabled = true;
                buttonCancel.Enabled = true;
            });

            RequestTicket(code);
            StartAutoRedeemTimer();

            string type = string.Empty;

            switch (currentTicket.Type)
            {
                case CardType.Free:
                    type = Resources.CardType_Free;
                    break;
                case CardType.Normal:
                    type = Resources.CardType_Normal;
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
                labelCodeInfo.Text += currentTicket.Address + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.Zip + " " + currentTicket.City + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.Phone + Environment.NewLine;
                labelCodeInfo.Text += currentTicket.EMail + Environment.NewLine;
                if (currentTicket.IsRedeemed)
                {
                    labelCodeInfo.Text += Resources.Redeemed + ": " + currentTicket.RedeemDate.ToString("T");
                    labelCodeInfo.ForeColor = Color.Red;

                    Beep(BeepType.Error);
                }
            });
        }

        /// <summary>
        /// Beeps the specified type.
        /// </summary>
        /// <param name="type">The type.</param>
        private void Beep(BeepType type)
        {
            Thread beeper = new Thread(new ThreadStart(delegate()
                {
                    switch (type)
                    {
                        case BeepType.TicketRedeemed:
                            beep.Duration = 100;
                            beep.Frequency = 5000;
                            beep.Volume = 3;
                            beep.State = NotifyState.CYCLE;
                            Thread.Sleep(150);
                            beep.State = NotifyState.CYCLE;
                            break;
                        case BeepType.Error:
                            beep.Duration = 500;
                            beep.Frequency = 1000;
                            beep.Volume = 5;
                            beep.State = NotifyState.CYCLE;
                            break;
                        default:
                            beep.Duration = 1000;
                            beep.Frequency = 3000;
                            beep.Volume = 1;
                            beep.State = NotifyState.CYCLE;
                            break;
                    }
                }));
            beeper.IsBackground = true;
            beeper.Start();
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
            autoRedeemThread.Abort();
            if (currentTicket == null)
                return false;

            ResetUI();
            try
            {
                RedeemResult result = service.RedeemTicket(currentTicket.Id);
                currentTicket = null;
                if (result.Type == RedeemResultType.Redeemed)
                {
                    Beep(BeepType.TicketRedeemed);
                    return true;
                }
                else if (result.Type == RedeemResultType.AlreadyRedeemed)
                    labelCodeInfo.Text = Resources.AlreadyRedeemed;
                else
                    labelCodeInfo.Text = result.Error;
            }
            catch (WebException exp)
            {
                MessageBox.Show(Resources.ConnectionLost_Content + exp.Status.ToString(), Resources.ConnectionLost_Title,
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                if (SelectService())
                    return RedeemCurrentTicket();
                
                Close();
            }

            Beep(BeepType.Error);
            return false;
        }

        /// <summary>
        /// Resets the UI.
        /// </summary>
        private void ResetUI()
        {
            buttonRedeem.Invoke((Action)delegate()
            {
                labelCodeInfo.Text = string.Empty;
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
        private void mainForm_Closed(object sender, EventArgs e) { CloseOpenConnections(true); }
        /// <summary>
        /// Closes the open connections.
        /// </summary>
        /// <param name="dispose">if set to <c>true</c> the scanner is disposed.</param>
        public void CloseOpenConnections(bool dispose)
        {
            if (scanner != null)
            {
                if (scanner.IsScanPending)
                    scanner.ScanCancel();
                if (dispose)
                {
                    scanner.Dispose();
                    scanner = null;
                }
            }
        }
    }
}