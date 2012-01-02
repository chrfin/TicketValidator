using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.Enums;

namespace TicketServer.Interfaces
{
	/// <summary>
	/// Interface to represent a ticket.
	/// </summary>
	public interface ITicket
	{
		/// <summary>
		/// Gets or sets the id.
		/// </summary>
		/// <value>
		/// The id.
		/// </value>
		int Id { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this ticket is a online ticket.
		/// </summary>
		/// <value>
		/// 	<c>true</c> if this is a online ticket; otherwise, <c>false</c>.
		/// </value>
		bool IsOnlineTicket { get; set; }
		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		CardType Type { get; set; }
		/// <summary>
		/// Gets or sets the code.
		/// </summary>
		/// <value>
		/// The code.
		/// </value>
		string Code { get; set; }
		/// <summary>
		/// Gets or sets the name.
		/// </summary>
		/// <value>
		/// The name.
		/// </value>
		string Name { get; set; }
		/// <summary>
		/// Gets or sets the address.
		/// </summary>
		/// <value>
		/// The address.
		/// </value>
		string Address { get; set; }
		/// <summary>
		/// Gets or sets the zip.
		/// </summary>
		/// <value>
		/// The zip.
		/// </value>
		string Zip { get; set; }
		/// <summary>
		/// Gets or sets the city.
		/// </summary>
		/// <value>
		/// The city.
		/// </value>
		string City { get; set; }
		/// <summary>
		/// Gets or sets the phone.
		/// </summary>
		/// <value>
		/// The phone.
		/// </value>
		string Phone { get; set; }
		/// <summary>
		/// Gets or sets the E mail.
		/// </summary>
		/// <value>
		/// The E mail.
		/// </value>
		string EMail { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this <see cref="Ticket"/> is redeemed.
		/// </summary>
		/// <value>
		///   <c>true</c> if redeemed; otherwise, <c>false</c>.
		/// </value>
		bool IsRedeemed { get; set; }
		/// <summary>
		/// Gets or sets the redeem date.
		/// </summary>
		/// <value>
		/// The redeem date.
		/// </value>
		DateTime RedeemDate { get; set; }
	}
}
