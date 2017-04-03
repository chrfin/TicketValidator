namespace TicketValidator
{
    partial class ServiceSelection
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.MainMenu mainMenu1;

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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ServiceSelection));
            this.mainMenu1 = new System.Windows.Forms.MainMenu();
            this.buttonTest = new System.Windows.Forms.Button();
            this.labelUri = new System.Windows.Forms.Label();
            this.buttonOk = new System.Windows.Forms.Button();
            this.labelTest = new System.Windows.Forms.Label();
            this.comboBoxUri = new System.Windows.Forms.ComboBox();
            this.labelInfo = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonTest
            // 
            resources.ApplyResources(this.buttonTest, "buttonTest");
            this.buttonTest.Name = "buttonTest";
            this.buttonTest.Click += new System.EventHandler(this.buttonTest_Click);
            // 
            // labelUri
            // 
            resources.ApplyResources(this.labelUri, "labelUri");
            this.labelUri.Name = "labelUri";
            // 
            // buttonOk
            // 
            resources.ApplyResources(this.buttonOk, "buttonOk");
            this.buttonOk.Name = "buttonOk";
            this.buttonOk.Click += new System.EventHandler(this.buttonOk_Click);
            // 
            // labelTest
            // 
            resources.ApplyResources(this.labelTest, "labelTest");
            this.labelTest.Name = "labelTest";
            // 
            // comboBoxUri
            // 
            this.comboBoxUri.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDown;
            this.comboBoxUri.Items.Add(resources.GetString("comboBoxUri.Items"));
            this.comboBoxUri.Items.Add(resources.GetString("comboBoxUri.Items1"));
            resources.ApplyResources(this.comboBoxUri, "comboBoxUri");
            this.comboBoxUri.Name = "comboBoxUri";
            this.comboBoxUri.TextChanged += new System.EventHandler(this.comboBoxUri_TextChanged);
            // 
            // labelInfo
            // 
            resources.ApplyResources(this.labelInfo, "labelInfo");
            this.labelInfo.Name = "labelInfo";
            // 
            // labelStatus
            // 
            resources.ApplyResources(this.labelStatus, "labelStatus");
            this.labelStatus.Name = "labelStatus";
            // 
            // buttonCancel
            // 
            resources.ApplyResources(this.buttonCancel, "buttonCancel");
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // ServiceSelection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            resources.ApplyResources(this, "$this");
            this.ControlBox = false;
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.labelStatus);
            this.Controls.Add(this.labelInfo);
            this.Controls.Add(this.comboBoxUri);
            this.Controls.Add(this.labelTest);
            this.Controls.Add(this.buttonOk);
            this.Controls.Add(this.labelUri);
            this.Controls.Add(this.buttonTest);
            this.Name = "ServiceSelection";
            this.TopMost = true;
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonTest;
        private System.Windows.Forms.Label labelUri;
        private System.Windows.Forms.Button buttonOk;
        private System.Windows.Forms.Label labelTest;
        private System.Windows.Forms.ComboBox comboBoxUri;
        private System.Windows.Forms.Label labelInfo;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.Button buttonCancel;
    }
}