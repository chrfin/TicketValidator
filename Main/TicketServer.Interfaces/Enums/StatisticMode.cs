using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TicketServer.Interfaces.Enums
{
	/// <summary>
	/// The mode how the statisitc should add up its values.
	/// </summary>
	public enum StatisticMode
	{
		/// <summary>
		/// The total value until the current value
		/// </summary>
		Total,
		/// <summary>
		/// The changes since the last value
		/// </summary>
		PerUnit
	}
}
