using System;
using System.Linq;
using System.Collections.Generic;
using System.Windows.Forms;

namespace TicketValidator.SymbolScanner
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [MTAThread]
        static void Main()
        {
            MainForm form = new MainForm(new SymbolScanner());
            try
            {
                Application.Run(form);
            }
            finally { form.CloseOpenConnections(true); }
        }
    }
}