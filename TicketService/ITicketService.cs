using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace TicketService
{
	[ServiceContract]
	public interface ITicketService
	{
		/// <summary>
		/// Gets the ticket with the specific code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		[OperationContract]
		Ticket GetTicket(string code);

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		[OperationContract]
		bool RedeemTicket(int id);
	}
}
