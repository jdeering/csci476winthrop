using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LoginGUI
{
    /// <remarks>
    /// LoginForm contains a user interface for logging in and create user functions.
    /// </remarks>
    /// <summary>
    /// LoginForm contains a user interface for logging in and create user functions.
    /// </summary>
    public partial class LoginForm : Form
    {
        /// <summary>
        /// Constructor initializes and displays the form.
        /// </summary>
        public LoginForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Validates a username to ensure no illegal characters are entered.
        /// </summary>
        /// <param name="username">Username being validated.</param>
        /// <returns>1 if username is valid, 0 if username is invalid.</returns>
        private bool UserNameValidate(string username)
        {
            if (username.Contains(".") || username.Contains(",") || username.Contains("'")
                || username.Contains("`") || username.Contains(":") || username.Contains("/")
                || username.Contains("\\") || username.Contains("*") || username.Contains("|")
                || username.Contains("?") || username.Contains("\"") || username.Contains("&")
                || username.Contains("%") || username.Contains("$") || username.Contains("!")
                || username.Contains("-") || username.Contains("+") || username.Contains("=")
                || username.Contains("(") || username.Contains(")") || username.Contains("[")
                || username.Contains("]") || username.Contains("{") || username.Contains("}")
                || username.Contains(" "))
            // Disallows special characters
            {
                MessageBox.Show("Username cannot contain the characters:\n. , ; ' ` : / \\ * | ? \" & % $ ! - + = ( ) [ ] { }");
                str_userName.Focus();
                str_userName.SelectAll();
                return false;
            }
            else if (username.Equals("scores"))
            // Prevents the scores.xml file from being overwritten
            {
                MessageBox.Show("This username is reserved.  Please try another username.");
                str_userName.Focus();
                str_userName.SelectAll();
            }
            return true;

        }

        private void btnSel_crtUser_CheckedChanged(object sender, EventArgs e)
        {
            if (btnSel_crtUser.Checked)
            // Enables Create User function
            // Shows the Verify Password textbox
            {
                lbl_verPwd.Show();
                str_verPwd.Show();
                btn_crtUser.Show();
                btn_login.Hide();
            }
            else
            // Enables the Login function
            // Hides the Verify Password textbox
            {
                lbl_verPwd.Hide();
                str_verPwd.Hide();
                btn_crtUser.Hide();
                btn_login.Show();
            }
        }

        private void btn_login_Click(object sender, EventArgs e)
        {
            if (UserNameValidate(str_userName.Text.ToString()))
            // If the username is legal...
            {
                if (Login.UserLogin(str_userName.Text.ToString(), str_pwd.Text.ToString()) == 1)
                // and if the username is an existing user with the correct password...
                {
                    if(str_userName.Text.ToString().Equals("Admin"))
                    // If Admin login...
                    {
                        // Show Administration Panel (AdminForm)
                        AdminForm adminForm = new AdminForm(this);
                        adminForm.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
                        adminForm.Show();

                        // Reset login information
                        str_userName.Text = "";
                        str_pwd.Text = "";
                    }
                    else
                    // Correct login
                    {
                        // Launch game framework
                        MessageBox.Show(str_userName.Text.ToString() + " successfully logged in!");
                        Framework.StartInfo.Arguments = str_userName.Text.ToString();
                        Framework.Start(); // <-- This is where the Framework is launched
                        Close();
                    }
                }
                else
                // Else if login fails
                {
                    // Display error message, and do not proceed
                    MessageBox.Show("Login failed! Incorrect Username or Password!\nIf you do not have a Username, click Create User");
                }
            }
        }

        private void btn_crtUser_Click(object sender, EventArgs e)
        {
            if (UserNameValidate(str_userName.Text.ToString()))
            // If username to be created is legal...
            {
                if (!str_pwd.Text.ToString().Equals(str_verPwd.Text.ToString()))
                // If password and verify password do not match...
                {
                    // Display error message and do not continue
                    MessageBox.Show("Password and Verify Password do not match!");
                    str_pwd.Focus();
                    str_pwd.SelectAll();
                }
                else if (str_pwd.Text.Length < 4)
                // If password length is less than 4...
                {
                    // Display error message and do not continue
                    MessageBox.Show("Password must be 4 characters or longer.");
                    str_pwd.Focus();
                    str_pwd.SelectAll();
                }
                else if (Login.CreateUser(str_userName.Text.ToString(), str_pwd.Text.ToString(), str_verPwd.Text.ToString()) == 1)
                // Else if username is unique and legal...
                {
                    // Success! and go back to the login screen
                    MessageBox.Show(str_userName.Text.ToString() + " successfully created!\nYou may now login.");
                    btn_login.Show();
                    btnSel_login.Select();
                    str_userName.Clear();
                    str_pwd.Clear();
                    str_verPwd.Clear();
                }
                else
                // Else if username already exists...
                {
                    // Display error message and do not continue
                    MessageBox.Show("User already exists!\nLogin, or try another Username.");
                    str_userName.Focus();
                    str_userName.SelectAll();
                }
            }
        }

        private void btn_Exit_Click(object sender, EventArgs e)
        {
            // Close Login application
            Close();
        }

    }
}