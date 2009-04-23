using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace LoginGUI
{
    /// <summary>
    /// .NET created entry point class (DO NOT MODIFY)
    /// </summary>
    /// <remarks>
    /// .NET created entry point class (DO NOT MODIFY)
    /// </remarks>
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new LoginForm()); // starts application with LoginForm
        }
    }
}