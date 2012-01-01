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

using TicketService;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		ServiceHost host;
		Thread hostThread;

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
				host = new ServiceHost(typeof(TicketService.TicketService));
				host.Open();
			}));
			hostThread.Start();
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
