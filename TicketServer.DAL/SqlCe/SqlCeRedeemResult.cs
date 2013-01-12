using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.BusinessLayer;
using TicketServer.Interfaces.Enums;

namespace TicketServer.DAL.SqlCe
{
	internal class SqlCeRedeemResult : IRedeemResult
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
	}
}
