namespace UseSynchronizationContextLibrary
{
	partial class CMyForm
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
			this.MLABLabel = new System.Windows.Forms.Label();
			this.MLABCounter = new System.Windows.Forms.Label();
			this.MBUTExit = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// MLABLabel
			// 
			this.MLABLabel.Location = new System.Drawing.Point(12,9);
			this.MLABLabel.Name = "MLABLabel";
			this.MLABLabel.Size = new System.Drawing.Size(268,23);
			this.MLABLabel.TabIndex = 0;
			this.MLABLabel.Text = "Counter:";
			// 
			// MLABCounter
			// 
			this.MLABCounter.Location = new System.Drawing.Point(12,39);
			this.MLABCounter.Name = "MLABCounter";
			this.MLABCounter.Size = new System.Drawing.Size(268,23);
			this.MLABCounter.TabIndex = 1;
			this.MLABCounter.Text = "0";
			this.MLABCounter.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// MBUTExit
			// 
			this.MBUTExit.Location = new System.Drawing.Point(12,78);
			this.MBUTExit.Name = "MBUTExit";
			this.MBUTExit.Size = new System.Drawing.Size(268,23);
			this.MBUTExit.TabIndex = 2;
			this.MBUTExit.Text = "Exit";
			this.MBUTExit.UseVisualStyleBackColor = true;
			this.MBUTExit.Click += new System.EventHandler(this.MBUTExit_Click);
			// 
			// CMyForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F,16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292,113);
			this.Controls.Add(this.MBUTExit);
			this.Controls.Add(this.MLABCounter);
			this.Controls.Add(this.MLABLabel);
			this.Name = "CMyForm";
			this.Text = "CMyForm";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.CMyForm_FormClosed);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Label MLABLabel;
		private System.Windows.Forms.Label MLABCounter;
		private System.Windows.Forms.Button MBUTExit;
	}
}