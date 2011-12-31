using System;
using System.Linq;
using System.Collections.Generic;
using System.Windows.Forms;

namespace TicketValidator
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [MTAThread]
        static void Main()
        {
            mainForm form = new mainForm();
            try
            {
                Application.Run(form);
            }
            finally { form.CloseOpenConnections(); }
        }
    }
}