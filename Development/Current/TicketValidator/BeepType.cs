using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace TicketValidator
{
    /// <summary>
    /// Different types of predefined beeps.
    /// </summary>
    public enum BeepType
    {
        /// <summary>
        /// The beep signal for a successfully redeemed ticket.
        /// </summary>
        TicketRedeemed,
        /// <summary>
        /// The beep signal fo any error (e.g. ticket already redeemed).
        /// </summary>
        Error,
        /// <summary>
        /// The beep signal if the user needs to check the display.
        /// </summary>
        Attention
    }
}
