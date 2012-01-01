using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using TicketServer.DAL;

namespace TicketServer.Service
{
	/// <summary>
	/// This represents a ticket.
	/// </summary>
	[DataContract]
	public class Ticket : ITicket
	{
		/// <summary>
		/// Gets or sets the id.
		/// </summary>
		/// <value>
		/// The id.
		/// </value>
		[DataMember]
		public int Id { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this ticket is a online ticket.
		/// </summary>
		/// <value>
		/// 	<c>true</c> if this is a online ticket; otherwise, <c>false</c>.
		/// </value>
		[DataMember]
		public bool IsOnlineTicket { get; set; }
		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		[DataMember]
		public CardType Type { get; set; }
		/// <summary>
		/// Gets or sets the code.
		/// </summary>
		/// <value>
		/// The code.
		/// </value>
		[DataMember]
		public string Code { get; set; }
		/// <summary>
		/// Gets or sets the name.
		/// </summary>
		/// <value>
		/// The name.
		/// </value>
		[DataMember]
		public string Name { get; set; }
		/// <summary>
		/// Gets or sets the address.
		/// </summary>
		/// <value>
		/// The address.
		/// </value>
		[DataMember]
		public string Address { get; set; }
		/// <summary>
		/// Gets or sets the zip.
		/// </summary>
		/// <value>
		/// The zip.
		/// </value>
		[DataMember]
		public string Zip { get; set; }
		/// <summary>
		/// Gets or sets the city.
		/// </summary>
		/// <value>
		/// The city.
		/// </value>
		[DataMember]
		public string City { get; set; }
		/// <summary>
		/// Gets or sets the phone.
		/// </summary>
		/// <value>
		/// The phone.
		/// </value>
		[DataMember]
		public string Phone { get; set; }
		/// <summary>
		/// Gets or sets the E mail.
		/// </summary>
		/// <value>
		/// The E mail.
		/// </value>
		[DataMember]
		public string EMail { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this <see cref="Ticket"/> is redeemed.
		/// </summary>
		/// <value>
		///   <c>true</c> if redeemed; otherwise, <c>false</c>.
		/// </value>
		[DataMember]
		public bool IsRedeemed { get; set; }
		/// <summary>
		/// Gets or sets the redeem date.
		/// </summary>
		/// <value>
		/// The redeem date.
		/// </value>
		[DataMember]
		public DateTime RedeemDate { get; set; }

		/// <summary>
		/// Initializes a new instance of the <see cref="Ticket"/> class.
		/// </summary>
		public Ticket() { }
		/// <summary>
		/// Initializes a new instance of the <see cref="Ticket"/> class.
		/// </summary>
		/// <param name="ticket">The ticket to copy.</param>
		public Ticket(ITicket ticket)
		{
			Id = ticket.Id;
			IsOnlineTicket = ticket.IsOnlineTicket;
			Type = ticket.Type;
			Code = ticket.Code;
			Name = ticket.Name;
			Address = ticket.Address;
			Zip = ticket.Zip;
			City = ticket.City;
			Phone = ticket.Phone;
			EMail = ticket.EMail;
			IsRedeemed = ticket.IsRedeemed;
			RedeemDate = ticket.RedeemDate;
		}
	}
}
