using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using System.IO;

namespace LoginGUI
{
    /// <remarks>
    /// Login contains methods for storing and looking up usernames and passwords, as well as an MD5 encryption method.
    /// </remarks>
    /// <summary>
    /// Login contains methods for storing and looking up usernames and passwords, as well as an MD5 encryption method.
    /// </summary>
    public class Login
    {
        /// <summary>
        /// MD5Encrypt performs an MD5 hash on <paramref>valueString</paramref>
        /// </summary>
        /// <param name="valueString">String to be encrypted.</param>
        /// <returns>MD5 encrypted string.</returns>
        public static string MD5Encrypt(string valueString)
        {
            string ret = String.Empty;
            //Setup crypto
            MD5CryptoServiceProvider md5Hasher = new MD5CryptoServiceProvider();
            //Get bytes
            byte[] data = System.Text.Encoding.ASCII.GetBytes(valueString);
            //Encrypt
            data = md5Hasher.ComputeHash(data);
            //Convert from byte 2 hex
            for (int i = 0; i < data.Length; i++)
            {
                ret += data[i].ToString("x2").ToLower();
            }
            //Return encoded string
            return ret;
        }


        /// <summary>
        /// CreateUser creates and stores a user if the username and password are valid.
        /// </summary>
        /// <param name="username">Username to be created.</param>
        /// <param name="password">Password for new user.</param>
        /// <param name="verpass">Verified (matching) password for new user.</param>
        /// <returns>-1 if user exists; 0 if password and verified password do not match; 1 if successful.</returns>
        public static int CreateUser(string username, string password, string verpass)
        {
            if (!password.Equals(verpass))
                return 0; // Password and verified password do not match

            StreamReader loginFileIn; // for looking through user file
            StreamWriter loginFileOut; // for writing new user name to user file

            if (File.Exists("data\\users.dat"))
            // If file exists...
            // Check user file for existing user
            {
                loginFileIn = new StreamReader("data\\users.dat");
                string tempuser;

                while ((tempuser = loginFileIn.ReadLine()) != null)
                {
                    if (tempuser.Equals(username))
                    {
                        loginFileIn.Close(); // close read stream
                        return -1; // user already exists
                    }
                    loginFileIn.ReadLine();
                }
                loginFileIn.Close();
            }

            loginFileOut = new StreamWriter("data\\users.dat", true);

            loginFileOut.Write(username); // Write username to file
            loginFileOut.WriteLine();
            loginFileOut.Write(MD5Encrypt(password + username)); // Write encrypted password to file
            loginFileOut.WriteLine();
            loginFileOut.Close(); // Close write stream
            return 1; //User created successfully
        }

        /// <summary>
        /// UserLogin checks the <paramref>username</paramref> and <paramref>password</paramref>
        /// to see if they exist and match.
        /// </summary>
        /// <param name="username">Entered username.</param>
        /// <param name="password">Entered password.</param>
        /// <returns>1 if login success; 0 if failed.</returns>
        public static int UserLogin(string username, string password)
        {
            if (!File.Exists("data\\users.dat")) return 0; //no users exist

            // Open user file stream
            StreamReader loginFile = new StreamReader("data\\users.dat");
            string tempuser, temppass;

            while ((tempuser = loginFile.ReadLine()) != null)
            // Read to end of file
            {
                temppass = loginFile.ReadLine().ToString();
                if (tempuser.Equals(username))
                // If username matches...
                {
                    if (temppass.Equals(MD5Encrypt(password + username)))
                    // If password matches...
                    {
                        loginFile.Close();
                        return 1; // Login success
                    }
                }
            }
            loginFile.Close(); // Close user file
            return 0;
        }                   
    }
}
