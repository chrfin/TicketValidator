using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.Enums;
using TicketServer.Interfaces.BusinessLayer;
using System.Collections.ObjectModel;
using TicketServer.Interfaces.Classes;
using System.ComponentModel;

namespace TicketServer.Interfaces.DAL
{
	/// <summary>
	/// Interface to represent a ticket data source.
	/// </summary>
	public interface ITicketDataSource : INotifyPropertyChanged
	{
		/// <summary>
		/// Gets the ticket count. Special tickets are not included!
		/// </summary>
		int TicketCount { get; }
		/// <summary>
		/// Gets the redeemed count. Special tickets are not included!
		/// </summary>
		int RedeemedCount { get; }

		/// <summary>
		/// Adds the ticket to the data source.
		/// </summary>
		/// <param name="ticket">The ticket.</param>
		/// <returns></returns>
		bool AddTicket(ITicket ticket);

		/// <summary>
		/// Gets the ticket by its id.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		ITicket GetTicket(int id);
		/// <summary>
		/// Gets the ticket by its code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		ITicket GetTicket(string code);

		/// <summary>
		/// Gets all the tickets including special tickets.
		/// </summary>
		SafeObservable<ITicket> AllTickets { get; }
		/// <summary>
		/// Gets all the tickets except special tickets.
		/// </summary>
		SafeObservable<ITicket> ActiveTickets { get; }

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		IRedeemResult RedeemTicket(int id);

		/// <summary>
		/// Resets all ticket redemtions in this data source.
		/// </summary>
		/// <param name="createBackup">if set to <c>true</c> a backup will be created.</param>
		/// <returns></returns>
		bool Reset(bool createBackup = true);
		/// <summary>
		/// Clears this datasource from all tickets.
		/// </summary>
		/// <param name="createBackup">if set to <c>true</c> a backup will be created.</param>
		/// <returns></returns>
		bool Clear(bool createBackup = true);

		/// <summary>
		/// Gets or sets the string identifing special tickets. Seperate multiple strings with semicolon (group1;group2;...).
		/// </summary>
		/// <value>
		/// The special tickets string.
		/// </value>
		string SpecialTicketsString { get; set; }
	}
}
