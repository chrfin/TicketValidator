using System;
using System.Linq;
using System.Collections.Generic;
using System.Windows.Forms;
using TicketValidator.Interfaces;

namespace TicketValidator.Denso
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [MTAThread]
        static void Main()
        {
            IScanner scanner = new DensoScanner();
            MainForm form = new MainForm(scanner);
            try
            {
                Application.Run(form);
            }
            finally { form.CloseOpenConnections(true); }
        }
    }
}