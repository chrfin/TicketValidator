using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.BusinessLayer;
using TicketServer.Interfaces.Enums;

namespace TicketServer.DAL
{
	class DummyRedeemResult : IRedeemResult
	{
		#region IRedeemResult Members

		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		public RedeemResultType Type { get; set; }

		/// <summary>
		/// Gets or sets the error.
		/// </summary>
		/// <value>
		/// The error.
		/// </value>
		public string Error { get; set; }

		#endregion

		/// <summary>
		/// Initializes a new instance of the <see cref="DummyRedeemResult"/> class.
		/// </summary>
		/// <param name="result">The result.</param>
		public DummyRedeemResult(RedeemResultType type = RedeemResultType.Redeemed, string error = null)
		{
			Type = type;
			Error = error;
		}
	}
}
