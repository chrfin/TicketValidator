using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Castle.ActiveRecord;
using Castle.ActiveRecord.Framework;
using TicketServer.Interfaces;
using TicketServer.Interfaces.Enums;
using System.ComponentModel;

namespace TicketServer.DAL.ActiveRecords
{
	/// <summary>
	/// This is the Active Record implementation of ITicket.
	/// </summary>
	[ActiveRecord("tickets")]
	public class TicketRecord : ActiveRecordLinqBase<TicketRecord>, ITicket
	{
		#region private members

		private int id;
		private bool isOnlineTicket;
		private TicketType type;
		private string code;
		private string name;
		private string street;
		private string zip;
		private string city;
		private string phone;
		private string email;
		private bool isRedeemed;
		private DateTime? redeemDate;

		#endregion

		#region ITicket Members

		/// <summary>
		/// Gets or sets the id.
		/// </summary>
		/// <value>
		/// The id.
		/// </value>
		[PrimaryKey(Generator = PrimaryKeyType.Identity)]
		public int Id
		{
			get { return id; }
			set
			{
				id = value; 
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Id"));
			}
		}
		/// <summary>
		/// Gets or sets a value indicating whether this ticket is a online ticket.
		/// </summary>
		/// <value>
		///   <c>true</c> if this is a online ticket; otherwise, <c>false</c>.
		/// </value>
		[Property]
		public bool IsOnlineTicket
		{
			get { return isOnlineTicket; }
			set
			{
				isOnlineTicket = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("IsOnlineTicket"));
			}
		}
		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		[Property]
		public TicketType Type
		{
			get { return type; }
			set
			{
				type = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Type"));
			}
		}
		/// <summary>
		/// Gets or sets the code.
		/// </summary>
		/// <value>
		/// The code.
		/// </value>
		[Property(Unique = true)]
		public string Code
		{
			get { return code; }
			set
			{
				code = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Code"));
			}
		}
		/// <summary>
		/// Gets or sets the name.
		/// </summary>
		/// <value>
		/// The name.
		/// </value>
		[Property]
		public string Name
		{
			get { return name; }
			set
			{
				name = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Name"));
			}
		}
		/// <summary>
		/// Gets or sets the address.
		/// </summary>
		/// <value>
		/// The address.
		/// </value>
		[Property]
		public string Street
		{
			get { return street; }
			set
			{
				street = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Street"));
			}
		}
		/// <summary>
		/// Gets or sets the zip.
		/// </summary>
		/// <value>
		/// The zip.
		/// </value>
		[Property]
		public string Zip
		{
			get { return zip; }
			set
			{
				zip = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Zip"));
			}
		}
		/// <summary>
		/// Gets or sets the city.
		/// </summary>
		/// <value>
		/// The city.
		/// </value>
		[Property]
		public string City
		{
			get { return city; }
			set
			{
				city = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("City"));
			}
		}
		/// <summary>
		/// Gets or sets the phone.
		/// </summary>
		/// <value>
		/// The phone.
		/// </value>
		[Property]
		public string Phone
		{
			get { return phone; }
			set
			{
				phone = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Phone"));
			}
		}
		/// <summary>
		/// Gets or sets the E mail.
		/// </summary>
		/// <value>
		/// The E mail.
		/// </value>
		[Property]
		public string EMail
		{
			get { return email; }
			set
			{
				email = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("EMail"));
			}
		}
		/// <summary>
		/// Gets or sets a value indicating whether this <see cref="Ticket"/> is redeemed.
		/// </summary>
		/// <value>
		///   <c>true</c> if redeemed; otherwise, <c>false</c>.
		/// </value>
		[Property]
		public bool IsRedeemed
		{
			get { return isRedeemed; }
			set
			{
				isRedeemed = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("IsRedeemed"));
			}
		}
		/// <summary>
		/// Gets or sets the redeem date.
		/// </summary>
		/// <value>
		/// The redeem date.
		/// </value>
		[Property]
		public DateTime? RedeemDate
		{
			get { return redeemDate; }
			set
			{
				redeemDate = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("RedeemDate"));
			}
		}

		#endregion

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion
	}
}
