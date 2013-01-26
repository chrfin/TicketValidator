using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.WindowsAPICodePack.Dialogs;
using TicketServer.Common;
using TicketServer.Interfaces;
using TicketServer.Interfaces.Enums;
using TicketServer.Interfaces.DAL;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for TicketControl.xaml
	/// </summary>
	public partial class TicketControl : UserControl
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
		public static readonly DependencyProperty TicketProperty = DependencyProperty.Register("Ticket", typeof(ITicket), typeof(TicketControl));

		/// <summary>
		/// Occurs when a new ticket was created.
		/// </summary>
		public event EventHandler TicketCreated;
		/// <summary>
		/// Raises the <see cref="E:TicketCreated"/> event.
		/// </summary>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		protected virtual void OnTicketCreated(EventArgs e)
		{
			if (TicketCreated != null)
				TicketCreated(this, e);
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="TicketControl"/> class.
		/// </summary>
		public TicketControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Handles the Click event of the buttonDelete control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonDelete_Click(object sender, RoutedEventArgs e)
		{
			TaskDialog dialog = new TaskDialog();
			dialog.OwnerWindowHandle = new WindowInteropHelper(Window.GetWindow(this)).Handle;
			dialog.Cancelable = true;
			dialog.Caption = Properties.Resources.DeleteTicketCaption;
			dialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
			dialog.Icon = TaskDialogStandardIcon.None;
			dialog.StartupLocation = TaskDialogStartupLocation.CenterOwner;
			dialog.Text = Properties.Resources.DeleteTicketText;

			TaskDialogCommandLink buttonYes = new TaskDialogCommandLink("buttonYes", Properties.Resources.DeleteTicketYes);
			buttonYes.Click += new EventHandler(delegate(object snd, EventArgs eventArgs)
				{
					Ticket.Delete();
					Ticket = null;
					dialog.Close();
				});
			TaskDialogCommandLink buttonNo = new TaskDialogCommandLink("buttonNo", Properties.Resources.DeleteTicketNo);
			buttonNo.Click += new EventHandler(delegate(object snd, EventArgs eventArgs) { dialog.Close(); });

			dialog.Controls.Add(buttonYes);
			dialog.Controls.Add(buttonNo);

			dialog.Show();
		}

		/// <summary>
		/// Handles the Click event of the buttonSave control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonSave_Click(object sender, RoutedEventArgs e)
		{
			if (Ticket != null)
			{
				textBoxCode.GetBindingExpression(TextBox.TextProperty).UpdateSource();
				textBoxName.GetBindingExpression(TextBox.TextProperty).UpdateSource();
				textBoxStreet.GetBindingExpression(TextBox.TextProperty).UpdateSource();
				textBoxZip.GetBindingExpression(TextBox.TextProperty).UpdateSource();
				textBoxCity.GetBindingExpression(TextBox.TextProperty).UpdateSource();
				textBoxPhone.GetBindingExpression(TextBox.TextProperty).UpdateSource();
				textBoxMail.GetBindingExpression(TextBox.TextProperty).UpdateSource();

				Ticket.IsRedeemed = checkBoxRedeemed.IsChecked.Value;
				Ticket.IsOnlineTicket = checkBoxOnline.IsChecked.Value;
				Ticket.Type = (TicketType)comboBoxType.SelectedItem;

				DateTime result;
				Ticket.RedeemDate = textBoxRedeemDate.Text.Length < 8 ?
					(DateTime?)null : (DateTime.TryParse(textBoxRedeemDate.Text, out result) ? result : new DateTime());

				Ticket.Save();
			}
			else
			{
				MemoryTicket ticket = new MemoryTicket();
				ticket.IsOnlineTicket = checkBoxOnline.IsChecked.Value;
				ticket.Type = comboBoxType.SelectedItem == null ? TicketType.Normal : (TicketType)comboBoxType.SelectedItem;
				ticket.Code = textBoxCode.Text;
				ticket.Name = textBoxName.Text;
				ticket.Street = textBoxStreet.Text;
				ticket.Zip = textBoxZip.Text;
				ticket.City = textBoxCity.Text;
				ticket.Phone = textBoxPhone.Text;
				ticket.EMail = textBoxMail.Text;
				ticket.IsRedeemed = checkBoxRedeemed.IsChecked.Value;
				DateTime result;
				ticket.RedeemDate = textBoxRedeemDate.Text.Length < 8 ?
					 (DateTime?)null : (DateTime.TryParse(textBoxRedeemDate.Text, out result) ? result : new DateTime());

				OnTicketCreated(new TicketEventArgs(ticket));
			}
		}

		/// <summary>
		/// Handles the Checked event of the checkBoxRedeemed control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void checkBoxRedeemed_Checked(object sender, RoutedEventArgs e)
		{
			if (Ticket == null)
				return;

			if (!checkBoxRedeemed.IsChecked.Value)
				Ticket.RedeemDate = null;
			else if (Ticket.RedeemDate == null)
				Ticket.RedeemDate = DateTime.Now;
		}
	}
}
