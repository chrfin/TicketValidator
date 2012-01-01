using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TicketServer.DAL
{
	/// <summary>
	/// Interface to represent a ticket data source.
	/// </summary>
	public interface ITicketDataSource
	{
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
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		bool RedeemTicket(int id);
	}
}
