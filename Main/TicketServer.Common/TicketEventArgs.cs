using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces;
using TicketServer.Interfaces.DAL;
using TicketServer.Interfaces.BusinessLayer;
using System.ComponentModel;

namespace TicketServer.Common
{
	/// <summary>
	/// EventArgs implementation for ticket events.
	/// </summary>
	public class TicketEventArgs : EventArgs, INotifyPropertyChanged
	{
		/// <summary>
		/// Gets or sets the ticked id.
		/// </summary>
		/// <value>
		/// The ticked id.
		/// </value>
		protected int TicketId { get; set; }
		/// <summary>
		/// Gets or sets the ticket source.
		/// </summary>
		/// <value>
		/// The ticket source.
		/// </value>
		protected ITicketDataSource TicketSource { get; set; }

		ITicket ticket;
		/// <summary>
		/// Gets or sets the ticket.
		/// </summary>
		/// <value>
		/// The ticket.
		/// </value>
		public ITicket Ticket 
		{
			get
			{
				if (ticket != null)
					return ticket;

				if (TicketSource != null && TicketId >= 0)
					return TicketSource.GetTicket(TicketId);

				return null;
			}
			set { ticket = value; }
		}

		/// <summary>
		/// Gets or sets the client.
		/// </summary>
		/// <value>
		/// The client.
		/// </value>
		public string Client { get; set; }

		/// <summary>
		/// Gets the date time when this instance was created.
		/// </summary>
		public DateTime Created { get; private set; }

		private IRedeemResult result = null;
		/// <summary>
		/// Gets or sets the result.
		/// NULL if it wasn't a redeem request.
		/// </summary>
		/// <value>
		/// The result.
		/// </value>
		public IRedeemResult Result
		{
			get { return result; }
			set
			{
				result = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Result"));
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="TicketEventArgs"/> class.
		/// </summary>
		/// <param name="ticket">The ticket.</param>
		/// <param name="client">The client.</param>
		public TicketEventArgs(ITicket ticket, string client = null)
		{
			this.ticket = ticket;
			Client = client;
			Created = DateTime.Now;
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="TicketEventArgs"/> class.
		/// </summary>
		/// <param name="ticketId">The ticket id.</param>
		/// <param name="client">The client.</param>
		public TicketEventArgs(int ticketId, ITicketDataSource ticketSource, string client = null)
		{
			TicketId = ticketId;
			TicketSource = ticketSource;
			Client = client;
			Created = DateTime.Now;
		}

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion
	}
}
