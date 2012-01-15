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
		// Using a DependencyProperty as the backing store for TicketSource.  This enables animation, styling, binding, etc...
		public static readonly DependencyProperty TicketSourceProperty = DependencyProperty.Register("TicketSource", typeof(ITicketDataSource), typeof(DatabaseControl));

		/// <summary>
		/// Initializes a new instance of the <see cref="DatabaseControl"/> class.
		/// </summary>
		public DatabaseControl()
		{
			InitializeComponent();
		}
	}
}
