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
using System.IO;
using System.Net;
using TicketValidator.Common;
using ProtoBuf;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		bool running;

		TcpListener server;
		List<Thread> clientListeners = new List<Thread>();

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
			server = new TcpListener(IPAddress.Any, 7880);

			Thread listener = new Thread(new ThreadStart(delegate()
				{
					running = true;
					server.Start();

					while (running)
					{
						while (server.Pending())
							Thread.Sleep(100);
						TcpClient client = server.AcceptTcpClient();
						if (client != null)
						{
							Thread clientReader = new Thread(new ParameterizedThreadStart(ClientListener));
							clientReader.Start(client);
							clientListeners.Add(clientReader);
						}
					}
				}));
			listener.Start();
		}

		/// <summary>
		/// Handles the Closing event of the Window control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			running = false;
		}

		/// <summary>
		/// Listens to data from the client.
		/// </summary>
		/// <param name="client">The client.</param>
		protected void ClientListener(object client)
		{
			TcpClient tcpClient = client as TcpClient;
			Stream stream = tcpClient.GetStream();

			while (running && tcpClient.Connected)
			{
				while (tcpClient.Available <= 0)
					Thread.Sleep(100);

				byte[] buffer = new byte[tcpClient.Available];
				stream.Read(buffer, 0, buffer.Length);
				string code = Encoding.UTF8.GetString(buffer);

				textBoxLog.Dispatcher.Invoke((Action)delegate()
				{
					textBoxLog.Text += "Code received: " + code + Environment.NewLine;
				});

				Ticket ticket = new Ticket();
				ticket.Code = code;
				ticket.Name = "TEST";

				Serializer.Serialize(stream, ticket);
				stream.Flush();
			}
		}
	}
}
