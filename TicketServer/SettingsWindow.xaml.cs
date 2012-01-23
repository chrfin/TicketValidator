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

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for SettingsWindow.xaml
	/// </summary>
	public partial class SettingsWindow : Window
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SettingsWindow"/> class.
		/// </summary>
		public SettingsWindow()
		{
			InitializeComponent();
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
			//SAVE
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
	}
}
