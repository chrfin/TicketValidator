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
using TicketServer.Interfaces.DAL;
using System.ComponentModel;
using TicketServer.Interfaces;
using TicketServer.Interfaces.Enums;

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
		/// Gets the ticket source.
		/// </summary>
		public ITicketDataSource TicketSource { get { return service.TicketSource; } }

		/// <summary>
		/// Gets or sets a value indicating whether this instance is busy.
		/// </summary>
		/// <value>
		///   <c>true</c> if this instance is busy; otherwise, <c>false</c>.
		/// </value>
		public bool IsBusy
		{
			get
			{
				bool busy = false;
				busyIndicator.Dispatcher.Invoke((Action)delegate() { busy = busyIndicator.IsBusy; });
				return busy;
			}
			set
			{
				busyIndicator.Dispatcher.Invoke((Action)delegate() { busyIndicator.IsBusy = value; });
			}
		}

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
				IsBusy = true;

				service = new TicketService(new SqlCeTicketDataSource(Filename));
				service.TicketRequested += new EventHandler(service_TicketRequested);
				service.TicketRedeemed += new EventHandler(service_TicketRedeemed);

				host = new ServiceHost(service);
				host.Open();

				databaseControlMain.Dispatcher.Invoke((Action)delegate() { databaseControlMain.TicketSource = service.TicketSource; });
				statusBarItemInfo.Dispatcher.Invoke((Action)delegate() { statusBarItemInfo.Text = Properties.Resources.MainStatusReady; });

				UpdateStatus();
				IsBusy = false;
			}));
			hostThread.Start();
			UpdateRecentFiles();
		}

		/// <summary>
		/// Updates the status bar values.
		/// </summary>
		private void UpdateStatus()
		{
			statusBarItemTicketsValue.Dispatcher.Invoke((Action)delegate()
			{
				statusBarItemTicketsValue.Text = String.Format(Properties.Resources.MainStatusTicketsValue, 
					TicketSource.RedeemedCount, TicketSource.TicketCount);
			});
		}

		/// <summary>
		/// Handles the TicketRedeemed event of the service control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		protected void service_TicketRedeemed(object sender, EventArgs e)
		{
			textBoxLog.Dispatcher.Invoke((Action)delegate()
			{
				textBoxLog.Text += string.Format("Ticket redeemed ({0}): {1}", (e as TicketEventArgs).Client, (e as TicketEventArgs).Ticket.Code) + Environment.NewLine;
			});
			UpdateStatus();
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
			TaskDialog dialog = new TaskDialog();
			dialog.Cancelable = true;
			dialog.Caption = Properties.Resources.CloseWarningCaption;
			dialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
			dialog.Icon = TaskDialogStandardIcon.None;
			dialog.StartupLocation = TaskDialogStartupLocation.CenterOwner;
			dialog.Text = Properties.Resources.CloseWarningText;

			TaskDialogCommandLink buttonYes = new TaskDialogCommandLink("buttonYes", Properties.Resources.CloseWarningYes);
			buttonYes.Click += new EventHandler(delegate(object snd, EventArgs eventArgs)
			{
				host.Close();
				dialog.Close();
			});
			TaskDialogCommandLink buttonNo = new TaskDialogCommandLink("buttonNo", Properties.Resources.CloseWarningNo);
			buttonNo.Click += new EventHandler(delegate(object snd, EventArgs eventArgs) { dialog.Close(); e.Cancel = true; });

			dialog.Controls.Add(buttonYes);
			dialog.Controls.Add(buttonNo);

			dialog.Show();
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
			UpdateStatus();
		}

		/// <summary>
		/// Handles the Click event of the buttonClear control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonClear_Click(object sender, RoutedEventArgs e) { service.TicketSource.Clear(); UpdateStatus(); }
		/// <summary>
		/// Handles the Click event of the buttonReset control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonReset_Click(object sender, RoutedEventArgs e) { service.TicketSource.Reset(); UpdateStatus(); }

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

				OpenFile(sfd.FileName);
			}
		}

		/// <summary>
		/// Handles the SelectionChanged event of the tabControlMain control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.Controls.SelectionChangedEventArgs"/> instance containing the event data.</param>
		private void tabControlMain_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			tabGroupDatabase.Visibility = e.AddedItems.Contains(tabDatabase) || tabDatabase.IsSelected ? 
				System.Windows.Visibility.Visible : System.Windows.Visibility.Hidden;
		}

		/// <summary>
		/// Updates the filter.
		/// </summary>
		private void UpdateFilter()
		{
			if (databaseControlMain == null || databaseControlMain.TicketSource == null)
				return;

			ICollectionView view = CollectionViewSource.GetDefaultView(databaseControlMain.TicketSource.Tickets);
			if (view != null)
			{
				Predicate<object> filter = 
					new Predicate<object>(delegate(object o)
					{
						if (!(o is ITicket))
							return false;
						ITicket ticket = o as ITicket;

						bool show = true;

						show = radioButtonModeAll.IsChecked.Value ? show : 
							(radioButtonModeOnline.IsChecked.Value ? ticket.IsOnlineTicket : !ticket.IsOnlineTicket);

						if (show)
							show = radioButtonTypeAll.IsChecked.Value ? show :
								(radioButtonTypeFree.IsChecked.Value ? ticket.Type == TicketType.Free :
								(radioButtonTypeNormal.IsChecked.Value ? ticket.Type == TicketType.Normal : ticket.Type == TicketType.Special));

						return show;
					});
				view.Filter = filter;
			}
		}

		/// <summary>
		/// Handles the Checked event of the radioButtonMode control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void radioButtonMode_Checked(object sender, RoutedEventArgs e) { UpdateFilter(); }
		/// <summary>
		/// Handles the Checked event of the radioButtonType control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void radioButtonType_Checked(object sender, RoutedEventArgs e) { UpdateFilter(); }

		/// <summary>
		/// Handles the Click event of the buttonOpen control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonOpen_Click(object sender, RoutedEventArgs e)
		{
			CommonOpenFileDialog ofd = new CommonOpenFileDialog();
			ofd.Filters.Add(new CommonFileDialogFilter(Properties.Resources.FileFilterText, Properties.Resources.FileFilterExtension));
			ofd.DefaultExtension = Properties.Resources.FileFilterExtension;
			if (ofd.ShowDialog() == CommonFileDialogResult.Ok)
				OpenFile(ofd.FileName);
		}

		/// <summary>
		/// Opens the file.
		/// </summary>
		/// <param name="filename">The filename.</param>
		private void OpenFile(string filename)
		{
			if (filename.StartsWith("./"))
				filename = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, filename.Substring(2));

			service.TicketSource = new SqlCeTicketDataSource(filename);
			Filename = filename;
			Settings.Default.CurrentDataFile = Filename;
			Settings.Default.Save();
			UpdateTitle();
			UpdateStatus();

			string[] recentFiles = Settings.Default.RecentFiles.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
			if (!recentFiles.Contains(filename))
			{
				Settings.Default.RecentFiles += ";" + filename;
				Settings.Default.Save();
				UpdateRecentFiles();
			}
		}

		/// <summary>
		/// Updates the recent files.
		/// </summary>
		private void UpdateRecentFiles()
		{
			listRecentFiles.ItemsSource = Settings.Default.RecentFiles.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
		}

		/// <summary>
		/// Handles the Click event of the ribbonApplicationMenuItemRecentFile control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void ribbonApplicationMenuItemRecentFile_Click(object sender, RoutedEventArgs e)
		{
			OpenFile((sender as RibbonApplicationMenuItem).Tag as string);
		}
	}
}
