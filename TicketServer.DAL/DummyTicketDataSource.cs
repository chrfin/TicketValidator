using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.DAL;
using TicketServer.Interfaces;
using TicketServer.Interfaces.Enums;
using TicketServer.Interfaces.BusinessLayer;

namespace TicketServer.DAL
{
	/// <summary>
	/// Dummy source for testing.
	/// </summary>
	public class DummyTicketDataSource : ITicketDataSource
	{
		#region ITicketDataSource Members

		/// <summary>
		/// Gets the ticket by its id.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public ITicket GetTicket(int id)
		{
			DummyTicket ticket = new DummyTicket();

			ticket.Id = id;
			ticket.IsOnlineTicket = true;
			ticket.Name = "TESTER TEST";
			ticket.Address = "Testergasse 12";
			ticket.Zip = "1234";
			ticket.City = "Testingen";
			ticket.Phone = "+43/1234/567890";
			ticket.EMail = "tester@butzvarruckt.at";

			return ticket;
		}

		/// <summary>
		/// Gets the ticket by its code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		public ITicket GetTicket(string code)
		{
			DummyTicket ticket = new DummyTicket();

			ticket.Id = 1234;
			ticket.Code = code;
			ticket.IsOnlineTicket = true;
			ticket.Name = "TESTER TEST";
			ticket.Address = "Testergasse 12";
			ticket.Zip = "1234";
			ticket.City = "Testingen";
			ticket.Phone = "+43/1234/567890";
			ticket.EMail = "tester@butzvarruckt.at";

			return ticket;
		}

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public IRedeemResult RedeemTicket(int id)
		{
			return new DummyRedeemResult();
		}

		#endregion
	}
}
