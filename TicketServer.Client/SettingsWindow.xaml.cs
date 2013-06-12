﻿using System;
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
using Microsoft.Windows.Controls;
using System.Security;

using System.Net;
using System.IO;
using Microsoft.WindowsAPICodePack.Dialogs;
using System.Windows.Interop;
using System.Threading;
using TicketServer.Client.Properties;

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
	}
}