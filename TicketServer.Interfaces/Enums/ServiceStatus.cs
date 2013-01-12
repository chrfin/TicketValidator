using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TicketServer.Interfaces.Enums
{
	/// <summary>
	/// Defines the state of a service.
	/// </summary>
	public enum ServiceStatus
	{
		/// <summary>
		/// The serive is up an running.
		/// </summary>
		Running,
		/// <summary>
		/// The service is up, but not jet ready.
		/// </summary>
		NotReady,
		/// <summary>
		/// The service is up, but is in an error state.
		/// </summary>
		Error
	}
}
