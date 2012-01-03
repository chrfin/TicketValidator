using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using TicketValidator.TicketServiceReference;
using System.Net;
using System.Threading;
using TicketValidator.Properties;

namespace TicketValidator
{
    /// <summary>
    /// This form can select and test a service URI.
    /// </summary>
    public partial class ServiceSelection : Form
    {
        /// <summary>
        /// Gets or sets the service URI.
        /// </summary>
        /// <value>
        /// The service URI.
        /// </value>
        public string ServiceUri
        {
            get
            {
                return comboBoxUri.Text;
            }
            set
            {
                comboBoxUri.Text = value;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ServiceSelection"/> class.
        /// </summary>
        public ServiceSelection()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Handles the Click event of the buttonTest control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonTest_Click(object sender, EventArgs e)
        {
            labelTest.Text = Resources.Connecting;
            TicketService testService = new TicketService();
            testService.Url = ServiceUri;
            Application.DoEvents();

            try
            {
                ServiceStatus status = testService.GetServiceState();
                labelTest.Text = status.ToString();
            }
            catch (WebException exp)
            {
                labelTest.Text = exp.Status.ToString();
            }
        }

        /// <summary>
        /// Handles the Click event of the buttonOk control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonOk_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        /// <summary>
        /// Handles the TextChanged event of the comboBoxUri control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void comboBoxUri_TextChanged(object sender, EventArgs e)
        {
            labelTest.Text = Resources.NotConnected;
        }

        /// <summary>
        /// Handles the Click event of the buttonCancel control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void buttonCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }
    }
}