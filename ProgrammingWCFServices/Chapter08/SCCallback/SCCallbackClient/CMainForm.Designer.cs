namespace SCCallbackClient
{
	partial class CMainForm
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
			if(disposing && (components != null))
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
			this.MBUTWithout = new System.Windows.Forms.Button();
			this.MBUTWith = new System.Windows.Forms.Button();
			this.MBUTExit = new System.Windows.Forms.Button();
			this.MLABRecords = new System.Windows.Forms.Label();
			this.MLBXRecords = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// MBUTWithout
			// 
			this.MBUTWithout.Location = new System.Drawing.Point(28,166);
			this.MBUTWithout.Name = "MBUTWithout";
			this.MBUTWithout.Size = new System.Drawing.Size(75,23);
			this.MBUTWithout.TabIndex = 0;
			this.MBUTWithout.Text = "Without";
			this.MBUTWithout.UseVisualStyleBackColor = true;
			this.MBUTWithout.Click += new System.EventHandler(this.MBUTWithout_Click);
			// 
			// MBUTWith
			// 
			this.MBUTWith.Location = new System.Drawing.Point(109,166);
			this.MBUTWith.Name = "MBUTWith";
			this.MBUTWith.Size = new System.Drawing.Size(75,23);
			this.MBUTWith.TabIndex = 1;
			this.MBUTWith.Text = "With";
			this.MBUTWith.UseVisualStyleBackColor = true;
			this.MBUTWith.Click += new System.EventHandler(this.MBUTWith_Click);
			// 
			// MBUTExit
			// 
			this.MBUTExit.Location = new System.Drawing.Point(190,166);
			this.MBUTExit.Name = "MBUTExit";
			this.MBUTExit.Size = new System.Drawing.Size(75,23);
			this.MBUTExit.TabIndex = 2;
			this.MBUTExit.Text = "Exit";
			this.MBUTExit.UseVisualStyleBackColor = true;
			this.MBUTExit.Click += new System.EventHandler(this.MBUTExit_Click);
			// 
			// MLABRecords
			// 
			this.MLABRecords.AutoSize = true;
			this.MLABRecords.Location = new System.Drawing.Point(12,9);
			this.MLABRecords.Name = "MLABRecords";
			this.MLABRecords.Size = new System.Drawing.Size(61,17);
			this.MLABRecords.TabIndex = 3;
			this.MLABRecords.Text = "Records";
			// 
			// MLBXRecords
			// 
			this.MLBXRecords.FormattingEnabled = true;
			this.MLBXRecords.ItemHeight = 16;
			this.MLBXRecords.Location = new System.Drawing.Point(12,29);
			this.MLBXRecords.Name = "MLBXRecords";
			this.MLBXRecords.Size = new System.Drawing.Size(268,132);
			this.MLBXRecords.TabIndex = 4;
			// 
			// CMainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F,16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292,198);
			this.Controls.Add(this.MLBXRecords);
			this.Controls.Add(this.MLABRecords);
			this.Controls.Add(this.MBUTExit);
			this.Controls.Add(this.MBUTWith);
			this.Controls.Add(this.MBUTWithout);
			this.Name = "CMainForm";
			this.Text = "CMainForm";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.CMainForm_FormClosed);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button MBUTWithout;
		private System.Windows.Forms.Button MBUTWith;
		private System.Windows.Forms.Button MBUTExit;
		private System.Windows.Forms.Label MLABRecords;
		public System.Windows.Forms.ListBox MLBXRecords;
	}
}

