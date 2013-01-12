using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace TicketValidator.Interfaces
{
    /// <summary>
    /// A scanner event argument.
    /// </summary>
    public class ScanEventArgs : EventArgs
    {
        /// <summary>
        /// Gets or sets the code.
        /// </summary>
        /// <value>
        /// The code.
        /// </value>
        public string Code { get; set; }
    }
}
