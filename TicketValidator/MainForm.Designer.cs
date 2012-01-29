namespace TicketValidator
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.mainMenu = new System.Windows.Forms.MainMenu();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonRedeem = new System.Windows.Forms.Button();
            this.labelCodeInfo = new System.Windows.Forms.Label();
            this.buttonClose = new System.Windows.Forms.Button();
            this.buttonSelectService = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonCancel
            // 
            resources.ApplyResources(this.buttonCancel, "buttonCancel");
            this.buttonCancel.BackColor = System.Drawing.Color.Pink;
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonRedeem
            // 
            resources.ApplyResources(this.buttonRedeem, "buttonRedeem");
            this.buttonRedeem.BackColor = System.Drawing.Color.LightGreen;
            this.buttonRedeem.Name = "buttonRedeem";
            this.buttonRedeem.Click += new System.EventHandler(this.buttonRedeem_Click);
            // 
            // labelCodeInfo
            // 
            resources.ApplyResources(this.labelCodeInfo, "labelCodeInfo");
            this.labelCodeInfo.Name = "labelCodeInfo";
            // 
            // buttonClose
            // 
            resources.ApplyResources(this.buttonClose, "buttonClose");
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // buttonSelectService
            // 
            resources.ApplyResources(this.buttonSelectService, "buttonSelectService");
            this.buttonSelectService.Name = "buttonSelectService";
            this.buttonSelectService.Click += new System.EventHandler(this.buttonSelectService_Click);
            // 
            // mainForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            resources.ApplyResources(this, "$this");
            this.Controls.Add(this.buttonSelectService);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonRedeem);
            this.Controls.Add(this.labelCodeInfo);
            this.Menu = this.mainMenu;
            this.Name = "mainForm";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
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
        private System.Windows.Forms.Button buttonSelectService;

    }
}

