using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ProtoBuf;

namespace TicketValidator.Common
{
    /// <summary>
    /// Represents a ticket.
    /// </summary>
    [ProtoContract]
    [Serializable]
    public class Ticket
    {
        /// <summary>
        /// Gets or sets the id.
        /// </summary>
        /// <value>
        /// The id.
        /// </value>
        [ProtoMember(1)]
        public int Id { get; set; }
        /// <summary>
        /// Gets or sets a value indicating whether this ticket is a online ticket.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this is a online ticket; otherwise, <c>false</c>.
        /// </value>
        [ProtoMember(2)]
        public bool IsOnlineTicket { get; set; }
        /// <summary>
        /// Gets or sets the type.
        /// </summary>
        /// <value>
        /// The type.
        /// </value>
        [ProtoMember(3)]
        public CardType Type { get; set; }
        /// <summary>
        /// Gets or sets the code.
        /// </summary>
        /// <value>
        /// The code.
        /// </value>
        [ProtoMember(4)]
        public string Code { get; set; }
        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>
        /// The name.
        /// </value>
        [ProtoMember(5)]
        public string Name { get; set; }
        /// <summary>
        /// Gets or sets the address.
        /// </summary>
        /// <value>
        /// The address.
        /// </value>
        [ProtoMember(6)]
        public string Address { get; set; }
        /// <summary>
        /// Gets or sets the zip.
        /// </summary>
        /// <value>
        /// The zip.
        /// </value>
        [ProtoMember(7)]
        public string Zip { get; set; }
        /// <summary>
        /// Gets or sets the city.
        /// </summary>
        /// <value>
        /// The city.
        /// </value>
        [ProtoMember(8)]
        public string City { get; set; }
        /// <summary>
        /// Gets or sets the phone.
        /// </summary>
        /// <value>
        /// The phone.
        /// </value>
        [ProtoMember(9)]
        public string Phone { get; set; }
        /// <summary>
        /// Gets or sets the E mail.
        /// </summary>
        /// <value>
        /// The E mail.
        /// </value>
        [ProtoMember(10)]
        public string EMail { get; set; }
        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="Ticket"/> is redeemed.
        /// </summary>
        /// <value>
        ///   <c>true</c> if redeemed; otherwise, <c>false</c>.
        /// </value>
        [ProtoMember(11)]
        public bool IsRedeemed { get; set; }
        /// <summary>
        /// Gets or sets the redeem date.
        /// </summary>
        /// <value>
        /// The redeem date.
        /// </value>
        [ProtoMember(12)]
        public DateTime RedeemDate { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="Ticket"/> class.
        /// </summary>
        public Ticket() { Id = -1; }

        /// <summary>
        /// Determines whether the specified <see cref="System.Object"/> is equal to this instance.
        /// </summary>
        /// <param name="obj">The <see cref="System.Object"/> to compare with this instance.</param>
        /// <returns>
        ///   <c>true</c> if the specified <see cref="System.Object"/> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        /// <exception cref="T:System.NullReferenceException">
        /// The <paramref name="obj"/> parameter is null.
        ///   </exception>
        public override bool Equals(object obj)
        {
            return (obj is Ticket && (obj as Ticket).Id == this.Id) || (obj is string && ((string)obj) == this.Code);
        }
        /// <summary>
        /// Returns a hash code for this instance.
        /// </summary>
        /// <returns>
        /// A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table. 
        /// </returns>
        public override int GetHashCode()
        {
            return Convert.ToInt32(Code);
        }
    }
}
