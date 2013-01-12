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
using System.Windows.Shapes;
using TicketServer.Properties;
using Microsoft.Windows.Controls;
using System.Security;
using TicketServer.Common;

using WinForms = System.Windows.Forms;
using System.Net;
using System.IO;
using Microsoft.WindowsAPICodePack.Dialogs;
using System.Windows.Interop;
using System.Threading;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for SettingsWindow.xaml
	/// </summary>
	public partial class SettingsWindow : Window
	{
		/// <summary>
		/// Gets or sets a value indicating whether this instance is busy.
		/// </summary>
		/// <value>
		///   <c>true</c> if this instance is busy; otherwise, <c>false</c>.
		/// </value>
		public bool FtpIsBusy
		{
			get
			{
				bool busy = false;
				busyIndicatorFTP.Dispatcher.Invoke((Action)delegate() { busy = busyIndicatorFTP.IsBusy; });
				return busy;
			}
			set
			{
				busyIndicatorFTP.Dispatcher.Invoke((Action)delegate() { busyIndicatorFTP.IsBusy = value; });
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="SettingsWindow"/> class.
		/// </summary>
		public SettingsWindow()
		{
			InitializeComponent();

			passwordBoxFTP.Password = Helper.ToInsecureString(Helper.DecryptString(Settings.Default.FTPBackupPassword));
		}

		/// <summary>
		/// Handles the Click event of the buttonCancel control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonCancel_Click(object sender, RoutedEventArgs e) { Close(); }

		/// <summary>
		/// Handles the Click event of the buttonSave control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonSave_Click(object sender, RoutedEventArgs e)
		{
			Settings.Default.FTPBackupPassword = Helper.EncryptString(Helper.ToSecureString(passwordBoxFTP.Password));
			if (Settings.Default.FileBackupInterval <= 0)
				Settings.Default.FileBackupInterval = 1;
			if (Settings.Default.FTPBackupInterval <= 0)
				Settings.Default.FTPBackupInterval = 1;
			Settings.Default.Save();

			DialogResult = true;
			Close();
		}

		/// <summary>
		/// Handles the SelectionChanged event of the listBoxPage control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.Controls.SelectionChangedEventArgs"/> instance containing the event data.</param>
		private void listBoxPage_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			if (tabControlSettings != null && tabControlSettings.Items.Count > listBoxPage.SelectedIndex)
				tabControlSettings.SelectedIndex = listBoxPage.SelectedIndex;
		}

		/// <summary>
		/// Handles the Closed event of the Window control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		private void Window_Closed(object sender, EventArgs e)
		{
			if (!DialogResult.HasValue || !DialogResult.Value)
				Settings.Default.Reload();
		}

		/// <summary>
		/// Handles the Spin event of the ButtonSpinner control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="Microsoft.Windows.Controls.SpinEventArgs"/> instance containing the event data.</param>
		private void ButtonSpinner_Spin(object sender, Microsoft.Windows.Controls.SpinEventArgs e)
		{
			ButtonSpinner spinner = (ButtonSpinner)sender;
			TextBox txtBox = (TextBox)spinner.Content;
			Binding binding = txtBox.GetBindingExpression(TextBox.TextProperty).ParentBinding;

			int value = String.IsNullOrEmpty(txtBox.Text) ? 0 : Convert.ToInt32(txtBox.Text);
			if (e.Direction == Microsoft.Windows.Controls.SpinDirection.Increase)
				value++;
			else
				value--;
			if (value <= 0)
				value = 1;
			typeof(Settings).GetProperty(binding.Path.Path).SetValue(Settings.Default, Convert.ToUInt32(value), null);
		}

		/// <summary>
		/// Handles the Click event of the buttonBrowse control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonBrowse_Click(object sender, RoutedEventArgs e)
		{
			WinForms.FolderBrowserDialog fbd = new WinForms.FolderBrowserDialog();
			fbd.ShowNewFolderButton = true;
			if (fbd.ShowDialog() == WinForms.DialogResult.OK)
				Settings.Default.FileBackupFolder = fbd.SelectedPath;
		}

		/// <summary>
		/// Handles the Click event of the buttonBrowseFTP control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonBrowseFTP_Click(object sender, RoutedEventArgs e)
		{
			//ToDo: Implement!
			try
			{
				string server = (Settings.Default.FTPBackupServer.StartsWith("ftp:") ? String.Empty : "ftp://") + Settings.Default.FTPBackupServer;
				FtpWebRequest ftp = (FtpWebRequest)FtpWebRequest.Create(server);
				ftp.Method = WebRequestMethods.Ftp.ListDirectory;
				ftp.Credentials = new NetworkCredential(Settings.Default.FTPBackupUser, passwordBoxFTP.Password);
				FtpWebResponse response = (FtpWebResponse)ftp.GetResponse();

				Stream responseStream = response.GetResponseStream();
				StreamReader reader = new StreamReader(responseStream);

				System.Windows.MessageBox.Show("OK. " + reader.ReadToEnd());
				response.Close();
			}
			catch (Exception exp) { System.Windows.MessageBox.Show(exp.Message); }
		}

		/// <summary>
		/// Handles the Click event of the buttonTestFTP control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonTestFTP_Click(object sender, RoutedEventArgs e)
		{
			IntPtr handle = new WindowInteropHelper(this).Handle;
			Thread check = new Thread(new ThreadStart(delegate()
			{
				FtpIsBusy = true;

				try
				{
					string server = (Settings.Default.FTPBackupServer.StartsWith("ftp:") ? String.Empty : "ftp://") + Settings.Default.FTPBackupServer;
					FtpWebRequest ftp = (FtpWebRequest)FtpWebRequest.Create(server);
					ftp.Method = WebRequestMethods.Ftp.ListDirectory;
					ftp.Credentials = new NetworkCredential(Settings.Default.FTPBackupUser, passwordBoxFTP.Password);
					FtpWebResponse response = (FtpWebResponse)ftp.GetResponse();
					response.Close();

					TaskDialog dialog = new TaskDialog();
					dialog.Caption = Properties.SettingsWindow.FTPTestSuccessfullCaption;
					dialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
					dialog.Icon = TaskDialogStandardIcon.None;
					dialog.OwnerWindowHandle = handle;
					dialog.StandardButtons = TaskDialogStandardButtons.Ok;
					dialog.StartupLocation = TaskDialogStartupLocation.CenterOwner;
					dialog.InstructionText = Properties.SettingsWindow.FTPTestSuccessfullHeader;
					dialog.Text = Properties.SettingsWindow.FTPTestSuccessfullText;
					dialog.Show();
				}
				catch (Exception exp)
				{
					TaskDialog dialog = new TaskDialog();
					dialog.Caption = Properties.SettingsWindow.FTPTestFaildCaption;
					dialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
					dialog.Icon = TaskDialogStandardIcon.Error;
					dialog.OwnerWindowHandle = handle;
					dialog.StandardButtons = TaskDialogStandardButtons.Ok;
					dialog.StartupLocation = TaskDialogStartupLocation.CenterOwner;
					dialog.InstructionText = Properties.SettingsWindow.FTPTestFaildHeader;
					dialog.Text = exp.Message;
					dialog.Show();
				}

				FtpIsBusy = false;
			}));
			check.Start();
		}
	}
}