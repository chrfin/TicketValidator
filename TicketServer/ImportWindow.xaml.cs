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
using TicketServer.Interfaces.DAL;
using System.IO;
using Microsoft.WindowsAPICodePack.Dialogs;
using TicketServer.Interfaces.Enums;
using System.Threading;

namespace TicketServer
{
	/// <summary>
	/// Interaction logic for ImportWindow.xaml
	/// </summary>
	public partial class ImportWindow : Window
	{
		private string FirstLine;
		private List<string> DemoLines;

		private List<ComboBox> ColumnBoxes = new List<ComboBox>();

		/// <summary>
		/// Gets or sets the ticket source.
		/// </summary>
		/// <value>
		/// The ticket source.
		/// </value>
		public ITicketDataSource TicketSource { get; set; }

		/// <summary>
		/// Initializes a new instance of the <see cref="ImportWindow"/> class.
		/// </summary>
		/// <param name="ticketSource">The ticket source to import to.</param>
		public ImportWindow(ITicketDataSource ticketSource)
		{
			TicketSource = ticketSource;

			InitializeComponent();

			ColumnBoxes.Add(comboBoxCodeColumn);
			ColumnBoxes.Add(comboBoxNameColumn);
			ColumnBoxes.Add(comboBoxStreetColumn);
			ColumnBoxes.Add(comboBoxZipColumn);
			ColumnBoxes.Add(comboBoxCityColumn);
			ColumnBoxes.Add(comboBoxPhoneColumn);
			ColumnBoxes.Add(comboBoxMailColumn);

			comboBoxCodeColumn.Tag = new GridViewColumn() { Header = Properties.Import.FieldCode };
			comboBoxNameColumn.Tag = new GridViewColumn() { Header = Properties.Import.FieldName };
			comboBoxStreetColumn.Tag = new GridViewColumn() { Header = Properties.Import.FieldStreet };
			comboBoxZipColumn.Tag = new GridViewColumn() { Header = Properties.Import.FieldZip };
			comboBoxCityColumn.Tag = new GridViewColumn() { Header = Properties.Import.FieldCity };
			comboBoxPhoneColumn.Tag = new GridViewColumn() { Header = Properties.Import.FieldPhone };
			comboBoxMailColumn.Tag = new GridViewColumn() { Header = Properties.Import.FieldMail };

			listViewPreview.View = new GridView();
			ColumnBoxes.ForEach(cb => (listViewPreview.View as GridView).Columns.Add(cb.Tag as GridViewColumn));
		}

		/// <summary>
		/// Enables the column selection and import controls.
		/// </summary>
		/// <param name="enable">if set to <c>true</c> [enable].</param>
		protected void EnableControls(bool enable = true)
		{
			comboBoxSeparator.IsEnabled = enable;
			ColumnBoxes.ForEach(cb => cb.IsEnabled = enable);
			buttonImport.IsEnabled = enable;
		}

		/// <summary>
		/// Updates the file.
		/// </summary>
		protected void UpdateFile()
		{
			bool exists = File.Exists(textBoxFile.Text);
			EnableControls(exists);
			if (exists)
			{
				using (TextReader reader = File.OpenText(textBoxFile.Text))
				{
					FirstLine = reader.ReadLine();
					DemoLines = new List<string>();
					for (int i = 0; i < 5; ++i)
						DemoLines.Add(reader.ReadLine());
					reader.Close();

					UpdateColumns(comboBoxSeparator.Text);
				}
			}
			else
			{
				listViewPreview.ItemsSource = null;
				ColumnBoxes.ForEach(cb => cb.ItemsSource = null);
			}
		}

		/// <summary>
		/// Updates the columns.
		/// </summary>
		/// <param name="separator">The separator.</param>
		private void UpdateColumns(string separator)
		{
			if (FirstLine != null)
			{
				string[] columns = FirstLine.Split(new string[] { separator == "\\t" ? "\t" : separator }, StringSplitOptions.None);
				List<string> columnList = new List<string>(columns);
				ColumnBoxes.ForEach(cb => cb.ItemsSource = columnList);

				listViewPreview.ItemsSource = null;
			}
		}

		/// <summary>
		/// Handles the TextChanged event of the textBoxFile control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.Controls.TextChangedEventArgs"/> instance containing the event data.</param>
		private void textBoxFile_TextChanged(object sender, TextChangedEventArgs e)
		{
			UpdateFile();
		}

		/// <summary>
		/// Handles the Click event of the buttonBrowse control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonBrowse_Click(object sender, RoutedEventArgs e)
		{
			CommonOpenFileDialog ofd = new CommonOpenFileDialog();
			ofd.Filters.Add(new CommonFileDialogFilter(Properties.Import.CsvFilterName, "*.csv"));
			ofd.Filters.Add(new CommonFileDialogFilter(Properties.Import.AllFilterName, "*.*"));
			if (ofd.ShowDialog() == CommonFileDialogResult.Ok)
				textBoxFile.Text = ofd.FileName;
		}

		/// <summary>
		/// Handles the TextChanged event of the comboBoxSeparator control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.Controls.TextChangedEventArgs"/> instance containing the event data.</param>
		private void comboBoxSeparator_TextChanged(object sender, TextChangedEventArgs e) { UpdateColumns(comboBoxSeparator.Text); }

		/// <summary>
		/// Handles the SelectionChanged event of the comboBox-Column controls.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.Controls.SelectionChangedEventArgs"/> instance containing the event data.</param>
		private void comboBoxColumn_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			List<string[]> rows = new List<string[]>();
			DemoLines.ForEach(l => rows.Add(SplitLine(l, comboBoxSeparator.Text).ToArray()));
			listViewPreview.ItemsSource = rows;

