using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace TicketService
{
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single, UseSynchronizationContext=false)]
	public class TicketService : ITicketService
	{
		#region ITicketService Members

		/// <summary>
		/// Gets the ticket with the specific code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		public Ticket GetTicket(string code)
		{
			Ticket ticket = new Ticket();
			ticket.Code = code;
			ticket.IsOnlineTicket = true;
			ticket.Name = "TESTER TEST";
			ticket.Address = "Testergasse 12";
			ticket.Zip = "1234";
			ticket.City = "Testingen";
			ticket.Phone = "+43/1234/567890";
			ticket.EMail = "tester@butzvarruckt.at";

			return ticket;
		}

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public bool RedeemTicket(int id)
		{
			return false;
		}

		#endregion
	}
}
