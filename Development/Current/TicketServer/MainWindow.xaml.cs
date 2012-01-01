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
using System.Net.Sockets;
using System.Threading;

using System.ServiceModel;
using System.ServiceModel.Description;

using TicketServer.Service;
using TicketServer.DAL;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		ServiceHost host;
		Thread hostThread;

		TicketService service;

		/// <summary>
		/// Initializes a new instance of the <see cref="MainWindow"/> class.
		/// </summary>
		public MainWindow()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Handles the Loaded event of the Window control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			hostThread = new Thread(new ThreadStart(delegate()
			{
				service = new TicketService(new DummyTicketDataSource());
				service.TicketRequested += new EventHandler(service_TicketRequested);

				host = new ServiceHost(service);
				host.Open();
			}));
			hostThread.Start();
		}

		/// <summary>
		/// Handles the TicketRequested event of the service control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		protected void service_TicketRequested(object sender, EventArgs e)
		{
			textBoxLog.Dispatcher.Invoke((Action)delegate()
			{
				textBoxLog.Text += string.Format("Ticket requested ({0}): {1}", (e as TicketEventArgs).Client ,(e as TicketEventArgs).Ticket.Code) + Environment.NewLine;
			});
		}

		/// <summary>
		/// Handles the Closing event of the Window control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			host.Close();
		}
	}
}
