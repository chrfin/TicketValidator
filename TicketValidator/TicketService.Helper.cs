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
    public static class TicketServiceExtensions
    {
        /// <summary>
        /// Gets the state of the service.
        /// </summary>
        /// <returns></returns>
        public static ServiceStatus GetServiceState(this TicketService service)
        {
            bool specified;
            ServiceStatus status;
            service.GetCurrentState(out status, out specified);

            return specified ? status : ServiceStatus.Error;
        }

        /// <summary>
        /// Redeems the ticket.
        /// </summary>
        /// <param name="id">The id.</param>
        /// <returns></returns>
        public static RedeemResult RedeemTicket(this TicketService service, int id)
        {
            return service.RedeemTicket(id, true);
        }
    }
}
