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
using TicketServer.Interfaces.Classes;
using System.Windows.Interop;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : RibbonWindow
	{
		ServiceHost host;
		Thread hostThread;

		/// <summary>
		/// Gets or sets the service.
		/// </summary>
		/// <value>
		/// The service.
		/// </value>
		public TicketService Service
		{
			get { return (TicketService)GetValue(ServiceProperty); }
			set { SetValue(ServiceProperty, value); }
		}
		// Using a DependencyProperty as the backing store for Service.  This enables animation, styling, binding, etc...
		public static readonly DependencyProperty ServiceProperty = DependencyProperty.Register("Service", typeof(TicketService), typeof(MainWindow));

		/// <summary>
		/// Gets or sets the filename.
		/// </summary>
		/// <value>
		/// The filename.
		/// </value>
		protected string Filename { get; set; }

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
			listBoxStatus.ItemsSource = new SafeObservable<TicketEventArgs>();
			hostThread = new Thread(new ThreadStart(delegate()
			{
				IsBusy = true;

				ITicketDataSource source = new SqlCeTicketDataSource(Filename);
				source.SpecialTicketsString = Settings.Default.SpecialTicketsString;
				source.PropertyChanged += new PropertyChangedEventHandler(source_PropertyChanged);

				TicketService service = new TicketService(source);
				service.TicketRequested += new EventHandler(service_TicketRequested);
				service.TicketRedeemed += new EventHandler(service_TicketRedeemed);

				Dispatcher.Invoke((Action)delegate() { Service = service; });

				host = new ServiceHost(service);
				host.Open();

				databaseControlMain.Dispatcher.Invoke((Action)delegate() { databaseControlMain.TicketSource = service.TicketSource; });
				statusBarItemInfo.Dispatcher.Invoke((Action)delegate() { statusBarItemInfo.Text = Properties.Resources.MainStatusReady; });

				SafeObservable<ObservablePoint<DateTime, int>> dataTotal = BuildStatistic(StatisticMode.Total);
				SafeObservable<ObservablePoint<DateTime, int>> dataPerUnit = BuildStatistic(StatisticMode.PerUnit);
				lineSeriesStatisticTotal.Dispatcher.Invoke((Action)delegate()
				{
					lineSeriesStatisticTotal.ItemsSource = dataTotal;
					lineSeriesStatisticTotal.IndependentValuePath = "X";
					lineSeriesStatisticTotal.DependentValuePath = "Y";

					areaSeriesStatisticPerUnit.ItemsSource = dataPerUnit;
					areaSeriesStatisticPerUnit.IndependentValuePath = "X";
					areaSeriesStatisticPerUnit.DependentValuePath = "Y";
				});

				IsBusy = false;
			}));
			hostThread.Start();
			UpdateRecentFiles();

		}

		/// <summary>
		/// Builds the statistic.
		/// </summary>
		/// <param name="mode">The mode.</param>
		/// <returns></returns>
		private SafeObservable<ObservablePoint<DateTime, int>> BuildStatistic(StatisticMode mode)
		{
			TicketService service = null;
			Dispatcher.Invoke((Action)delegate() { service = Service; });

			if (service == null)
				return null;

			SafeObservable<ObservablePoint<DateTime, int>> data = new SafeObservable<ObservablePoint<DateTime, int>>();

			SafeObservable<ITicket> tickets = service.TicketSource.ActiveTickets;

			DateTime firstRedeemed = (from t in tickets
									  where t.IsRedeemed && t.RedeemDate.HasValue
									  orderby t.RedeemDate ascending
									  select t).First().RedeemDate.Value;
			int offset = 0;
			int interval = 60;
			Dispatcher.Invoke((Action)delegate() { interval = Convert.ToInt32((comboBoxStatisticResolution.SelectedItem as ComboBoxItem).Tag); });
			DateTime time = new DateTime();
			do
			{
				DateTime last = time;
				time = (new DateTime(firstRedeemed.Year, firstRedeemed.Month, firstRedeemed.Day, firstRedeemed.Hour, 0, 0)).AddMinutes(interval * offset++);
				int ticketsRedeemed;
				switch (mode)
				{
					case StatisticMode.PerUnit:
						ticketsRedeemed = GetRedeemdCount(tickets, last, time);
						break;
					case StatisticMode.Total:
					default:
						ticketsRedeemed = GetRedeemdCount(tickets, time);
						break;
				}
				data.Add(new ObservablePoint<DateTime, int>(time, ticketsRedeemed));
			}
			while (time < DateTime.Now);

			return data;
		}

		/// <summary>
		/// Gets the redeemd count.
		/// </summary>
		/// <param name="tickets">The tickets.</param>
		/// <param name="until">The until.</param>
		/// <returns></returns>
		private static int GetRedeemdCount(IEnumerable<ITicket> tickets, DateTime until)
		{
			return (from t in tickets
					where t.IsRedeemed && t.RedeemDate.HasValue && t.RedeemDate.Value <= until
					select t).Count();
		}
		/// <summary>
		/// Gets the redeemd count.
		/// </summary>
		/// <param name="tickets">The tickets.</param>
		/// <param name="begin">The begin.</param>
		/// <param name="end">The end.</param>
		/// <returns></returns>
		private static int GetRedeemdCount(IEnumerable<ITicket> tickets, DateTime begin, DateTime end)
		{
			return (from t in tickets
					where t.IsRedeemed && t.RedeemDate.HasValue && t.RedeemDate.Value > begin && t.RedeemDate.Value <= end
					select t).Count();
		}

		/// <summary>
		/// Handles the PropertyChanged event of the source control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.ComponentModel.PropertyChangedEventArgs"/> instance containing the event data.</param>
		protected void source_PropertyChanged(object sender, PropertyChangedEventArgs e) { UpdateStatus(); }

		/// <summary>
		/// Updates the status bar values.
		/// </summary>
		private void UpdateStatus()
		{
			Dispatcher.Invoke((Action)delegate()
			{
				foreach (ObservablePoint<DateTime, int> point in lineSeriesStatisticTotal.ItemsSource as SafeObservable<ObservablePoint<DateTime, int>>)
				{
					point.Y = GetRedeemdCount(Service.TicketSource.ActiveTickets, point.X);
				}

				DateTime last = new DateTime();
				foreach (ObservablePoint<DateTime, int> point in areaSeriesStatisticPerUnit.ItemsSource as SafeObservable<ObservablePoint<DateTime, int>>)
				{
					point.Y = GetRedeemdCount(Service.TicketSource.ActiveTickets, last, point.X);
					last = point.X;
				}
			});
		}

		/// <summary>
		/// Handles the TicketRedeemed event of the service control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		protected void service_TicketRedeemed(object sender, EventArgs e)
		{
			TicketEventArgs args = e as TicketEventArgs;
			SafeObservable<TicketEventArgs> list = listBoxStatus.ItemsSource as SafeObservable<TicketEventArgs>;

			if (list.FirstOrDefault(a => a.Ticket.Id == args.Ticket.Id) == null)
				list.Insert(0, e as TicketEventArgs);
			else
			    UpdateStatusItem(args);
		}
		/// <summary>
		/// Handles the TicketRequested event of the service control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
		protected void service_TicketRequested(object sender, EventArgs e)
		{
			TicketEventArgs args = e as TicketEventArgs;
			SafeObservable<TicketEventArgs> list = listBoxStatus.ItemsSource as SafeObservable<TicketEventArgs>;

			if (list.FirstOrDefault(a => a.Ticket.Id == args.Ticket.Id) == null)
				list.Insert(0, e as TicketEventArgs);
			else
				UpdateStatusItem(args);
		}
		/// <summary>
		/// Updates the status item.
		/// </summary>
		/// <param name="args">The <see cref="TicketServer.Common.TicketEventArgs"/> instance containing the event data.</param>
		private void UpdateStatusItem(TicketEventArgs args)
		{
			TicketEventArgs e = (listBoxStatus.ItemsSource as SafeObservable<TicketEventArgs>).First(a => a.Ticket.Id == args.Ticket.Id);
			e.Result = args.Result;
			return;
		}

		/// <summary>
		/// Handles the Closing event of the Window control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			TaskDialog dialog = new TaskDialog();
			dialog.OwnerWindowHandle = new WindowInteropHelper(this).Handle;
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
			ImportWindow import = new ImportWindow(Service.TicketSource);
			import.Owner = this;
			import.ShowDialog();
			UpdateStatus();
		}

		/// <summary>
		/// Handles the Click event of the buttonClear control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonClear_Click(object sender, RoutedEventArgs e)
		{
			TaskDialog dialog = new TaskDialog();
			dialog.OwnerWindowHandle = new WindowInteropHelper(Window.GetWindow(this)).Handle;
			dialog.Cancelable = true;
			dialog.Caption = Properties.Resources.ClearDatabaseCaption;
			dialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
			dialog.Icon = TaskDialogStandardIcon.Warning;
			dialog.StartupLocation = TaskDialogStartupLocation.CenterOwner;
			dialog.Text = Properties.Resources.ClearDatabaseText;

			TaskDialogCommandLink buttonYes = new TaskDialogCommandLink("buttonYes", Properties.Resources.ClearDatabaseYes);
			buttonYes.Click += new EventHandler(delegate(object snd, EventArgs eventArgs)
			{
				Service.TicketSource.Clear();
				listBoxStatus.ItemsSource = new SafeObservable<TicketEventArgs>();
				lineSeriesStatisticTotal.ItemsSource = BuildStatistic(StatisticMode.Total);
				areaSeriesStatisticPerUnit.ItemsSource = BuildStatistic(StatisticMode.PerUnit);
				UpdateStatus();

				dialog.Close();
			});
			TaskDialogCommandLink buttonNo = new TaskDialogCommandLink("buttonNo", Properties.Resources.ClearDatabaseNo);
			buttonNo.Click += new EventHandler(delegate(object snd, EventArgs eventArgs) { dialog.Close(); });

			dialog.Controls.Add(buttonYes);
			dialog.Controls.Add(buttonNo);

			dialog.Show();
		}
		/// <summary>
		/// Handles the Click event of the buttonReset control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonReset_Click(object sender, RoutedEventArgs e)
		{
			TaskDialog dialog = new TaskDialog();
			dialog.OwnerWindowHandle = new WindowInteropHelper(Window.GetWindow(this)).Handle;
			dialog.Cancelable = true;
			dialog.Caption = Properties.Resources.ResetDatabaseCaption;
			dialog.ExpansionMode = TaskDialogExpandedDetailsLocation.Hide;
			dialog.Icon = TaskDialogStandardIcon.Warning;
			dialog.StartupLocation = TaskDialogStartupLocation.CenterOwner;
			dialog.Text = Properties.Resources.ResetDatabaseText;

			TaskDialogCommandLink buttonYes = new TaskDialogCommandLink("buttonYes", Properties.Resources.ResetDatabaseYes);
			buttonYes.Click += new EventHandler(delegate(object snd, EventArgs eventArgs)
			{
				Service.TicketSource.Reset();
				listBoxStatus.ItemsSource = new SafeObservable<TicketEventArgs>();
				lineSeriesStatisticTotal.ItemsSource = BuildStatistic(StatisticMode.Total);
				areaSeriesStatisticPerUnit.ItemsSource = BuildStatistic(StatisticMode.PerUnit);
				UpdateStatus();

				dialog.Close();
			});
			TaskDialogCommandLink buttonNo = new TaskDialogCommandLink("buttonNo", Properties.Resources.ResetDatabaseNo);
			buttonNo.Click += new EventHandler(delegate(object snd, EventArgs eventArgs) { dialog.Close(); });

			dialog.Controls.Add(buttonYes);
			dialog.Controls.Add(buttonNo);

			dialog.Show();
		}

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
			tabGroupDatabase.Visibility = e.AddedItems.Contains(tabDatabase) || tabDatabase.IsSelected ? Visibility.Visible : Visibility.Hidden;
			ribbonGroupStatus.Visibility = e.AddedItems.Contains(tabStatus) || tabStatus.IsSelected ? Visibility.Visible : Visibility.Hidden;
		}

		/// <summary>
		/// Updates the filter.
		/// </summary>
		private void UpdateFilter()
		{
			if (databaseControlMain == null || databaseControlMain.TicketSource == null)
				return;

			ICollectionView view = CollectionViewSource.GetDefaultView(databaseControlMain.TicketSource.AllTickets);
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

						if (show)
							show = radioButtonRedeemedAll.IsChecked.Value ? show :
								(radioButtonRedeemedYes.IsChecked.Value ? ticket.IsRedeemed : !ticket.IsRedeemed);

						return show;
					});
				view.Filter = filter;
			}
		}

		/// <summary>
		/// Handles the Checked event of the radioButton controls.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void radioButtonFilter_Checked(object sender, RoutedEventArgs e) { UpdateFilter(); }

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

			Service.TicketSource = new SqlCeTicketDataSource(filename);
			Service.TicketSource.SpecialTicketsString = Settings.Default.SpecialTicketsString;
			Filename = filename;
			Settings.Default.CurrentDataFile = Filename;
			Settings.Default.Save();
			databaseControlMain.Dispatcher.Invoke((Action)delegate() { databaseControlMain.TicketSource = Service.TicketSource; });
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
		private void ribbonApplicationMenuItemRecentFile_Click(object sender, RoutedEventArgs e) { OpenFile((sender as RibbonApplicationMenuItem).Tag as string); }

		/// <summary>
		/// Handles the MouseDoubleClick event of the listBoxStatus control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.Input.MouseButtonEventArgs"/> instance containing the event data.</param>
		private void listBoxStatus_MouseDoubleClick(object sender, MouseButtonEventArgs e)
		{
			if (listBoxStatus.SelectedItem is TicketEventArgs)
			{
				databaseControlMain.SelectedItem = (listBoxStatus.SelectedItem as TicketEventArgs).Ticket;
				tabDatabase.IsSelected = true;
			}
		}

		/// <summary>
		/// Handles the SelectionChanged event of the comboBoxStatisticResolution control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.Controls.SelectionChangedEventArgs"/> instance containing the event data.</param>
		private void comboBoxStatisticResolution_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			lineSeriesStatisticTotal.ItemsSource = BuildStatistic(StatisticMode.Total);
			areaSeriesStatisticPerUnit.ItemsSource = BuildStatistic(StatisticMode.PerUnit);
		}

		/// <summary>
		/// Handles the Click event of the buttonSettings control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonSettings_Click(object sender, RoutedEventArgs e)
		{
			SettingsWindow settings = new SettingsWindow();
			settings.Owner = this;
			settings.ShowDialog();

			Service.TicketSource.SpecialTicketsString = Settings.Default.SpecialTicketsString;
		}

		/// <summary>
		/// Handles the Click event of the buttonStatusClear control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonStatusClear_Click(object sender, RoutedEventArgs e)
		{
			listBoxStatus.ItemsSource = new SafeObservable<TicketEventArgs>();
		}
	}
}
