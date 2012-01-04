﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TicketServer.Interfaces.DAL;
using TicketServer.Interfaces.BusinessLayer;
using TicketServer.Interfaces;
using System.Collections;
using NHibernate.Cfg;
using Castle.ActiveRecord.Framework.Config;
using Castle.ActiveRecord;
using System.Reflection;
using System.IO;
using System.Data.SqlServerCe;
using TicketServer.DAL.ActiveRecords;
using TicketServer.Interfaces.Enums;

namespace TicketServer.DAL.SqlCe
{
	public class SqlCeTicketDataSource : ITicketDataSource
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SqlCeTicketDataSource"/> class.
		/// </summary>
		/// <param name="filename">The filename wher the database is or should be created.</param>
		public SqlCeTicketDataSource(string filename)
		{
			bool createSchema = false;
			if (!File.Exists(filename))
			{
				createSchema = true;
				SqlCeEngine engine = new SqlCeEngine(SqlCE.GetConnectionString(filename));
				engine.CreateDatabase();
				engine.Dispose();
			}

			IDictionary<string, string> properties = new Dictionary<string, string>();
			properties.Add("connection.driver_class", "NHibernate.Driver.SqlServerCeDriver");
			properties.Add("dialect", "NHibernate.Dialect.MsSqlCeDialect");
			properties.Add("connection.provider", "NHibernate.Connection.DriverConnectionProvider");
			properties.Add("connection.connection_string", SqlCE.GetConnectionString(filename));
			properties.Add("proxyfactory.factory_class", "NHibernate.ByteCode.Castle.ProxyFactoryFactory, NHibernate.ByteCode.Castle");

			InPlaceConfigurationSource source = new InPlaceConfigurationSource();
			source.Add(typeof(ActiveRecordBase), properties);

			ActiveRecordStarter.Initialize(Assembly.GetExecutingAssembly(), source);

			if (createSchema)
				ActiveRecordStarter.CreateSchema();
		}

		#region ITicketDataSource Members

		/// <summary>
		/// Gets the ticket count.
		/// </summary>
		public int TicketCount { get { return ActiveRecordMediator<TicketRecord>.Count(); } }

		/// <summary>
		/// Gets the redeemed count.
		/// </summary>
		public int RedeemedCount { get { return (from t in TicketRecord.Queryable where t.IsRedeemed select t).Count(); } }

		/// <summary>
		/// Adds the ticket to the data source.
		/// </summary>
		/// <param name="ticket">The ticket.</param>
		/// <returns></returns>
		public bool AddTicket(ITicket ticket)
		{
			TicketRecord newTicket = new TicketRecord();

			if (ticket.Id > 0)
				newTicket.Id = ticket.Id;
			newTicket.Address = ticket.Address;
			newTicket.City = ticket.City;
			newTicket.Code = ticket.Code;
			newTicket.EMail = ticket.EMail;
			newTicket.IsOnlineTicket = ticket.IsOnlineTicket;
			newTicket.IsRedeemed = ticket.IsRedeemed;
			newTicket.Name = ticket.Name;
			newTicket.Phone = ticket.Phone;
			newTicket.RedeemDate = ticket.RedeemDate;
			newTicket.Type = ticket.Type;
			newTicket.Zip = ticket.Zip;

			try 
			{
				using (new SessionScope())
				{
					newTicket.Create();
				}
			}
			catch { return false; }

			return true;
		}

		/// <summary>
		/// Gets the ticket by its id.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public ITicket GetTicket(int id)
		{
			return TicketRecord.Find(id);
		}
		/// <summary>
		/// Gets the ticket by its code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		public ITicket GetTicket(string code)
		{
			return (from t in TicketRecord.Queryable
					where t.Code == code
					select t).FirstOrDefault();
		}

		/// <summary>
		/// Gets all the tickets.
		/// </summary>
		public IList<ITicket> Tickets
		{
			get
			{
				return (from t in TicketRecord.Queryable
						select t).ToList() as IList<ITicket>;
			}
		}

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public IRedeemResult RedeemTicket(int id)
		{
			SqlCeRedeemResult result = new SqlCeRedeemResult();

			TicketRecord ticket = GetTicket(id) as TicketRecord;

			if (ticket.IsRedeemed)
				result.Type = RedeemResultType.AlreadyRedeemed;
			else
			{
				ticket.IsRedeemed = true;
				ticket.RedeemDate = DateTime.Now;
				try
				{
					ticket.Save();
					result.Type = RedeemResultType.Redeemed;
				}
				catch (Exception exp)
				{
					result.Type = RedeemResultType.NotRedeemed;
					result.Error = exp.Message;
				}
			}

			return result;
		}

		#endregion
	}
}