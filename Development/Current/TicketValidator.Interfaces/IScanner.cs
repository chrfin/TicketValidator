using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TicketValidator.Interfaces
{
    /// <summary>
    /// A scanner.
    /// </summary>
    public interface IScanner : IDisposable
    {
        /// <summary>
        /// Inits this scanner.
        /// </summary>
        void Init();

        /// <summary>
        /// Starts the scan.
        /// </summary>
        void StartScan();
        /// <summary>
        /// Stops the scan.
        /// </summary>
        /// <param name="dispose">if set to <c>true</c> disposes the scanner.</param>
        void StopScan(bool dispose);

        /// <summary>
        /// Occures when a scna was successfull.
        /// </summary>
        event EventHandler OnScan;

        /// <summary>
        /// Beeps the specified type.
        /// </summary>
        /// <param name="type">The type.</param>
        void Beep(BeepType type);
    }
}
