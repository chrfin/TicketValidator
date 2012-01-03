using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using TicketValidator.TicketServiceReference;

namespace TicketValidator.TicketServiceReference
{
    /// <summary>
    /// This implements a few helper for easier access.
    /// </summary>
    partial class TicketService
    {
        /// <summary>
        /// Gets the state of the service.
        /// </summary>
        /// <returns></returns>
        public ServiceStatus GetServiceState()
        {
            bool specified;
            ServiceStatus status;
            GetServiceState(out status, out specified);

            return specified ? status : ServiceStatus.Error;
        }

        /// <summary>
        /// Redeems the ticket.
        /// </summary>
        /// <param name="id">The id.</param>
        /// <returns></returns>
        public RedeemResult RedeemTicket(int id)
        {
            return RedeemTicket(id, true);
        }
    }
}
