using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.BusinessLayer;
using System.Runtime.Serialization;

namespace TicketServer.Service
{
	/// <summary>
	/// Represents the result of a ticket redemtion.
	/// </summary>
	[DataContract]
	public class RedeemResult : IRedeemResult
	{
		#region IRedeemResult Members

		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		[DataMember]
		public Interfaces.Enums.RedeemResultType Type { get; set; }

		/// <summary>
		/// Gets or sets the error.
		/// </summary>
		/// <value>
		/// The error.
		/// </value>
		[DataMember]
		public string Error { get; set; }

		#endregion

		/// <summary>
		/// Initializes a new instance of the <see cref="RedeemResult"/> class.
		/// </summary>
		/// <param name="result">The result.</param>
		public RedeemResult(IRedeemResult result)
		{
			Type = result.Type;
			Error = result.Error;
		}
	}
}
