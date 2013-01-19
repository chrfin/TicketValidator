using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Windows.Controls.Ribbon;
using TicketServer.Client.Properties;
using TicketServer.Client.TicketService;
using TicketServer.Common;
using TicketServer.Controls;
using TicketServer.Interfaces;
using TicketServer.Interfaces.BusinessLayer;
using WPFLocalizeExtension.Engine;

namespace TicketServer.Client
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : RibbonWindow
	{
		TicketServiceClient service;

		/// <summary>
		/// Initializes a new instance of the <see cref="MainWindow" /> class.
		/// </summary>
		public MainWindow()
		{
			InitializeComponent();

			PrepareLocalisation();

			ConnectService();
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

			try { ReplaceRibbonApplicationMenuButtonContent(Ribbon.ApplicationMenu); }
			catch (Exception exp) { Trace.WriteLine(exp.ToString()); }
		}

		/// <summary>
		/// Handles the Loaded event of the RibbonWindow control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="RoutedEventArgs" /> instance containing the event data.</param>
		private void RibbonWindow_Loaded(object sender, RoutedEventArgs e)
		{
			listBoxStatus.ItemsSource = new ObservableCollection<TicketEventArgs>();
			ReplaceRibbonApplicationMenuButtonContent(Ribbon.ApplicationMenu);
		}

		/// <summary>
		/// Replaces the image and down arrow of a Ribbon Application Menu Button with the button's Label text.
		/// </summary>
		/// <param name="menu">The menu whose application button should show the label text.</param>
		/// <remarks>
		/// The method assumes the specific visual tree implementation of the October 2010 version of <see cref="RibbonApplicationMenu "/>.
		/// Fortunately, since the application menu is high profile, breakage due to an version changes should be obvious.
		/// Hopefully, the native support for text will be added before the implementation breaks.
		/// </remarks>
		private void ReplaceRibbonApplicationMenuButtonContent(RibbonApplicationMenu menu)
		{
			Grid outerGrid = (Grid)VisualTreeHelper.GetChild(menu, 0);
			RibbonToggleButton toggleButton = (RibbonToggleButton)outerGrid.Children[0];
			ReplaceRibbonToggleButtonContent(toggleButton, menu.Label);

			Popup popup = (Popup)outerGrid.Children[2];
			EventHandler popupOpenedHandler = null;
			popupOpenedHandler = new EventHandler(delegate
			{
				Decorator decorator = (Decorator)popup.Child;
				Grid popupGrid = (Grid)decorator.Child;
				Canvas canvas = (Canvas)popupGrid.Children[1];
				RibbonToggleButton popupToggleButton = (RibbonToggleButton)canvas.Children[0];
				ReplaceRibbonToggleButtonContent(popupToggleButton, menu.Label);
				popup.Opened -= popupOpenedHandler;
			});
			popup.Opened += popupOpenedHandler;
		}
		private void ReplaceRibbonToggleButtonContent(RibbonToggleButton toggleButton, string text)
		{
			// Subdues the aero highlighting to that the text has better contrast.
			Grid grid = (Grid)VisualTreeHelper.GetChild(toggleButton, 0);
			Border middleBorder = (Border)grid.Children[1];
			middleBorder.Opacity = .5;

			// Replaces the images with the label text.
			StackPanel stackPanel = (StackPanel)grid.Children[2];
			UIElementCollection children = stackPanel.Children;
			children.RemoveRange(0, children.Count);
			TextBlock textBlock = new TextBlock(new Run(text));
			textBlock.Foreground = Brushes.White;
			children.Add(textBlock);
		}

		/// <summary>
		/// Handles the Click event of the buttonExit control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="RoutedEventArgs" /> instance containing the event data.</param>
		private void buttonExit_Click(object sender, RoutedEventArgs e) { Close(); }

		/// <summary>
		/// Handles the Click event of the menuItemSetting control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="RoutedEventArgs" /> instance containing the event data.</param>
		private void menuItemSetting_Click(object sender, RoutedEventArgs e)
		{
			SettingsWindow settings = new SettingsWindow();
			settings.Owner = this;
			if (settings.ShowDialog() == true)
			{
				ConnectService();
			}
		}

		/// <summary>
		/// Handles the Click event of the ribbonButtonConnect control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="RoutedEventArgs" /> instance containing the event data.</param>
		private void ribbonButtonConnect_Click(object sender, RoutedEventArgs e) { ConnectService(); }

		/// <summary>
		/// Connects the service.
		/// </summary>
		private bool ConnectService()
		{
			try
			{
				service = new TicketServiceClient("BasicHttpBinding_ITicketService", String.Format("http://{0}/tickets/ws", Settings.Default.ServiceURI));
				var status = service.GetCurrentState();
				statusBarItemInfo.Text = status.ToString();
				ticketGrid.IsEnabled = true;
				textBoxCode.Focus();
				return true;
			}
			catch (Exception exp)
			{
				statusBarItemInfo.Text = exp.Message;
				ticketGrid.IsEnabled = false;
			}

			return false;
		}

		/// <summary>
		/// Handles the KeyUp event of the textBoxCode control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="KeyEventArgs" /> instance containing the event data.</param>
		private void textBoxCode_KeyUp(object sender, KeyEventArgs e)
		{
			if(e.Key == Key.Enter)
				GetTicket();
		}

		/// <summary>
		/// Handles the Click event of the buttonGetTicket control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="RoutedEventArgs" /> instance containing the event data.</param>
		private void buttonGetTicket_Click(object sender, RoutedEventArgs e) { GetTicket(); }

		Ticket currentTicket = null;
		Thread redeemThread = null;
		/// <summary>
		/// Gets the ticket.
		/// </summary>
		private void GetTicket()
		{
			try
			{
				if (redeemThread != null)
				{
					redeemThread.Abort();
					redeemThread = null;
				}
				if (currentTicket != null)
					RedeemTicket();

				currentTicket = service.GetTicket(textBoxCode.Text);
				textBoxCode.Text = String.Empty;

				if (currentTicket != null)
				{
					textBlockError.Text = String.Empty;
					buttonRedeemTicket.IsEnabled = true;

					ITicket ticket = new MemoryTicket();
					ticket.Id = currentTicket.Id;
					ticket.Street = currentTicket.Street;
					ticket.City = currentTicket.City;
					ticket.Code = currentTicket.Code;
					ticket.EMail = currentTicket.EMail;
					ticket.IsOnlineTicket = currentTicket.IsOnlineTicket;
					ticket.IsRedeemed = currentTicket.IsRedeemed;
					ticket.Name = currentTicket.Name;
					ticket.Phone = currentTicket.Phone;
					ticket.RedeemDate = currentTicket.RedeemDate;
					ticket.Type = (Interfaces.Enums.TicketType)Enum.Parse(typeof(Interfaces.Enums.TicketType), currentTicket.Type.ToString());
					ticket.Zip = currentTicket.Zip;

					TicketEventArgs args = new TicketEventArgs(ticket);
					ObservableCollection<TicketEventArgs> list = listBoxStatus.ItemsSource as ObservableCollection<TicketEventArgs>;
					Dispatcher.Invoke((Action)delegate() { list.Insert(0, args); });

					if (Settings.Default.AutoRedeem && !ticket.IsRedeemed)
					{
						redeemThread = new Thread(new ThreadStart(delegate
						{
							uint timeLeft = Settings.Default.SecondsToAutoRedeem;
							while (timeLeft > 0)
							{
								Dispatcher.Invoke((Action)delegate { textBlockAutoRedeem.Text = String.Format(Properties.Resources.AutoRedeemIn, timeLeft); });
								Thread.Sleep(1000);
								timeLeft--;
							}
							Dispatcher.Invoke((Action)delegate { RedeemTicket(); });
							redeemThread = null;
						}));
						redeemThread.Start();
					}
					else if (ticket.IsRedeemed)
					{
						ErrorBeep();
					}
				}
				else
				{
					textBlockError.Text = Properties.Resources.TicketNotFound;
					ErrorBeep();
				}
			}
			catch
			{
				if (ConnectService())
					GetTicket();
			}
		}

		/// <summary>
		/// Signals an error via BEEP.
		/// </summary>
		/// <remarks>Christoph FINK, 19.01.2013</remarks>
		private static void ErrorBeep()
		{
			Thread beeper = new Thread(new ThreadStart(delegate
			{
				for (int i = 0; i < Settings.Default.BeepCount; ++i)
				{
					Console.Beep(1000, Convert.ToInt32(Settings.Default.BeepDuration));
					Thread.Sleep(Convert.ToInt32(Settings.Default.BeepPause));
				}
			}));
			beeper.Start();
		}

		/// <summary>
		/// Handles the Click event of the buttonRedeemTicket control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="RoutedEventArgs" /> instance containing the event data.</param>
		private void buttonRedeemTicket_Click(object sender, RoutedEventArgs e) { RedeemTicket(); }

		/// <summary>
		/// Redeems the ticket.
		/// </summary>
		private void RedeemTicket()
		{
			textBlockAutoRedeem.Text = String.Empty;
			buttonRedeemTicket.IsEnabled = false;
			if (currentTicket == null || currentTicket.IsRedeemed)
				return;

			if (redeemThread != null)
			{
				redeemThread.Abort();
				redeemThread = null;
			}

			try
			{
				RedeemResult result = service.RedeemTicket(currentTicket.Id);

				ObservableCollection<TicketEventArgs> list = listBoxStatus.ItemsSource as ObservableCollection<TicketEventArgs>;
				var item = list.First(i => i.Ticket.Id == currentTicket.Id);
				item.Ticket.IsRedeemed = result.Type == RedeemResultType.Redeemed;
				item.Ticket.RedeemDate = DateTime.Now;
				item.Result = new ClientRedeemResult() 
				{ 
					Type = (Interfaces.Enums.RedeemResultType)Enum.Parse(typeof(Interfaces.Enums.RedeemResultType), result.Type.ToString()),
					Error = result.Error 
				};

				currentTicket = null;
			}
			catch
			{
				if (ConnectService())
					RedeemTicket();
			}
		}

		/// <summary>
		/// Handles the Checked event of the checkBoxAutoFocus control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="RoutedEventArgs" /> instance containing the event data.</param>
		private void checkBoxAutoFocus_Checked(object sender, RoutedEventArgs e)
		{
			System.Timers.Timer timer = null;
			if (checkBoxAutoFocus.IsChecked == true)
			{
				if (timer != null)
					timer.Stop();

				timer = new System.Timers.Timer(Settings.Default.AutoFocusInterval * 1000);
				timer.Elapsed += (s, arg) =>
				{
					Dispatcher.Invoke((Action)delegate
					{
						if (checkBoxAutoFocus.IsChecked != true)
						{
							timer.Stop();
							timer = null;
						}

						Activate();
						textBoxCode.Focus();
					});
				};
				timer.Start();
			}
			else
			{
				timer.Stop();
				timer = null;
			}
		}
	}

	internal class ClientRedeemResult : IRedeemResult
	{
		#region IRedeemResult Members

		/// <summary>
		/// Gets or sets the type.
		/// </summary>
		/// <value>
		/// The type.
		/// </value>
		public Interfaces.Enums.RedeemResultType Type { get; set; }
		/// <summary>
		/// Gets or sets the error.
		/// </summary>
		/// <value>
		/// The error.
		/// </value>
		public string Error { get; set; }

		#endregion
	}
}
