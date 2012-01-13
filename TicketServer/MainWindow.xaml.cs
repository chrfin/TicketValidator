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
using TicketServer.Common;
using TicketServer.DAL.SqlCe;
using Microsoft.Windows.Controls.Ribbon;
using TicketServer.Properties;
using System.Globalization;
using RootLibrary.WPF.Localization;
using Microsoft.WindowsAPICodePack.Dialogs;
using Microsoft.VisualBasic.FileIO;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : RibbonWindow
	{
		ServiceHost host;
		Thread hostThread;

		TicketService service;

		/// <summary>
		/// Gets or sets the filename.
		/// </summary>
		/// <value>
		/// The filename.
		/// </value>
		protected string Filename { get; set; }

		/// <summary>
		/// Initializes a new instance of the <see cref="MainWindow"/> class.
		/// </summary>
		public MainWindow()
		{
			InitializeComponent();

			PrepareLocalisation();

			if (Settings.Default.CurrentDataFile.StartsWith("./"))
				Filename = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, Settings.Default.CurrentDataFile.Substring(2));
			else
				Filename = Settings.Default.CurrentDataFile;

			UpdateTitle();
		}

		/// <summary>
		/// Updates the title of the window.
		/// </summary>
		private void UpdateTitle()
		{
			Title = string.Format(Properties.Resources.MainTitleFile, System.IO.Path.GetFileName(Filename));
		}

		/// <summary>
		/// Prepares the localisation.
		/// </summary>
		private void PrepareLocalisation()
		{
			foreach (string lang in Settings.Default.AvailableLanguages.Split(';'))
			{
				CultureInfo culture = new CultureInfo(lang);
				RibbonGalleryItem item = new RibbonGalleryItem();
				item.Content = culture.Parent.NativeName + " (" + culture.Parent.EnglishName + ")";
				item.Tag = culture;
				item.Selected += new RoutedEventHandler(language_Selected);
				ribbonGalleryCategoryLanguages.Items.Add(item);

				if (culture.TwoLetterISOLanguageName == Settings.Default.SelectedLanguage)
					SetUICulture(culture);
			}
		}

		/// <summary>
		/// Handles the Selected event of the language control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void language_Selected(object sender, RoutedEventArgs e)
		{
			SetUICulture((sender as RibbonGalleryItem).Tag as CultureInfo);
		}

		/// <summary>
		/// Sets the UI culture.
		/// </summary>
		/// <param name="culture">The culture.</param>
		private void SetUICulture(CultureInfo culture)
		{
			Thread.CurrentThread.CurrentCulture = culture;
			Thread.CurrentThread.CurrentUICulture = culture;
			LocalizeDictionary.Instance.Culture = culture;

			foreach (RibbonGalleryItem item in ribbonGalleryCategoryLanguages.Items)
			{
				if (item.Tag == culture)
					item.IsSelected = true;
			}

			Settings.Default.SelectedLanguage = culture.TwoLetterISOLanguageName;
			Settings.Default.Save();
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
				service = new TicketService(new SqlCeTicketDataSource(Filename));
				service.TicketRequested += new EventHandler(service_TicketRequested);
				service.TicketRedeemed += new EventHandler(service_TicketRedeemed);

				host = new ServiceHost(service);
				host.Open();
			}));
			hostThread.Start();
		}

		/// <summary>
		/// Handles the TicketRedeemed event of the service control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		void service_TicketRedeemed(object sender, EventArgs e)
		{
			textBoxLog.Dispatcher.Invoke((Action)delegate()
			{
				textBoxLog.Text += string.Format("Ticket redeemed ({0}): {1}", (e as TicketEventArgs).Client, (e as TicketEventArgs).Ticket.Code) + Environment.NewLine;
			});
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
				textBoxLog.Text += string.Format("Ticket requested ({0}): {1}", (e as TicketEventArgs).Client, (e as TicketEventArgs).Ticket.Code) + Environment.NewLine;
			});
		}

		/// <summary>
		/// Handles the Closing event of the Window control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			//Does not work while debigging
			//TaskDialog errorDialog = new TaskDialog();

			//errorDialog.Cancelable = true;
			//errorDialog.Icon = TaskDialogStandardIcon.None;

			//errorDialog.Caption = "Caption";
			//errorDialog.InstructionText = "IT";
			//errorDialog.Text = "Text";

			//errorDialog.DetailsExpanded = false;
			//errorDialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
			//errorDialog.StandardButtons = TaskDialogStandardButtons.Yes;

			//TaskDialogCommandLink buttonYes = new TaskDialogCommandLink("buttonClose", "T", "I");
			//buttonYes.Click += new EventHandler(delegate(object snd, EventArgs eventArgs)
			//{
			//    host.Close();
			//});
			//errorDialog.Controls.Add(buttonYes);

			//errorDialog.Show();

			host.Close();
		}

		/// <summary>
		/// Handles the Click event of the buttonImport control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonImport_Click(object sender, RoutedEventArgs e)
		{
			ImportWindow import = new ImportWindow(service.TicketSource);
			import.Owner = this;
			import.ShowDialog();
		}

		/// <summary>
		/// Handles the Click event of the buttonClear control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonClear_Click(object sender, RoutedEventArgs e) { service.TicketSource.Clear(); }
		/// <summary>
		/// Handles the Click event of the buttonReset control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonReset_Click(object sender, RoutedEventArgs e) { service.TicketSource.Reset(); }

		/// <summary>
		/// Handles the Click event of the buttonExit control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonExit_Click(object sender, RoutedEventArgs e) { Close(); }

		/// <summary>
		/// Handles the Click event of the buttonNew control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonNew_Click(object sender, RoutedEventArgs e)
		{
			CommonSaveFileDialog sfd = new CommonSaveFileDialog();
			sfd.Filters.Add(new CommonFileDialogFilter(Properties.Resources.FileFilterText, Properties.Resources.FileFilterExtension));
			sfd.DefaultExtension = Properties.Resources.FileFilterExtension;
			sfd.AlwaysAppendDefaultExtension = true;
			if (sfd.ShowDialog() == CommonFileDialogResult.Ok)
			{
				if (System.IO.File.Exists(sfd.FileName))
					FileSystem.DeleteFile(sfd.FileName, UIOption.OnlyErrorDialogs, RecycleOption.SendToRecycleBin);

				service.TicketSource = new SqlCeTicketDataSource(sfd.FileName);
				Filename = sfd.FileName;
				Settings.Default.CurrentDataFile = Filename;
				Settings.Default.Save();
				UpdateTitle();
			}
		}
	}
}
