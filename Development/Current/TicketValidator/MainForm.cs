using System;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;

using TicketValidator.Properties;

using Symbol.Barcode2;
using Symbol.Notification;
using Symbol.WPAN.Bluetooth;
using System.Net.Sockets;
using System.Threading;
using TicketValidator.Common;
using ProtoBuf;

namespace TicketValidator
{
    public partial class mainForm : Form
    {
        Beeper beep;
        Barcode2 scanner;

        TcpClient serverClient;

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

            try
            {
                serverClient = new TcpClient("192.168.0.130", 7880);

                scanner = new Barcode2(Symbol.Barcode2.Devices.SupportedDevices[0]);
                scanner.Config.Reader.ReaderSpecific.LaserSpecific.AimType = AIM_TYPE.AIM_TYPE_TRIGGER;
                scanner.Config.Reader.Set();
                scanner.OnScan += new Barcode2.OnScanHandler(scanner_OnScan);
                scanner.Scan();

                beep = new Beeper(Symbol.Notification.Device.AvailableDevices.First(d => d.ObjectType == NotifyType.BEEPER));
                beep.Duration = 1000;
                beep.Frequency = 6000;
                beep.Volume = 100;
            }
            catch (Exception e) { labelCodeInfo.Text = e.ToString(); }
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
        /// Scanner_s the on scan.
        /// </summary>
        /// <param name="scancollection">The scancollection.</param>
        protected void scanner_OnScan(ScanDataCollection scancollection)
        {
            labelCodeInfo.Invoke((Action)delegate()
            {
                Stream str = serverClient.GetStream();
                byte[] data = System.Text.Encoding.UTF8.GetBytes(scancollection.GetFirst.Text);
                str.Write(data, 0, data.Length);

                while (serverClient.Client.Available <= 0)
                    Thread.Sleep(100);
                Thread.Sleep(100);

                byte[] buffer = new byte[serverClient.Client.Available];
                serverClient.Client.Receive(buffer);

                MemoryStream ms = new MemoryStream(buffer);
                ms.Flush();
                ms.Seek(0, SeekOrigin.Begin);

                Ticket ticket = Serializer.Deserialize<Ticket>(ms);

                labelCodeInfo.Text = "Code: " + ticket.Code + Environment.NewLine + "Name: " + ticket.Name;
            });
            scanner.Scan();
        }

        /// <summary>
        /// Handles the Click event of the buttonClose control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonClose_Click(object sender, EventArgs e)
        {
            Close();
        }
        /// <summary>
        /// Handles the Deactivate event of the mainForm control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void mainForm_Deactivate(object sender, EventArgs e)
        {
            Close();
        }
        /// <summary>
        /// Handles the Closing event of the mainForm control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
        private void mainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            CloseOpenConnections();
        }
        /// <summary>
        /// Handles the Closed event of the mainForm control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void mainForm_Closed(object sender, EventArgs e)
        {
            CloseOpenConnections();
        }
        /// <summary>
        /// Closes the open connections.
        /// </summary>
        public void CloseOpenConnections()
        {
            if (scanner != null)
            {
                scanner.ScanCancel();
                scanner.Dispose();
            }
        }
    }
}