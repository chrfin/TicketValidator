using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using TicketServer.Interfaces.Attributes;
using TicketServer.Interfaces.Properties;

namespace TicketServer.Interfaces.Enums
{
	/// <summary>
	/// Defines the type of the card.
	/// </summary>
	public enum TicketType
	{
		/// <summary>
		/// A free card (lucky drawings or sponsors)
		/// </summary>
		[LocalizableDescription("TicketType_Free", typeof(Resources))]
		Free,
		/// <summary>
		/// A normal/paid card.
		/// </summary>
		[LocalizableDescription("TicketType_Normal", typeof(Resources))]
		Normal,
		/// <summary>
		/// A special card type.
		/// </summary>
		[LocalizableDescription("TicketType_Special", typeof(Resources))]
		Special
	}
}
