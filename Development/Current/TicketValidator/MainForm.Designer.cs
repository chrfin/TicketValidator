namespace TicketValidator
{
    partial class mainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.MainMenu mainMenu;

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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.mainMenu = new System.Windows.Forms.MainMenu();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonRedeem = new System.Windows.Forms.Button();
            this.labelCodeInfo = new System.Windows.Forms.Label();
            this.buttonClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonCancel
            // 
            this.buttonCancel.BackColor = System.Drawing.Color.Pink;
            this.buttonCancel.Location = new System.Drawing.Point(7, 210);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(224, 27);
            this.buttonCancel.TabIndex = 7;
            this.buttonCancel.Text = "Abbrechen";
            // 
            // buttonRedeem
            // 
            this.buttonRedeem.BackColor = System.Drawing.Color.LightGreen;
            this.buttonRedeem.Enabled = false;
            this.buttonRedeem.Font = new System.Drawing.Font("Tahoma", 24F, System.Drawing.FontStyle.Regular);
            this.buttonRedeem.Location = new System.Drawing.Point(7, 165);
            this.buttonRedeem.Name = "buttonRedeem";
            this.buttonRedeem.Size = new System.Drawing.Size(224, 39);
            this.buttonRedeem.TabIndex = 6;
            this.buttonRedeem.Text = "Einlösen";
            // 
            // labelCodeInfo
            // 
            this.labelCodeInfo.Font = new System.Drawing.Font("Tahoma", 11F, System.Drawing.FontStyle.Bold);
            this.labelCodeInfo.Location = new System.Drawing.Point(7, 11);
            this.labelCodeInfo.Name = "labelCodeInfo";
            this.labelCodeInfo.Size = new System.Drawing.Size(224, 145);
            // 
            // buttonClose
            // 
            this.buttonClose.Font = new System.Drawing.Font("Tahoma", 10F, System.Drawing.FontStyle.Bold);
            this.buttonClose.Location = new System.Drawing.Point(150, 243);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(81, 17);
            this.buttonClose.TabIndex = 8;
            this.buttonClose.Text = "BEENDEN";
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // mainForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(238, 295);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonRedeem);
            this.Controls.Add(this.labelCodeInfo);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.mainMenu;
            this.Name = "mainForm";
            this.Text = "TicketValidator";
            this.Deactivate += new System.EventHandler(this.mainForm_Deactivate);
            this.Closed += new System.EventHandler(this.mainForm_Closed);
            this.Activated += new System.EventHandler(this.mainForm_Activated);
            this.Closing += new System.ComponentModel.CancelEventHandler(this.mainForm_Closing);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonRedeem;
        private System.Windows.Forms.Label labelCodeInfo;
        private System.Windows.Forms.Button buttonClose;

    }
}

