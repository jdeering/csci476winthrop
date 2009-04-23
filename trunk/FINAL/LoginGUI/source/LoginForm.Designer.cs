namespace LoginGUI
{
    partial class LoginForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnSel_login = new System.Windows.Forms.RadioButton();
            this.btnSel_crtUser = new System.Windows.Forms.RadioButton();
            this.str_userName = new System.Windows.Forms.TextBox();
            this.str_pwd = new System.Windows.Forms.TextBox();
            this.str_verPwd = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lbl_verPwd = new System.Windows.Forms.Label();
            this.btn_login = new System.Windows.Forms.Button();
            this.btn_crtUser = new System.Windows.Forms.Button();
            this.btn_Exit = new System.Windows.Forms.Button();
            this.Framework = new System.Diagnostics.Process();
            this.SuspendLayout();
            // 
            // btnSel_login
            // 
            this.btnSel_login.AutoSize = true;
            this.btnSel_login.Checked = true;
            this.btnSel_login.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSel_login.ForeColor = System.Drawing.Color.White;
            this.btnSel_login.Location = new System.Drawing.Point(16, 5);
            this.btnSel_login.Name = "btnSel_login";
            this.btnSel_login.Size = new System.Drawing.Size(66, 21);
            this.btnSel_login.TabIndex = 1;
            this.btnSel_login.TabStop = true;
            this.btnSel_login.Text = "Login";
            this.btnSel_login.UseVisualStyleBackColor = true;
            // 
            // btnSel_crtUser
            // 
            this.btnSel_crtUser.AutoSize = true;
            this.btnSel_crtUser.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSel_crtUser.ForeColor = System.Drawing.Color.White;
            this.btnSel_crtUser.Location = new System.Drawing.Point(16, 24);
            this.btnSel_crtUser.Name = "btnSel_crtUser";
            this.btnSel_crtUser.Size = new System.Drawing.Size(113, 21);
            this.btnSel_crtUser.TabIndex = 2;
            this.btnSel_crtUser.Text = "Create User";
            this.btnSel_crtUser.UseVisualStyleBackColor = true;
            this.btnSel_crtUser.CheckedChanged += new System.EventHandler(this.btnSel_crtUser_CheckedChanged);
            // 
            // str_userName
            // 
            this.str_userName.Location = new System.Drawing.Point(139, 58);
            this.str_userName.MaxLength = 20;
            this.str_userName.Name = "str_userName";
            this.str_userName.Size = new System.Drawing.Size(216, 20);
            this.str_userName.TabIndex = 3;
            // 
            // str_pwd
            // 
            this.str_pwd.Location = new System.Drawing.Point(139, 84);
            this.str_pwd.MaxLength = 15;
            this.str_pwd.Name = "str_pwd";
            this.str_pwd.PasswordChar = '*';
            this.str_pwd.Size = new System.Drawing.Size(216, 20);
            this.str_pwd.TabIndex = 4;
            // 
            // str_verPwd
            // 
            this.str_verPwd.Location = new System.Drawing.Point(139, 110);
            this.str_verPwd.MaxLength = 15;
            this.str_verPwd.Name = "str_verPwd";
            this.str_verPwd.PasswordChar = '*';
            this.str_verPwd.Size = new System.Drawing.Size(216, 20);
            this.str_verPwd.TabIndex = 5;
            this.str_verPwd.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(43, 61);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(93, 17);
            this.label1.TabIndex = 6;
            this.label1.Text = "User Name:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(54, 87);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 17);
            this.label2.TabIndex = 7;
            this.label2.Text = "Password:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lbl_verPwd
            // 
            this.lbl_verPwd.AutoSize = true;
            this.lbl_verPwd.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_verPwd.ForeColor = System.Drawing.Color.White;
            this.lbl_verPwd.Location = new System.Drawing.Point(7, 113);
            this.lbl_verPwd.Name = "lbl_verPwd";
            this.lbl_verPwd.Size = new System.Drawing.Size(129, 17);
            this.lbl_verPwd.TabIndex = 8;
            this.lbl_verPwd.Text = "Verify Password:";
            this.lbl_verPwd.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.lbl_verPwd.Visible = false;
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(139, 146);
            this.btn_login.Name = "btn_login";
            this.btn_login.Size = new System.Drawing.Size(95, 25);
            this.btn_login.TabIndex = 9;
            this.btn_login.Text = "Login";
            this.btn_login.UseVisualStyleBackColor = true;
            this.btn_login.Click += new System.EventHandler(this.btn_login_Click);
            // 
            // btn_crtUser
            // 
            this.btn_crtUser.Location = new System.Drawing.Point(139, 146);
            this.btn_crtUser.Name = "btn_crtUser";
            this.btn_crtUser.Size = new System.Drawing.Size(95, 25);
            this.btn_crtUser.TabIndex = 10;
            this.btn_crtUser.Text = "Create User";
            this.btn_crtUser.UseVisualStyleBackColor = true;
            this.btn_crtUser.Visible = false;
            this.btn_crtUser.Click += new System.EventHandler(this.btn_crtUser_Click);
            // 
            // btn_Exit
            // 
            this.btn_Exit.Location = new System.Drawing.Point(263, 146);
            this.btn_Exit.Name = "btn_Exit";
            this.btn_Exit.Size = new System.Drawing.Size(92, 25);
            this.btn_Exit.TabIndex = 11;
            this.btn_Exit.Text = "Exit";
            this.btn_Exit.UseVisualStyleBackColor = true;
            this.btn_Exit.Click += new System.EventHandler(this.btn_Exit_Click);
            // 
            // Framework
            // 
            this.Framework.StartInfo.Domain = "";
            this.Framework.StartInfo.FileName = "notepad.exe";
            this.Framework.StartInfo.LoadUserProfile = false;
            this.Framework.StartInfo.Password = null;
            this.Framework.StartInfo.StandardErrorEncoding = null;
            this.Framework.StartInfo.StandardOutputEncoding = null;
            this.Framework.StartInfo.UserName = "";
            this.Framework.SynchronizingObject = this;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Navy;
            this.ClientSize = new System.Drawing.Size(387, 184);
            this.Controls.Add(this.btn_Exit);
            this.Controls.Add(this.btn_crtUser);
            this.Controls.Add(this.btn_login);
            this.Controls.Add(this.lbl_verPwd);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.str_verPwd);
            this.Controls.Add(this.str_pwd);
            this.Controls.Add(this.str_userName);
            this.Controls.Add(this.btnSel_crtUser);
            this.Controls.Add(this.btnSel_login);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Login";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton btnSel_login;
        private System.Windows.Forms.RadioButton btnSel_crtUser;
        private System.Windows.Forms.TextBox str_userName;
        private System.Windows.Forms.TextBox str_pwd;
        private System.Windows.Forms.TextBox str_verPwd;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lbl_verPwd;
        private System.Windows.Forms.Button btn_login;
        private System.Windows.Forms.Button btn_crtUser;
        private System.Windows.Forms.Button btn_Exit;
        private System.Diagnostics.Process Framework;
    }
}

