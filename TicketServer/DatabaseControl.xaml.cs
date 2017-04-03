using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using TicketServer.Interfaces.DAL;
using TicketServer.Interfaces;
using TicketServer.Common;
using Microsoft.WindowsAPICodePack.Dialogs;
using System.Windows.Interop;
using System.Windows.Threading;
using System.Threading;
using System.Collections.ObjectModel;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for DatabaseControl.xaml
	/// </summary>
	public partial class DatabaseControl : UserControl
	{
		/// <summary>
		/// Gets or sets the ticket source.
		/// </summary>
		/// <value>
		/// The ticket source.
		/// </value>
		public ITicketDataSource TicketSource
		{
			get { return (ITicketDataSource)GetValue(TicketSourceProperty); }
			set { SetValue(TicketSourceProperty, value); }
		}
		public static readonly DependencyProperty TicketSourceProperty =
			DependencyProperty.Register("TicketSource", typeof(ITicketDataSource), typeof(DatabaseControl));

		/// <summary>
		/// Gets or sets the selected item.
		/// </summary>
		/// <value>
		/// The selected item.
		/// </value>
		public object SelectedItem
		{
			get { return listBoxTickets.SelectedItem; }
			set
			{
				if (!(value is ITicket))
					return;

				ITicket ticket = (listBoxTickets.ItemsSource as IList<ITicket>).First(t => t.Id == (value as ITicket).Id);
				if (ticket == null)
					return;

				listBoxTickets.SelectedItem = ticket;
				listBoxTickets.ScrollIntoView(ticket);
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="DatabaseControl"/> class.
		/// </summary>
		public DatabaseControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Handles the Click event of the buttonAdd control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonAdd_Click(object sender, RoutedEventArgs e)
		{
			listBoxTickets.SelectedItem = null;
		}

		/// <summary>
		/// Handles the Click event of the buttonDelete control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonDelete_Click(object sender, RoutedEventArgs e)
		{
			ITicketDataSource ticketSource = TicketSource;
			MainWindow window = Window.GetWindow(this) as MainWindow;
			IList<ITicket> ticketsRemove = listBoxTickets.SelectedItems.OfType<ITicket>().ToList();

			Thread worker = new Thread(new ThreadStart(delegate()
			{
				window.IsBusy = true;
				foreach (ITicket ticket in ticketsRemove)
					ticketSource.RemoveTicket(ticket, Dispatcher);
				window.IsBusy = false;
			}));
			worker.Start();
		}

		/// <summary>
		/// Handles the TicketCreated event of the ticketControlView control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		private void ticketControlView_TicketCreated(object sender, EventArgs e)
		{
			ITicket ticket = (e as TicketEventArgs).Ticket;
			if (TicketSource.AddTicket(ticket))
			{
				ticket = TicketSource.AllTickets.First(t => t.Code == ticket.Code);
				listBoxTickets.SelectedItem = ticket;
				listBoxTickets.ScrollIntoView(ticket);
			}
			else
			{
				TaskDialog dialog = new TaskDialog();
				dialog.Caption = Properties.Resources.TicketAddFailedCaption;
				dialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
				dialog.Icon = TaskDialogStandardIcon.Error;
				dialog.OwnerWindowHandle = new WindowInteropHelper(Window.GetWindow(this)).Handle;
				dialog.StandardButtons = TaskDialogStandardButtons.Ok;
				dialog.StartupLocation = TaskDialogStartupLocation.CenterOwner;
				dialog.InstructionText = Properties.Resources.TicketAddFailedHeader;
				dialog.Text = Properties.Resources.TicketAddFailedText;
				dialog.Show();
			}
		}
	}
}
