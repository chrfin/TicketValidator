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
		}

		/// <summary>
		/// Enables the column selection and import controls.
		/// </summary>
		/// <param name="enable">if set to <c>true</c> [enable].</param>
		protected void EnableControls(bool enable = true)
		{
			comboBoxSeparator.IsEnabled = enable;
			ColumnBoxes.ForEach(cb => cb.IsEnabled = enable);
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

					UpdateColumns(comboBoxSeparator.Text);
				}
			}
			else
			{
				listViewPreview.ItemsSource = null;
				listViewPreview.View = null;
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
				listViewPreview.View = null;
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
			ofd.Filters.Add(new CommonFileDialogFilter(Properties.Resources.CsvFilterName, "*.csv"));
			ofd.Filters.Add(new CommonFileDialogFilter(Properties.Resources.AllFilterName, "*.*"));
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
			GridView view = new GridView();
			ColumnBoxes.ForEach(delegate(ComboBox cb)
			{
				if (cb == sender)
				{
					if (e.AddedItems.Count > 0)
					{
						string item = e.AddedItems[0].ToString();
						if (item.Length > 0)
						{
							int index = (cb.ItemsSource as List<string>).IndexOf(item);
							view.Columns.Add(new GridViewColumn() { Header = item, DisplayMemberBinding = new Binding("[" + index + "]") });
						}
					}
				}
				else
				{
					if (cb.Text.Length > 0)
					{
						int index = (cb.ItemsSource as List<string>).IndexOf(cb.Text);
						view.Columns.Add(new GridViewColumn() { Header = cb.Text, DisplayMemberBinding = new Binding("[" + index + "]") });
					}
				}
			});
			listViewPreview.View = view;
			
			List<string[]> rows = new List<string[]>();
			foreach (string row in DemoLines)
				rows.Add(row.Split(new string[] { comboBoxSeparator.Text == "\\t" ? "\t" : comboBoxSeparator.Text }, StringSplitOptions.None));
			listViewPreview.ItemsSource = rows;
		}
	}
}
