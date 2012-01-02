﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using TicketServer.DAL;
using TicketServer.Interfaces;
using TicketServer.Interfaces.Enums;

namespace TicketServer.DAL
{
	/// <summary>
	/// A dummy ticket for testing.
	/// </summary>
	public class DummyTicket : ITicket
	{
		/// <summary>
		/// Gets or sets the id.
		/// </summary>
		/// <value>
		/// The id.
		/// </value>
		public int Id { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this ticket is a online ticket.
		/// </summary>
		/// <value>
		/// 	<c>true</c> if this is a online ticket; otherwise, <c>false</c>.
		/// </value>
		public bool IsOnlineTicket { get; set; }
		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		public CardType Type { get; set; }
		/// <summary>
		/// Gets or sets the code.
		/// </summary>
		/// <value>
		/// The code.
		/// </value>
		public string Code { get; set; }
		/// <summary>
		/// Gets or sets the name.
		/// </summary>
		/// <value>
		/// The name.
		/// </value>
		public string Name { get; set; }
		/// <summary>
		/// Gets or sets the address.
		/// </summary>
		/// <value>
		/// The address.
		/// </value>
		public string Address { get; set; }
		/// <summary>
		/// Gets or sets the zip.
		/// </summary>
		/// <value>
		/// The zip.
		/// </value>
		public string Zip { get; set; }
		/// <summary>
		/// Gets or sets the city.
		/// </summary>
		/// <value>
		/// The city.
		/// </value>
		public string City { get; set; }
		/// <summary>
		/// Gets or sets the phone.
		/// </summary>
		/// <value>
		/// The phone.
		/// </value>
		public string Phone { get; set; }
		/// <summary>
		/// Gets or sets the E mail.
		/// </summary>
		/// <value>
		/// The E mail.
		/// </value>
		public string EMail { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this <see cref="Ticket"/> is redeemed.
		/// </summary>
		/// <value>
		///   <c>true</c> if redeemed; otherwise, <c>false</c>.
		/// </value>
		public bool IsRedeemed { get; set; }
		/// <summary>
		/// Gets or sets the redeem date.
		/// </summary>
		/// <value>
		/// The redeem date.
		/// </value>
		public DateTime RedeemDate { get; set; }

		/// <summary>
		/// Initializes a new instance of the <see cref="Ticket"/> class.
		/// </summary>
		public DummyTicket() { Id = -1; }
	}
}
