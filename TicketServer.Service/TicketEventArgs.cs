using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.DAL;

namespace TicketServer.Service
{
	/// <summary>
	/// EventArgs implementation for ticket events.
	/// </summary>
	public class TicketEventArgs : EventArgs
	{
		/// <summary>
		/// Gets or sets the ticket.
		/// </summary>
		/// <value>
		/// The ticket.
		/// </value>
		public ITicket Ticket { get; set; }

		/// <summary>
		/// Gets or sets the client.
		/// </summary>
		/// <value>
		/// The client.
		/// </value>
		public string Client { get; set; }

		/// <summary>
		/// Initializes a new instance of the <see cref="TicketEventArgs"/> class.
		/// </summary>
		/// <param name="ticket">The ticket.</param>
		/// <param name="client">The client.</param>
		public TicketEventArgs(ITicket ticket, string client = null)
		{
			Ticket = ticket;
			Client = client;
		}
	}
}
