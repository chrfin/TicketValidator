using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Castle.ActiveRecord;
using Castle.ActiveRecord.Framework;
using TicketServer.Interfaces;
using TicketServer.Interfaces.Enums;

namespace TicketServer.DAL.ActiveRecords
{
	/// <summary>
	/// This is the Active Record implementation of ITicket.
	/// </summary>
	[ActiveRecord("tickets")]
	public class TicketRecord : ActiveRecordLinqBase<TicketRecord>, ITicket
	{
		#region ITicket Members

		/// <summary>
		/// Gets or sets the id.
		/// </summary>
		/// <value>
		/// The id.
		/// </value>
		[PrimaryKey(Generator = PrimaryKeyType.Identity)]
		public int Id { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this ticket is a online ticket.
		/// </summary>
		/// <value>
		///   <c>true</c> if this is a online ticket; otherwise, <c>false</c>.
		/// </value>
		[Property]
		public bool IsOnlineTicket { get; set; }
		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		[Property]
		public TicketType Type { get; set; }
		/// <summary>
		/// Gets or sets the code.
		/// </summary>
		/// <value>
		/// The code.
		/// </value>
		[Property(Unique = true)]
		public string Code { get; set; }
		/// <summary>
		/// Gets or sets the name.
		/// </summary>
		/// <value>
		/// The name.
		/// </value>
		[Property]
		public string Name { get; set; }
		/// <summary>
		/// Gets or sets the address.
		/// </summary>
		/// <value>
		/// The address.
		/// </value>
		[Property]
		public string Street { get; set; }
		/// <summary>
		/// Gets or sets the zip.
		/// </summary>
		/// <value>
		/// The zip.
		/// </value>
		[Property]
		public string Zip { get; set; }
		/// <summary>
		/// Gets or sets the city.
		/// </summary>
		/// <value>
		/// The city.
		/// </value>
		[Property]
		public string City { get; set; }
		/// <summary>
		/// Gets or sets the phone.
		/// </summary>
		/// <value>
		/// The phone.
		/// </value>
		[Property]
		public string Phone { get; set; }
		/// <summary>
		/// Gets or sets the E mail.
		/// </summary>
		/// <value>
		/// The E mail.
		/// </value>
		[Property]
		public string EMail { get; set; }
		/// <summary>
		/// Gets or sets a value indicating whether this <see cref="Ticket"/> is redeemed.
		/// </summary>
		/// <value>
		///   <c>true</c> if redeemed; otherwise, <c>false</c>.
		/// </value>
		[Property]
		public bool IsRedeemed { get; set; }
		/// <summary>
		/// Gets or sets the redeem date.
		/// </summary>
		/// <value>
		/// The redeem date.
		/// </value>
		[Property("RedeemDate")]
		public DateTime? RedeemDateNullable { get; set; }

		/// <summary>
		/// Gets or sets the redeem date.
		/// </summary>
		/// <value>
		/// The redeem date.
		/// </value>
		public DateTime RedeemDate
		{
			get
			{
				return RedeemDateNullable.HasValue ? RedeemDateNullable.Value : new DateTime();
			}
			set
			{
				RedeemDateNullable = value.Year > 2000 ? value : (DateTime?)null;
			}
		}

		#endregion
	}
}
