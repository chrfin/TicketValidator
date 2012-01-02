using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using TicketServer.Interfaces.Enums;

namespace TicketServer.Service
{
	[ServiceContract]
	public interface ITicketService
	{
		/// <summary>
		/// Gets the state of the service.
		/// </summary>
		/// <returns></returns>
		[OperationContract]
		ServiceStatus GetServiceState();

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
		RedeemResult RedeemTicket(int id);
	}
}
