using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TicketServer.Interfaces.Enums
{
	/// <summary>
	/// Result types of a ticket redemtion.
	/// </summary>
	public enum RedeemResultType
	{
		/// <summary>
		/// Ticket was successfully redeemed.
		/// </summary>
		Redeemed,
		/// <summary>
		/// Ticket is already redeemed.
		/// </summary>
		AlreadyRedeemed,
		/// <summary>
		/// The ticket was NOT redeemed.
		/// </summary>
		NotRedeemed
	}
}
