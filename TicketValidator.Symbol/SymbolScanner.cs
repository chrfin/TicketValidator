using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using TicketValidator.Interfaces;
using Symbol.Barcode2;
using Symbol.Notification;
using System.Threading;

namespace TicketValidator.SymbolScanner
{
    class SymbolScanner : IScanner
    {
        Beeper beep;
        Barcode2 scanner;

        #region IScanner Members

        public event EventHandler OnScan;

        /// <summary>
        /// Inits this scanner.
        /// </summary>
        public void Init()
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

        /// <summary>
        /// Handles the on scan event.
        /// </summary>
        /// <param name="scancollection">The scancollection.</param>
        void scanner_OnScan(ScanDataCollection scancollection)
        {
            if (OnScan != null)
                OnScan(this, new ScanEventArgs() { Code = scancollection.GetFirst.Text });
        }

        /// <summary>
        /// Starts the scan.
        /// </summary>
        public void StartScan()
        {
            if (scanner != null && !scanner.IsScanPending)
                scanner.Scan();
        }
        /// <summary>
        /// Stops the scan.
        /// </summary>
        /// <param name="dispose">if set to <c>true</c> disposes the scanner.</param>
        public void StopScan(bool dispose)
        {
            if (scanner != null)
            {
                if (scanner.IsScanPending)
                    scanner.ScanCancel();
                if (dispose)
                    Dispose();
            }
        }

        /// <summary>
        /// Beeps the specified type.
        /// </summary>
        /// <param name="type">The type.</param>
        public void Beep(BeepType type)
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
                    case BeepType.Attention:
                        beep.Duration = 50;
                        beep.Frequency = 7500;
                        beep.Volume = 5;
                        for (int i = 0; i < 10; ++i)
                        {
                            beep.State = NotifyState.CYCLE;
                            Thread.Sleep(75);
                        }
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

        #endregion

        #region IDisposable Members

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (scanner != null)
            {
                if (scanner.IsScanPending)
                    scanner.ScanCancel();

                scanner.Dispose();
                scanner = null;
            }
        }

        #endregion
    }
}