			ColumnBoxes.ForEach(delegate(ComboBox cb)
			{
				GridViewColumn column = cb.Tag as GridViewColumn;
				column.DisplayMemberBinding = new Binding("[-1]") { TargetNullValue = string.Empty };
				if (cb == sender)
				{
					if (e.AddedItems.Count > 0)
					{
						string item = e.AddedItems[0].ToString();
						if (item.Length > 0)
							column.DisplayMemberBinding = new Binding("[" + cb.SelectedIndex + "]");
					}
				}
				else
				{
					if (cb.Text.Length > 0)
						column.DisplayMemberBinding = new Binding("[" + cb.SelectedIndex + "]");
				}

				if (double.IsNaN(column.Width))
					column.Width = column.ActualWidth;
				column.Width = double.NaN;
			});
		}

		/// <summary>
		/// Splits the line into its columns.
		/// </summary>
		/// <param name="row">The row.</param>
		/// <returns></returns>
		private List<string> SplitLine(string row, string separator)
		{
			List<string> rowValues = new List<string>();
			List<string> parts = new List<string>(row.Split(new string[] { separator == "\\t" ? "\t" : separator },
				StringSplitOptions.None));
			parts.ForEach(s => rowValues.Add(s.Trim(new char[] { '"' })));
			return rowValues;
		}

		/// <summary>
		/// Handles the Click event of the buttonImport control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.Windows.RoutedEventArgs"/> instance containing the event data.</param>
		private void buttonImport_Click(object sender, RoutedEventArgs e)
		{
			string file = textBoxFile.Text;
			bool hasHeader= checkBoxHeader.IsChecked.HasValue && checkBoxHeader.IsChecked.Value;
			string separator = comboBoxSeparator.Text;
			
			Thread importThread = new Thread(new ThreadStart(delegate()
			{
				Dispatcher.Invoke((Action)delegate()
				{
					textBlockStatus.Text = Properties.Import.ImportStatusReadingFile;
					progressBarStatus.Value = 0;
					progressBarStatus.Visibility = System.Windows.Visibility.Visible;
					busyIndicator.IsBusy = true;
				});

				List<string> lines;
				using (TextReader reader = File.OpenText(file))
				{
					if (hasHeader)
						reader.ReadLine();
					string content = reader.ReadToEnd();
					lines = new List<string>(content.Split(new string[] { content.Contains("\r\n") ? "\r\n" : "\n" }, StringSplitOptions.RemoveEmptyEntries));
					reader.Close();
				}

				int i = 0;
				foreach (string row in lines)
				{
					Dispatcher.Invoke((Action)delegate() 
					{
						textBlockStatus.Text = String.Format(Properties.Import.ImportStatusImporting, ++i, lines.Count);
						progressBarStatus.Value = (i * 100.0) / lines.Count;
					});
					List<string> rowValues = SplitLine(row, separator);

					ImportTicket ticket = new ImportTicket();
					Dispatcher.Invoke((Action)delegate()
					{
						ticket.IsOnlineTicket = (comboBoxTicketMode.SelectedItem as IsOnlineComboBoxItem).IsOnlineTicket;
						ticket.Type = (comboBoxTicketType.SelectedItem as TicketTypeComboBoxItem).TicketType;
						ticket.Code = comboBoxCodeColumn.Text.Length > 0 ? rowValues[comboBoxCodeColumn.SelectedIndex] : null;
						ticket.Name = comboBoxNameColumn.Text.Length > 0 ? rowValues[comboBoxNameColumn.SelectedIndex] : null;
						ticket.Street = comboBoxStreetColumn.Text.Length > 0 ? rowValues[comboBoxStreetColumn.SelectedIndex] : null;
						ticket.Zip = comboBoxZipColumn.Text.Length > 0 ? rowValues[comboBoxZipColumn.SelectedIndex] : null;
						ticket.City = comboBoxCityColumn.Text.Length > 0 ? rowValues[comboBoxCityColumn.SelectedIndex] : null;
						ticket.Phone = comboBoxPhoneColumn.Text.Length > 0 ? rowValues[comboBoxPhoneColumn.SelectedIndex] : null;
						ticket.EMail = comboBoxMailColumn.Text.Length > 0 ? rowValues[comboBoxMailColumn.SelectedIndex] : null;
					});
					TicketSource.AddTicket(ticket);
				}

				Dispatcher.Invoke((Action)delegate()
				{
					textBlockStatus.Text = Properties.Import.ImportStatusReady;
					progressBarStatus.Visibility = System.Windows.Visibility.Hidden;
					busyIndicator.IsBusy = false;
				});
			}));
			importThread.Start();
		}

		/// <summary>
		/// Handles the Closing event of the Window control.
		/// </summary>
		/// <param name="sender">The source of the event.</param>
		/// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			if (busyIndicator.IsBusy)
				e.Cancel = true;
		}
	}

	/// <summary>
	/// Item for "IsOnline" selection
	/// </summary>
	internal class IsOnlineComboBoxItem : ComboBoxItem
	{
		/// <summary>
		/// Gets or sets a value indicating whether this instance is online ticket.
		/// </summary>
		/// <value>
		/// 	<c>true</c> if this instance is online ticket; otherwise, <c>false</c>.
		/// </value>
		public bool IsOnlineTicket { get; set; }
	}

	/// <summary>
	/// Item for "TicketType" selection.
	/// </summary>
	internal class TicketTypeComboBoxItem : ComboBoxItem
	{
		/// <summary>
		/// Gets or sets the type of the ticket.
		/// </summary>
		/// <value>
		/// The type of the ticket.
		/// </value>
		public TicketType TicketType { get; set; }
	}
}
