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
using Microsoft.Windows.Controls.Ribbon;
using TicketServer.Client.TicketService;

namespace TicketServer.Client
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : RibbonWindow
	{
		TicketServiceClient service;

		public MainWindow()
		{
			InitializeComponent();

			service = new TicketServiceClient();
		}

		private void buttonExit_Click(object sender, RoutedEventArgs e)
		{
			Close();
		}

		private void buttonStatus_Click(object sender, RoutedEventArgs e)
		{
			ServiceStatus status = service.GetCurrentState();
			textBoxStatus.Text = "Status: " + status.ToString() + Environment.NewLine + textBoxStatus.Text;
		}

		private void buttonGetTicket_Click(object sender, RoutedEventArgs e)
		{
			Ticket ticket = service.GetTicket(textBoxCode.Text);
			textBoxStatus.Text = "Ticket: " + ticket.Id + Environment.NewLine + textBoxStatus.Text;
		}

		private void buttonRedeemTicket_Click(object sender, RoutedEventArgs e)
		{
			RedeemResult result = service.RedeemTicket(Convert.ToInt32(textBoxId.Text));
			textBoxStatus.Text = "Redeem: " + result.Type.ToString() + Environment.NewLine + textBoxStatus.Text;
		}
	}
}
