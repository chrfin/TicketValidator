using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using TicketValidator.Interfaces;
using DNWA.BHTCL;
using System.Threading;

namespace TicketValidator.Denso
{
    class DensoScanner : IScanner
    {
        Beep beeper;
        Scanner scanner;

        #region IScanner Members

        /// <summary>
        /// Inits this scanner.
        /// </summary>
        public void Init()
        {
            scanner = new Scanner();
            scanner.RdMode = "MB"; // M = Momentary switching mode -> On Code a time; B = Beeper -> beep after successful read
            scanner.RdType = "A,M"; // A = UPC; M = Code-39
            scanner.OnDone += new EventHandler(scanner_OnDone);
            scanner.PortOpen = true;

            beeper = new Beep();
        }

        /// <summary>
        /// Handles the OnDone event of the scanner control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected void scanner_OnDone(object sender, EventArgs e)
        {
            if (OnScan != null)
                OnScan(this, new ScanEventArgs() { Code = scanner.Input(Scanner.ALL_BUFFER) });
        }

        /// <summary>
        /// Starts the scan.
        /// </summary>
        public void StartScan()
        {
            if (scanner != null && !scanner.PortOpen)
                scanner.PortOpen = true;
        }
        /// <summary>
        /// Stops the scan.
        /// </summary>
        /// <param name="dispose">if set to <c>true</c> disposes the scanner.</param>
        public void StopScan(bool dispose)
        {
            if (scanner != null)
            {
                if (scanner.PortOpen)
                    scanner.PortOpen = false;
            }
            if (dispose)
                Dispose();
        }

        /// <summary>
        /// Occures when a scan was successfull.
        /// </summary>
        public event EventHandler OnScan;

        /// <summary>
        /// Beeps the specified type.
        /// </summary>
        /// <param name="type">The type.</param>
        public void Beep(BeepType type)
        {
            Thread beeperThread = new Thread(new ThreadStart(delegate()
            {
                switch (type)
                {
                    case BeepType.TicketRedeemed:
                        beeper.OnTime = 1;
                        beeper.OffTime = 2;
                        beeper.Count = 2;
                        beeper.Frequency = 1;
                        DNWA.BHTCL.Beep.Settings.Volume = DNWA.BHTCL.Beep.Settings.EN_VOLUME.LEVEL3;
                        beeper[DNWA.BHTCL.Beep.Settings.EN_DEVICE.BUZZER] = DNWA.BHTCL.Beep.EN_CTRL.ON;
                        break;
                    case BeepType.Error:
                        beeper.OnTime = 5;
                        beeper.OffTime = 5;
                        beeper.Count = 1;
                        beeper.Frequency = 0;
                        DNWA.BHTCL.Beep.Settings.Volume = DNWA.BHTCL.Beep.Settings.EN_VOLUME.LEVEL5;
                        beeper[DNWA.BHTCL.Beep.Settings.EN_DEVICE.BUZZER] = DNWA.BHTCL.Beep.EN_CTRL.ON;
                        break;
                    case BeepType.Attention:
                        beeper.OnTime = 1;
                        beeper.OffTime = 1;
                        beeper.Count = 10;
                        beeper.Frequency = 2;
                        DNWA.BHTCL.Beep.Settings.Volume = DNWA.BHTCL.Beep.Settings.EN_VOLUME.LEVEL5;
                        beeper[DNWA.BHTCL.Beep.Settings.EN_DEVICE.BUZZER] = DNWA.BHTCL.Beep.EN_CTRL.ON;
                        break;
                    default:
                        beeper.OnTime = 10;
                        beeper.Count = 1;
                        beeper.Frequency = 1;
                        DNWA.BHTCL.Beep.Settings.Volume = DNWA.BHTCL.Beep.Settings.EN_VOLUME.LEVEL1;
                        beeper[DNWA.BHTCL.Beep.Settings.EN_DEVICE.BUZZER] = DNWA.BHTCL.Beep.EN_CTRL.ON;
                        break;
                }
            }));
            beeperThread.IsBackground = true;
            beeperThread.Start();
        }

        #endregion

        #region IDisposable Members

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (scanner != null)
            {
                if (scanner.PortOpen)
                    scanner.PortOpen = false;

                scanner.Dispose();
                scanner = null;
            }
        }

        #endregion
    }
}
