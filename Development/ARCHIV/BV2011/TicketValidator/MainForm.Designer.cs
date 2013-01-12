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
            this.tabControlMain = new System.Windows.Forms.TabControl();
            this.tabPageScan = new System.Windows.Forms.TabPage();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonRedeem = new System.Windows.Forms.Button();
            this.labelCodeInfo = new System.Windows.Forms.Label();
            this.tabPageList = new System.Windows.Forms.TabPage();
            this.labelRedeemed = new System.Windows.Forms.Label();
            this.labelOpen = new System.Windows.Forms.Label();
            this.tabPageSystem = new System.Windows.Forms.TabPage();
            this.buttonClose = new System.Windows.Forms.Button();
            this.buttonClear = new System.Windows.Forms.Button();
            this.buttonResetRedeemed = new System.Windows.Forms.Button();
            this.buttonImport = new System.Windows.Forms.Button();
            this.listBoxCards = new System.Windows.Forms.ListBox();
            this.tabControlMain.SuspendLayout();
            this.tabPageScan.SuspendLayout();
            this.tabPageList.SuspendLayout();
            this.tabPageSystem.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControlMain
            // 
            this.tabControlMain.Controls.Add(this.tabPageScan);
            this.tabControlMain.Controls.Add(this.tabPageList);
            this.tabControlMain.Controls.Add(this.tabPageSystem);
            this.tabControlMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControlMain.Location = new System.Drawing.Point(0, 0);
            this.tabControlMain.Name = "tabControlMain";
            this.tabControlMain.SelectedIndex = 0;
            this.tabControlMain.Size = new System.Drawing.Size(238, 295);
            this.tabControlMain.TabIndex = 1;
            this.tabControlMain.SelectedIndexChanged += new System.EventHandler(this.tabControlMain_SelectedIndexChanged);
            // 
            // tabPageScan
            // 
            this.tabPageScan.Controls.Add(this.buttonCancel);
            this.tabPageScan.Controls.Add(this.buttonRedeem);
            this.tabPageScan.Controls.Add(this.labelCodeInfo);
            this.tabPageScan.Location = new System.Drawing.Point(4, 30);
            this.tabPageScan.Name = "tabPageScan";
            this.tabPageScan.Size = new System.Drawing.Size(230, 261);
            this.tabPageScan.Text = "Scannen";
            // 
            // buttonCancel
            // 
            this.buttonCancel.BackColor = System.Drawing.Color.Pink;
            this.buttonCancel.Location = new System.Drawing.Point(3, 193);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(224, 27);
            this.buttonCancel.TabIndex = 2;
            this.buttonCancel.Text = "Abbrechen";
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonRedeem
            // 
            this.buttonRedeem.BackColor = System.Drawing.Color.LightGreen;
            this.buttonRedeem.Enabled = false;
            this.buttonRedeem.Font = new System.Drawing.Font("Tahoma", 24F, System.Drawing.FontStyle.Regular);
            this.buttonRedeem.Location = new System.Drawing.Point(3, 148);
            this.buttonRedeem.Name = "buttonRedeem";
            this.buttonRedeem.Size = new System.Drawing.Size(224, 39);
            this.buttonRedeem.TabIndex = 1;
            this.buttonRedeem.Text = "Einlösen";
            this.buttonRedeem.Click += new System.EventHandler(this.buttonRedeem_Click);
            // 
            // labelCodeInfo
            // 
            this.labelCodeInfo.Font = new System.Drawing.Font("Tahoma", 11F, System.Drawing.FontStyle.Bold);
            this.labelCodeInfo.Location = new System.Drawing.Point(3, 0);
            this.labelCodeInfo.Name = "labelCodeInfo";
            this.labelCodeInfo.Size = new System.Drawing.Size(224, 145);
            // 
            // tabPageList
            // 
            this.tabPageList.Controls.Add(this.listBoxCards);
            this.tabPageList.Controls.Add(this.labelRedeemed);
            this.tabPageList.Controls.Add(this.labelOpen);
            this.tabPageList.Location = new System.Drawing.Point(4, 30);
            this.tabPageList.Name = "tabPageList";
            this.tabPageList.Size = new System.Drawing.Size(230, 261);
            this.tabPageList.Text = "Liste";
            // 
            // labelRedeemed
            // 
            this.labelRedeemed.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.labelRedeemed.Location = new System.Drawing.Point(3, 16);
            this.labelRedeemed.Name = "labelRedeemed";
            this.labelRedeemed.Size = new System.Drawing.Size(224, 16);
            this.labelRedeemed.Text = "Eingelöst:";
            // 
            // labelOpen
            // 
            this.labelOpen.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.labelOpen.Location = new System.Drawing.Point(3, 0);
            this.labelOpen.Name = "labelOpen";
            this.labelOpen.Size = new System.Drawing.Size(224, 16);
            this.labelOpen.Text = "Offen:";
            // 
            // tabPageSystem
            // 
            this.tabPageSystem.Controls.Add(this.buttonClose);
            this.tabPageSystem.Controls.Add(this.buttonClear);
            this.tabPageSystem.Controls.Add(this.buttonResetRedeemed);
            this.tabPageSystem.Controls.Add(this.buttonImport);
            this.tabPageSystem.Location = new System.Drawing.Point(4, 30);
            this.tabPageSystem.Name = "tabPageSystem";
            this.tabPageSystem.Size = new System.Drawing.Size(230, 261);
            this.tabPageSystem.Text = "Setup";
            // 
            // buttonClose
            // 
            this.buttonClose.Font = new System.Drawing.Font("Tahoma", 10F, System.Drawing.FontStyle.Bold);
            this.buttonClose.Location = new System.Drawing.Point(26, 162);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(178, 35);
            this.buttonClose.TabIndex = 3;
            this.buttonClose.Text = "BEENDEN";
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(14, 111);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(202, 31);
            this.buttonClear.TabIndex = 2;
            this.buttonClear.Text = "ALLE Tickets löschen";
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // buttonResetRedeemed
            // 
            this.buttonResetRedeemed.Location = new System.Drawing.Point(14, 72);
            this.buttonResetRedeemed.Name = "buttonResetRedeemed";
            this.buttonResetRedeemed.Size = new System.Drawing.Size(202, 31);
            this.buttonResetRedeemed.TabIndex = 1;
            this.buttonResetRedeemed.Text = "Eingelöste zurücksetzen";
            this.buttonResetRedeemed.Click += new System.EventHandler(this.buttonResetRedeemed_Click);
            // 
            // buttonImport
            // 
            this.buttonImport.Location = new System.Drawing.Point(69, 23);
            this.buttonImport.Name = "buttonImport";
            this.buttonImport.Size = new System.Drawing.Size(92, 33);
            this.buttonImport.TabIndex = 0;
            this.buttonImport.Text = "Lade CSV";
            this.buttonImport.Click += new System.EventHandler(this.buttonImport_Click);
            // 
            // listBoxCards
            // 
            this.listBoxCards.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
            this.listBoxCards.Location = new System.Drawing.Point(3, 35);
            this.listBoxCards.Name = "listBoxCards";
            this.listBoxCards.Size = new System.Drawing.Size(224, 178);
            this.listBoxCards.TabIndex = 4;
            this.listBoxCards.SelectedIndexChanged += new System.EventHandler(this.listBoxCards_SelectedIndexChanged);
            // 
            // mainForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(238, 295);
            this.Controls.Add(this.tabControlMain);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.mainMenu;
            this.Name = "mainForm";
            this.Text = "TicketValidator";
            this.Closed += new System.EventHandler(this.mainForm_Closed);
            this.Closing += new System.ComponentModel.CancelEventHandler(this.mainForm_Closing);
            this.tabControlMain.ResumeLayout(false);
            this.tabPageScan.ResumeLayout(false);
            this.tabPageList.ResumeLayout(false);
            this.tabPageSystem.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControlMain;
        private System.Windows.Forms.TabPage tabPageScan;
        private System.Windows.Forms.TabPage tabPageList;
        private System.Windows.Forms.Label labelOpen;
        private System.Windows.Forms.TabPage tabPageSystem;
        private System.Windows.Forms.Button buttonImport;
        private System.Windows.Forms.Label labelRedeemed;
        private System.Windows.Forms.Button buttonRedeem;
        private System.Windows.Forms.Label labelCodeInfo;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonResetRedeemed;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.ListBox listBoxCards;
    }
}

