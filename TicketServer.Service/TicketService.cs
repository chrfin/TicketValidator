﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TicketServer.DAL;
using TicketServer.Common;
using TicketServer.Interfaces.DAL;
using TicketServer.Interfaces.Enums;
using TicketServer.Interfaces.BusinessLayer;
using TicketServer.Interfaces;
using System.ComponentModel;
using System.Diagnostics;

namespace TicketServer.Service
{
	/// <summary>
	/// The ticket service.
	/// </summary>
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single, UseSynchronizationContext=false)]
	public class TicketService : ITicketService, INotifyPropertyChanged
	{
		private ITicketDataSource ticketSource;
		/// <summary>
		/// Gets or sets the ticket source.
		/// </summary>
		/// <value>
		/// The ticket source.
		/// </value>
		public ITicketDataSource TicketSource
		{
			get { return ticketSource; }
			set
			{
				ticketSource = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("TicketSource"));
			}
		}

		/// <summary>
		/// Gets the client.
		/// </summary>
		protected RemoteEndpointMessageProperty Client
		{
			get
			{
				OperationContext context = OperationContext.Current;
				MessageProperties prop = context.IncomingMessageProperties;
				return prop[RemoteEndpointMessageProperty.Name] as RemoteEndpointMessageProperty;
			}
		}

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
		/// Gets the state of the service.
		/// </summary>
		/// <returns></returns>
		public ServiceStatus GetCurrentState()
		{
			return ServiceStatus.Running;
		}

		/// <summary>
		/// Gets the ticket with the specific code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		public Ticket GetTicket(string code)
		{
			Trace.WriteLine("Ticket requested: " + code);

			ITicket sourceTicket = TicketSource.GetTicket(code);
			if (sourceTicket == null)
				return null;

			Ticket ticket = new Ticket(sourceTicket);

			AsyncHelper.FireAsync(TicketRequested, this, new TicketEventArgs(sourceTicket, Client.Address));

			return ticket;
		}

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public RedeemResult RedeemTicket(int id)
		{
			RedeemResult result = new RedeemResult(TicketSource.RedeemTicket(id));

			AsyncHelper.FireAsync(TicketRedeemed, this, new TicketEventArgs(id, TicketSource, Client.Address) { Result = result });

			return result;
		}

		#endregion

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion
	}
}
