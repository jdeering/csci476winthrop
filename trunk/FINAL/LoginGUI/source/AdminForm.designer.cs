namespace LoginGUI
{
    partial class AdminForm
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
            this.pnl_Startup = new System.Windows.Forms.Panel();
            this.btn_Login = new System.Windows.Forms.Button();
            this.btn_ReportGen = new System.Windows.Forms.Button();
            this.btn_PwdLookup = new System.Windows.Forms.Button();
            this.pnl_PwdLookup = new System.Windows.Forms.Panel();
            this.btn_AdminPanel1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_resetPwd = new System.Windows.Forms.Button();
            this.txt_newPwd = new System.Windows.Forms.TextBox();
            this.txt_Username = new System.Windows.Forms.TextBox();
            this.lbl_foundPwd = new System.Windows.Forms.Label();
            this.lbl_username = new System.Windows.Forms.Label();
            this.pnl_GenerateReport = new System.Windows.Forms.Panel();
            this.btn_moduleReport = new System.Windows.Forms.RadioButton();
            this.btn_userReport = new System.Windows.Forms.RadioButton();
            this.btn_generateReport = new System.Windows.Forms.Button();
            this.cbox_selectGame = new System.Windows.Forms.ComboBox();
            this.cbox_selectUser = new System.Windows.Forms.ComboBox();
            this.lbl_selectgame = new System.Windows.Forms.Label();
            this.lbl_selectuser = new System.Windows.Forms.Label();
            this.btn_AdminPanel2 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.pnl_Startup.SuspendLayout();
            this.pnl_PwdLookup.SuspendLayout();
            this.pnl_GenerateReport.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnl_Startup
            // 
            this.pnl_Startup.Controls.Add(this.btn_Login);
            this.pnl_Startup.Controls.Add(this.btn_ReportGen);
            this.pnl_Startup.Controls.Add(this.btn_PwdLookup);
            this.pnl_Startup.Location = new System.Drawing.Point(17, 13);
            this.pnl_Startup.Name = "pnl_Startup";
            this.pnl_Startup.Size = new System.Drawing.Size(363, 155);
            this.pnl_Startup.TabIndex = 0;
            // 
            // btn_Login
            // 
            this.btn_Login.Location = new System.Drawing.Point(113, 104);
            this.btn_Login.Name = "btn_Login";
            this.btn_Login.Size = new System.Drawing.Size(137, 31);
            this.btn_Login.TabIndex = 4;
            this.btn_Login.Text = "Back to Login";
            this.btn_Login.UseVisualStyleBackColor = true;
            this.btn_Login.Click += new System.EventHandler(this.btn_Login_Click);
            // 
            // btn_ReportGen
            // 
            this.btn_ReportGen.Location = new System.Drawing.Point(113, 58);
            this.btn_ReportGen.Name = "btn_ReportGen";
            this.btn_ReportGen.Size = new System.Drawing.Size(137, 31);
            this.btn_ReportGen.TabIndex = 3;
            this.btn_ReportGen.Text = "Report Generator";
            this.btn_ReportGen.UseVisualStyleBackColor = true;
            this.btn_ReportGen.Click += new System.EventHandler(this.btn_ReportGen_Click);
            // 
            // btn_PwdLookup
            // 
            this.btn_PwdLookup.Location = new System.Drawing.Point(113, 12);
            this.btn_PwdLookup.Name = "btn_PwdLookup";
            this.btn_PwdLookup.Size = new System.Drawing.Size(137, 31);
            this.btn_PwdLookup.TabIndex = 2;
            this.btn_PwdLookup.Text = "Reset Password";
            this.btn_PwdLookup.UseVisualStyleBackColor = true;
            this.btn_PwdLookup.Click += new System.EventHandler(this.btn_PwdLookup_Click);
            // 
            // pnl_PwdLookup
            // 
            this.pnl_PwdLookup.Controls.Add(this.btn_AdminPanel1);
            this.pnl_PwdLookup.Controls.Add(this.label1);
            this.pnl_PwdLookup.Controls.Add(this.btn_resetPwd);
            this.pnl_PwdLookup.Controls.Add(this.txt_newPwd);
            this.pnl_PwdLookup.Controls.Add(this.txt_Username);
            this.pnl_PwdLookup.Controls.Add(this.lbl_foundPwd);
            this.pnl_PwdLookup.Controls.Add(this.lbl_username);
            this.pnl_PwdLookup.Location = new System.Drawing.Point(20, 10);
            this.pnl_PwdLookup.Name = "pnl_PwdLookup";
            this.pnl_PwdLookup.Size = new System.Drawing.Size(362, 159);
            this.pnl_PwdLookup.TabIndex = 1;
            this.pnl_PwdLookup.Visible = false;
            // 
            // btn_AdminPanel1
            // 
            this.btn_AdminPanel1.Location = new System.Drawing.Point(96, 131);
            this.btn_AdminPanel1.Name = "btn_AdminPanel1";
            this.btn_AdminPanel1.Size = new System.Drawing.Size(114, 25);
            this.btn_AdminPanel1.TabIndex = 6;
            this.btn_AdminPanel1.Text = "Back to Admin Panel";
            this.btn_AdminPanel1.UseVisualStyleBackColor = true;
            this.btn_AdminPanel1.Click += new System.EventHandler(this.btn_AdminPanel1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(6, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(121, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "Reset Password";
            // 
            // btn_resetPwd
            // 
            this.btn_resetPwd.Location = new System.Drawing.Point(278, 92);
            this.btn_resetPwd.Name = "btn_resetPwd";
            this.btn_resetPwd.Size = new System.Drawing.Size(71, 21);
            this.btn_resetPwd.TabIndex = 4;
            this.btn_resetPwd.Text = "Reset";
            this.btn_resetPwd.UseVisualStyleBackColor = true;
            this.btn_resetPwd.Click += new System.EventHandler(this.btn_resetPwd_Click);
            // 
            // txt_newPwd
            // 
            this.txt_newPwd.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.txt_newPwd.Location = new System.Drawing.Point(96, 92);
            this.txt_newPwd.Name = "txt_newPwd";
            this.txt_newPwd.Size = new System.Drawing.Size(166, 20);
            this.txt_newPwd.TabIndex = 3;
            // 
            // txt_Username
            // 
            this.txt_Username.Location = new System.Drawing.Point(96, 54);
            this.txt_Username.Name = "txt_Username";
            this.txt_Username.Size = new System.Drawing.Size(166, 20);
            this.txt_Username.TabIndex = 2;
            // 
            // lbl_foundPwd
            // 
            this.lbl_foundPwd.AutoSize = true;
            this.lbl_foundPwd.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_foundPwd.ForeColor = System.Drawing.Color.White;
            this.lbl_foundPwd.Location = new System.Drawing.Point(6, 93);
            this.lbl_foundPwd.Name = "lbl_foundPwd";
            this.lbl_foundPwd.Size = new System.Drawing.Size(84, 16);
            this.lbl_foundPwd.TabIndex = 1;
            this.lbl_foundPwd.Text = "Password: ";
            // 
            // lbl_username
            // 
            this.lbl_username.AutoSize = true;
            this.lbl_username.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_username.ForeColor = System.Drawing.Color.White;
            this.lbl_username.Location = new System.Drawing.Point(6, 55);
            this.lbl_username.Name = "lbl_username";
            this.lbl_username.Size = new System.Drawing.Size(87, 16);
            this.lbl_username.TabIndex = 0;
            this.lbl_username.Text = "Username: ";
            // 
            // pnl_GenerateReport
            // 
            this.pnl_GenerateReport.Controls.Add(this.btn_moduleReport);
            this.pnl_GenerateReport.Controls.Add(this.btn_userReport);
            this.pnl_GenerateReport.Controls.Add(this.btn_generateReport);
            this.pnl_GenerateReport.Controls.Add(this.cbox_selectGame);
            this.pnl_GenerateReport.Controls.Add(this.cbox_selectUser);
            this.pnl_GenerateReport.Controls.Add(this.lbl_selectgame);
            this.pnl_GenerateReport.Controls.Add(this.lbl_selectuser);
            this.pnl_GenerateReport.Controls.Add(this.btn_AdminPanel2);
            this.pnl_GenerateReport.Controls.Add(this.label2);
            this.pnl_GenerateReport.Location = new System.Drawing.Point(17, 10);
            this.pnl_GenerateReport.Name = "pnl_GenerateReport";
            this.pnl_GenerateReport.Size = new System.Drawing.Size(366, 159);
            this.pnl_GenerateReport.TabIndex = 7;
            this.pnl_GenerateReport.Visible = false;
            // 
            // btn_moduleReport
            // 
            this.btn_moduleReport.AutoSize = true;
            this.btn_moduleReport.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_moduleReport.ForeColor = System.Drawing.Color.White;
            this.btn_moduleReport.Location = new System.Drawing.Point(236, 9);
            this.btn_moduleReport.Name = "btn_moduleReport";
            this.btn_moduleReport.Size = new System.Drawing.Size(67, 20);
            this.btn_moduleReport.TabIndex = 13;
            this.btn_moduleReport.TabStop = true;
            this.btn_moduleReport.Text = "Game";
            this.btn_moduleReport.UseVisualStyleBackColor = true;
            // 
            // btn_userReport
            // 
            this.btn_userReport.AutoSize = true;
            this.btn_userReport.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_userReport.ForeColor = System.Drawing.Color.White;
            this.btn_userReport.Location = new System.Drawing.Point(166, 9);
            this.btn_userReport.Name = "btn_userReport";
            this.btn_userReport.Size = new System.Drawing.Size(59, 20);
            this.btn_userReport.TabIndex = 12;
            this.btn_userReport.TabStop = true;
            this.btn_userReport.Text = "User";
            this.btn_userReport.UseVisualStyleBackColor = true;
            this.btn_userReport.CheckedChanged += new System.EventHandler(this.btn_userReport_CheckedChanged);
            // 
            // btn_generateReport
            // 
            this.btn_generateReport.Location = new System.Drawing.Point(291, 89);
            this.btn_generateReport.Name = "btn_generateReport";
            this.btn_generateReport.Size = new System.Drawing.Size(70, 20);
            this.btn_generateReport.TabIndex = 11;
            this.btn_generateReport.Text = "Generate";
            this.btn_generateReport.UseVisualStyleBackColor = true;
            this.btn_generateReport.Click += new System.EventHandler(this.btn_generateReport_Click);
            // 
            // cbox_selectGame
            // 
            this.cbox_selectGame.FormattingEnabled = true;
            this.cbox_selectGame.Location = new System.Drawing.Point(116, 88);
            this.cbox_selectGame.Name = "cbox_selectGame";
            this.cbox_selectGame.Size = new System.Drawing.Size(168, 21);
            this.cbox_selectGame.TabIndex = 10;
            // 
            // cbox_selectUser
            // 
            this.cbox_selectUser.FormattingEnabled = true;
            this.cbox_selectUser.Location = new System.Drawing.Point(116, 52);
            this.cbox_selectUser.Name = "cbox_selectUser";
            this.cbox_selectUser.Size = new System.Drawing.Size(168, 21);
            this.cbox_selectUser.TabIndex = 9;
            // 
            // lbl_selectgame
            // 
            this.lbl_selectgame.AutoSize = true;
            this.lbl_selectgame.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_selectgame.ForeColor = System.Drawing.Color.White;
            this.lbl_selectgame.Location = new System.Drawing.Point(6, 92);
            this.lbl_selectgame.Name = "lbl_selectgame";
            this.lbl_selectgame.Size = new System.Drawing.Size(105, 17);
            this.lbl_selectgame.TabIndex = 8;
            this.lbl_selectgame.Text = "Select Game:";
            // 
            // lbl_selectuser
            // 
            this.lbl_selectuser.AutoSize = true;
            this.lbl_selectuser.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_selectuser.ForeColor = System.Drawing.Color.White;
            this.lbl_selectuser.Location = new System.Drawing.Point(6, 54);
            this.lbl_selectuser.Name = "lbl_selectuser";
            this.lbl_selectuser.Size = new System.Drawing.Size(97, 17);
            this.lbl_selectuser.TabIndex = 7;
            this.lbl_selectuser.Text = "Select User:";
            // 
            // btn_AdminPanel2
            // 
            this.btn_AdminPanel2.Location = new System.Drawing.Point(96, 131);
            this.btn_AdminPanel2.Name = "btn_AdminPanel2";
            this.btn_AdminPanel2.Size = new System.Drawing.Size(114, 25);
            this.btn_AdminPanel2.TabIndex = 6;
            this.btn_AdminPanel2.Text = "Back to Admin Panel";
            this.btn_AdminPanel2.UseVisualStyleBackColor = true;
            this.btn_AdminPanel2.Click += new System.EventHandler(this.btn_AdminPanel2_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(6, 11);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(149, 16);
            this.label2.TabIndex = 5;
            this.label2.Text = "Generate Report for:";
            // 
            // Admin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Navy;
            this.ClientSize = new System.Drawing.Size(387, 184);
            this.Controls.Add(this.pnl_GenerateReport);
            this.Controls.Add(this.pnl_PwdLookup);
            this.Controls.Add(this.pnl_Startup);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Admin";
            this.Text = "Administration Tools";
            this.Load += new System.EventHandler(this.Admin_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Admin_FormClosed);
            this.pnl_Startup.ResumeLayout(false);
            this.pnl_PwdLookup.ResumeLayout(false);
            this.pnl_PwdLookup.PerformLayout();
            this.pnl_GenerateReport.ResumeLayout(false);
            this.pnl_GenerateReport.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnl_Startup;
        private System.Windows.Forms.Button btn_ReportGen;
        private System.Windows.Forms.Button btn_PwdLookup;
        private System.Windows.Forms.Panel pnl_PwdLookup;
        private System.Windows.Forms.Label lbl_username;
        private System.Windows.Forms.Label lbl_foundPwd;
        private System.Windows.Forms.TextBox txt_newPwd;
        private System.Windows.Forms.TextBox txt_Username;
        private System.Windows.Forms.Button btn_resetPwd;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_Login;
        private System.Windows.Forms.Button btn_AdminPanel1;
        private System.Windows.Forms.Panel pnl_GenerateReport;
        private System.Windows.Forms.Button btn_AdminPanel2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lbl_selectuser;
        private System.Windows.Forms.Label lbl_selectgame;
        private System.Windows.Forms.Button btn_generateReport;
        private System.Windows.Forms.ComboBox cbox_selectGame;
        private System.Windows.Forms.ComboBox cbox_selectUser;
        private System.Windows.Forms.RadioButton btn_userReport;
        private System.Windows.Forms.RadioButton btn_moduleReport;

    }
}

