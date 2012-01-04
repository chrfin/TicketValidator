using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.Enums;
using TicketServer.Interfaces.BusinessLayer;

namespace TicketServer.Interfaces.DAL
{
	/// <summary>
	/// Interface to represent a ticket data source.
	/// </summary>
	public interface ITicketDataSource
	{
		/// <summary>
		/// Gets the ticket count.
		/// </summary>
		int TicketCount { get; }
		/// <summary>
		/// Gets the redeemed count.
		/// </summary>
		int RedeemedCount { get; }

		/// <summary>
		/// Adds the ticket to the data source.
		/// </summary>
		/// <param name="ticket">The ticket.</param>
		/// <returns></returns>
		bool AddTicket(ITicket ticket);

		/// <summary>
		/// Gets the ticket by its id.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		ITicket GetTicket(int id);
		/// <summary>
		/// Gets the ticket by its code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		ITicket GetTicket(string code);

		/// <summary>
		/// Gets all the tickets.
		/// </summary>
		IList<ITicket> Tickets { get; }

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		IRedeemResult RedeemTicket(int id);
	}
}
