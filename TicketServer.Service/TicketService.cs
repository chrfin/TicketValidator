using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TicketServer.DAL;

namespace TicketServer.Service
{
	/// <summary>
	/// The ticket service.
	/// </summary>
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single, UseSynchronizationContext=false)]
	public class TicketService : ITicketService
	{
		/// <summary>
		/// Gets or sets the ticket source.
		/// </summary>
		/// <value>
		/// The ticket source.
		/// </value>
		public ITicketDataSource TicketSource { get; set; }

		/// <summary>
		/// Occurs when a ticket is requested.
		/// </summary>
		public event EventHandler TicketRequested;
		/// <summary>
		/// Raises the <see cref="E:TicketRequested"/> event.
		/// </summary>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		protected virtual void OnTicketRequested(EventArgs e)
		{
			if (TicketRequested != null)
				TicketRequested(this, e);
		}

		/// <summary>
		/// Occurs when a ticket is redeemed.
		/// </summary>
		public event EventHandler TicketRedeemed;
		/// <summary>
		/// Raises the <see cref="E:TicketRedeeemed"/> event.
		/// </summary>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		protected virtual void OnTicketRedeeemed(EventArgs e)
		{
			if (TicketRedeemed != null)
				TicketRedeemed(this, e);
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="TicketService"/> class.
		/// </summary>
		/// <param name="ticketSource">The ticket source.</param>
		public TicketService(ITicketDataSource ticketSource)
		{
			TicketSource = ticketSource;
		}

		#region ITicketService Members

		/// <summary>
		/// Gets the ticket with the specific code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		public Ticket GetTicket(string code)
		{
			Ticket ticket = new Ticket(TicketSource.GetTicket(code));

			OperationContext context = OperationContext.Current;
			MessageProperties prop = context.IncomingMessageProperties;
			RemoteEndpointMessageProperty endpoint = prop[RemoteEndpointMessageProperty.Name] as RemoteEndpointMessageProperty;

			OnTicketRequested(new TicketEventArgs(ticket, endpoint.Address));

			return ticket;
		}

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public bool RedeemTicket(int id)
		{
			return TicketSource.RedeemTicket(id);
		}

		#endregion
	}
}
