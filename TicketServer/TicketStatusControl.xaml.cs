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
using TicketServer.Interfaces;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for TicketStatusControl.xaml
	/// </summary>
	public partial class TicketStatusControl : UserControl
	{
		/// <summary>
		/// Gets or sets the ticket.
		/// </summary>
		/// <value>
		/// The ticket.
		/// </value>
		public ITicket Ticket
		{
			get { return (ITicket)GetValue(TicketProperty); }
			set { SetValue(TicketProperty, value); }
		}
		// Using a DependencyProperty as the backing store for Ticket.  This enables animation, styling, binding, etc...
		public static readonly DependencyProperty TicketProperty = DependencyProperty.Register("Ticket", typeof(ITicket), typeof(TicketStatusControl));

		/// <summary>
		/// Initializes a new instance of the <see cref="TicketStatusControl"/> class.
		/// </summary>
		public TicketStatusControl()
		{
			InitializeComponent();
		}
	}
}
