using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace LoginGUI
{
    /// <remarks>
    /// AdminForm contains the user interface for the Administration Panel, which includes
    /// password reset and report generation functions.
    /// </remarks>
    /// <summary>
    /// AdminForm contains the user interface for the Administration Panel, which includes
    /// password reset and report generation functions.
    /// </summary>
    public partial class AdminForm : Form
    {
        /// <summary>
        /// parentForm stores the calling form (<paramref>LoginForm</paramref>) so it may be hidden and accessed from this form.
        /// </summary>
        private Form parentForm;

        /// <summary>
        /// Constructor that initializes the <paramref>AdminForm</paramref> and hides the calling parent form.
        /// </summary>
        /// <param name="pf">Calling form that is hidden</param>
        public AdminForm(Form pf)
        {
            InitializeComponent();
            parentForm = pf;
            pf.Hide();
        }

        /// <summary>
        /// Preload user and module information for generating reports.
        /// </summary>
        /// <param name="sender">.NET GUI parameter</param>
        /// <param name="e">.NET GUI parameter</param>
        private void Admin_Load(object sender, EventArgs e)
        {
            // FILE NAMES

            // User Score file
            string userFile = Directory.GetCurrentDirectory() + "\\data\\users.dat";
            // Module Score file
            string moduleFile = Directory.GetCurrentDirectory() + "\\modules\\modules.dat";
            // string for storing temporary parse data
            string tempstring = "";

            // Open filestreams
            StreamReader userStream= new StreamReader(userFile);
            StreamReader moduleStream = new StreamReader(moduleFile);

            while ((tempstring = userStream.ReadLine()) != null)
            // Read user file until EOF
            {
                if (tempstring.Equals("Admin"))
                // Skip the Admin user
                {
                    userStream.ReadLine();
                    continue;
                }
                else
                // Add username to cbox_selectUser combobox
                {
                    cbox_selectUser.Items.Add(tempstring);
                    userStream.ReadLine();
                }
            }
            // Select first item in combobox
            cbox_selectUser.SelectedIndex = 0;

            while ((tempstring = moduleStream.ReadLine()) != null)
            // Read module file until EOF
            {
                // Add module to cbox_selectGame combobox
                cbox_selectGame.Items.Add(tempstring);
            }
            // Select first item in combobox
            cbox_selectGame.SelectedIndex = 0;

            // Close filestreams
            userStream.Close();
            moduleStream.Close();
        }

        private void btn_PwdLookup_Click(object sender, EventArgs e)
        {
            // Show password reset panel

            pnl_Startup.Visible = false;
            pnl_PwdLookup.Visible = true;
            this.Text = "Administration Tools - Password Reset";
        }

        private void btn_Login_Click(object sender, EventArgs e)
        {
            // Close AdminForm and show LoginForm

            parentForm.Show();
            this.Close();
        }

        private void btn_AdminPanel1_Click(object sender, EventArgs e)
        {
            // Show administration panel from password reset panel

            pnl_Startup.Visible = true;
            pnl_PwdLookup.Visible = false;
            this.Text = "Administration Tools";   
        }


        private void btn_AdminPanel2_Click(object sender, EventArgs e)
        {
            // Show administration panel from report generation panel

            pnl_Startup.Visible = true;
            pnl_GenerateReport.Visible = false;
            this.Text = "Administration Tools";
        }

        private void btn_ReportGen_Click(object sender, EventArgs e)
        {
            // Show report generation panel with user report selected

            btn_userReport.Checked = true;
            this.Text = "Administration Tools - Report Generator";
            pnl_GenerateReport.Visible = true;
            pnl_Startup.Visible = false;

        }

        private void btn_resetPwd_Click(object sender, EventArgs e)
        {
            //Create temp file
            StreamWriter tempFile;
            StreamReader userFile;

            tempFile = new StreamWriter(Directory.GetCurrentDirectory() + "\\data\\users.tmp");
            userFile = new StreamReader(Directory.GetCurrentDirectory() + "\\data\\users.dat");
            //Read in from user file

            string tempuser;
            bool found = false;

            //Copy usernames and passwords over to temp file
            while ((tempuser = userFile.ReadLine()) != null)
            {
                tempFile.WriteLine(tempuser);
                // Once desired username is reached,
                // copy username and new desired password over
                if (tempuser.Equals(txt_Username.Text.ToString()))
                {
                    tempFile.WriteLine(LoginGUI.Login.MD5Encrypt(txt_newPwd.Text.ToString() + txt_Username.Text.ToString()));
                    userFile.ReadLine();
                    found = true;
                }
                else
                    tempFile.WriteLine(userFile.ReadLine());
            }

            // Close file streams
            userFile.Close();
            tempFile.Close();
            if (!found)
            // If username not found... Show error
            // Delete temp file
            {
                MessageBox.Show("User does not exist!  Please check spelling or create an account.");
                File.Delete("data\\users.tmp");
            }
            else
            // Else if username was found...
            {
                MessageBox.Show(txt_Username.Text.ToString() + "'s password successfully changed to: " + txt_newPwd.Text.ToString());
                //Delete user file
                File.Delete("data\\users.dat");

                //Rename temp file to user file (File.Move)
                File.Move("data\\users.tmp", "data\\users.dat");
            }

        }

        private void btn_generateReport_Click(object sender, EventArgs e)
        {
         
            UserStats us = new UserStats();

            if (btn_userReport.Checked)
            // If user report is selected ...
            {
                try
                {
                    // Parse user score (see UserStats.cs)
                    // Pass to, and open, a new ChartForm
                    ChartForm cf = new ChartForm(us.parseUserScore(cbox_selectUser.Text, cbox_selectGame.Text));
                    cf.Show();
                }
                catch (FileNotFoundException f)
                // If user has not played the game
                // Display error message and do not continue
                {
                    MessageBox.Show("User's score file not found.\n" + cbox_selectUser.Text + " has not played " + cbox_selectGame.Text + ".");
                }
            }
            else
            // Else if game report is selected...
            {
                try
                {
                    // Parse module scores (see UserStats.cs)
                    // Pass to, and open, a new ChartForm
                    ChartForm cf = new ChartForm(us.parseModuleScore(cbox_selectGame.Text));
                    cf.Show();
                }
                catch (FileNotFoundException f)
                // If game has not been played
                // Display error message and do not continue
                {
                    MessageBox.Show("Game score file not found.\n" + cbox_selectGame.Text + " has not been played yet.");
                }
            }
           
        }

        private void btn_userReport_CheckedChanged(object sender, EventArgs e)
        {
            // Controls user report and game report radio buttons

            if (btn_userReport.Checked)
            {
                cbox_selectUser.Enabled = true;
            }
            else
            {
                cbox_selectUser.Enabled = false;
            }
        }

        private void Admin_FormClosed(object sender, FormClosedEventArgs e)
        {
            // When this form is closed, show LoginForm

            parentForm.Show();
        }

    }
}