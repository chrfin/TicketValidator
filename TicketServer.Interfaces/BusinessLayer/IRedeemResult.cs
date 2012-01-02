using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.Enums;

namespace TicketServer.Interfaces.BusinessLayer
{
	/// <summary>
	/// Interface which represents the result of a ticket redemtion
	/// </summary>
	public interface IRedeemResult
	{
		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		RedeemResultType Type { get; set; }
		/// <summary>
		/// Gets or sets the error.
		/// </summary>
		/// <value>
		/// The error.
		/// </value>
		string Error { get; set; }
	}
}
