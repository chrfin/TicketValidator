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
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Windows.Threading;
using TicketServer.Common;
using TicketServer.Interfaces.Classes;
using Castle.ActiveRecord.Framework.Scopes;

namespace TicketServer.DAL.SqlCe
{
	public class SqlCeTicketDataSource : ITicketDataSource
	{
		private static bool ActiveRecordsInitialized = false;

		/// <summary>
		/// Gets the filename.
		/// </summary>
		public string Filename { get; private set; }

		/// <summary>
		/// Initializes a new instance of the <see cref="SqlCeTicketDataSource"/> class.
		/// </summary>
		/// <param name="filename">The filename wher the database is or should be created.</param>
		public SqlCeTicketDataSource(string filename)
		{
			Filename = filename;
			OpenFile();
		}

		/// <summary>
		/// Opens the file.
		/// </summary>
		private void OpenFile()
		{
			bool createSchema = false;
			if (!File.Exists(Filename))
			{
				createSchema = true;
				SqlCeEngine engine = new SqlCeEngine(SqlCE.GetConnectionString(Filename));
				engine.CreateDatabase();
				engine.Dispose();
			}


			if (!SqlCeTicketDataSource.ActiveRecordsInitialized)
			{
			IDictionary<string, string> properties = new Dictionary<string, string>();
			properties.Add("connection.driver_class", "NHibernate.Driver.SqlServerCeDriver");
			properties.Add("dialect", "NHibernate.Dialect.MsSqlCeDialect");
			properties.Add("connection.provider", "NHibernate.Connection.DriverConnectionProvider");
			properties.Add("connection.connection_string", SqlCE.GetConnectionString(Filename));
			properties.Add("proxyfactory.factory_class", "NHibernate.ByteCode.Castle.ProxyFactoryFactory, NHibernate.ByteCode.Castle");

			InPlaceConfigurationSource source = new InPlaceConfigurationSource();
			source.Add(typeof(ActiveRecordBase), properties);

				ActiveRecordStarter.Initialize(Assembly.GetExecutingAssembly(), source);
				SqlCeTicketDataSource.ActiveRecordsInitialized = true;
			}
			else
			{
				SqlCeConnection con = new SqlCeConnection(SqlCE.GetConnectionString(Filename));
				con.Open();
				DifferentDatabaseScope scope = new DifferentDatabaseScope(con);
			}

			if (createSchema)
				ActiveRecordStarter.CreateSchema();

			Tickets = new SafeObservable<ITicket>();
			IQueryable<ITicket> list = (from t in TicketRecord.Queryable
										select t).Cast<ITicket>();
			list.ToList().ForEach(t => Tickets.Add(t));
			Tickets.CollectionChanged += new NotifyCollectionChangedEventHandler(Tickets_CollectionChanged);
		}

		/// <summary>
		/// Handles the CollectionChanged event of the Tickets control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Collections.Specialized.NotifyCollectionChangedEventArgs"/> instance containing the event data.</param>
		protected void Tickets_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
		{
			switch (e.Action)
			{
				case NotifyCollectionChangedAction.Add:
					if (e.NewItems.Cast<ITicket>().ToList().Find(t => !(t is TicketRecord)) != null)
						throw new ArgumentException("Can only add TicketRecords! Please use AddTicket() to add other tickets!");
					break;
				case NotifyCollectionChangedAction.Move:
					break;
				case NotifyCollectionChangedAction.Remove:
					foreach (ITicket ticket in e.OldItems)
						(ticket as TicketRecord).Delete();
					break;
				case NotifyCollectionChangedAction.Replace:
					throw new NotSupportedException();
				case NotifyCollectionChangedAction.Reset:
					throw new NotImplementedException("Please don't change the whole list at all!");
				default:
					throw new ArgumentException();
			}
		}

		#region ITicketDataSource Members

		/// <summary>
		/// Gets the ticket count.
		/// </summary>
		public int TicketCount { get { return Tickets.Count(); } }
		/// <summary>
		/// Gets the redeemed count.
		/// </summary>
		public int RedeemedCount { get { return (from t in Tickets where t.IsRedeemed select t).Count(); } }

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
			newTicket.Street = ticket.Street;
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

			Tickets.Add(newTicket);

			return true;
		}

		/// <summary>
		/// Gets the ticket by its id.
		/// </summary>
		/// <param name="id">The id.</param>
		/// <returns></returns>
		public ITicket GetTicket(int id)
		{
			return (from t in Tickets
					where t.Id == id
					select t).FirstOrDefault();
		}
		/// <summary>
		/// Gets the ticket by its code.
		/// </summary>
		/// <param name="code">The code.</param>
		/// <returns></returns>
		public ITicket GetTicket(string code)
		{
			return (from t in Tickets
					where t.Code == code
					select t).FirstOrDefault();
		}

		/// <summary>
		/// Gets all the tickets.
		/// </summary>
		public SafeObservable<ITicket> Tickets { get; private set; }

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

		/// <summary>
		/// Resets all ticket redemtions in this data source.
		/// </summary>
		/// <param name="createBackup">if set to <c>true</c> a backup will be created.</param>
		/// <returns></returns>
		public bool Reset(bool createBackup = true)
		{
			if (createBackup)
				File.Copy(Filename, Filename.Replace(Path.GetExtension(Filename), "_" + DateTime.Now.ToString("yyyyMddHHmm") + Path.GetExtension(Filename)), true);
			
			var tickets = from t in Tickets
						  where t.IsRedeemed
						  select t;

			foreach (TicketRecord ticket in tickets)
			{
				ticket.IsRedeemed = false;
				ticket.RedeemDate = null;
				ticket.Save();
			}

			return true;
		}
		/// <summary>
		/// Clears this datasource from all tickets.
		/// </summary>
		/// <param name="createBackup">if set to <c>true</c> a backup will be created.</param>
		/// <returns></returns>
		public bool Clear(bool createBackup = true)
		{
			if (createBackup)
				File.Copy(Filename, Filename.Replace(Path.GetExtension(Filename), "_" + DateTime.Now.ToString("yyyyMddHHmm") + Path.GetExtension(Filename)), true);
			TicketRecord.DeleteAll();

			Tickets = new SafeObservable<ITicket>();
			Tickets.CollectionChanged += new NotifyCollectionChangedEventHandler(Tickets_CollectionChanged);

			return true;
		}

		#endregion
	}
}
