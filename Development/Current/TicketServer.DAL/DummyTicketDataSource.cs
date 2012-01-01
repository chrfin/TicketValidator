using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

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
		public bool RedeemTicket(int id)
		{
			return true;
		}

		#endregion
	}
}
