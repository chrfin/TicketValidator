using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace TicketServer.DAL
{
    /// <summary>
    /// Defines the type of the card.
    /// </summary>
    public enum CardType
    {
        /// <summary>
        /// A free card (lucky drawings or sponsors)
        /// </summary>
        Free,
        /// <summary>
        /// A normal/paid card.
        /// </summary>
        Normal
    }
}
