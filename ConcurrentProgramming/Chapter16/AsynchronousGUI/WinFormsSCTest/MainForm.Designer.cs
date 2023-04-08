namespace WinFormsSCTest
{
	partial class MFRMMainForm
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
			this.MBUTButton = new System.Windows.Forms.Button();
			this.MLABLabel = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// MBUTButton
			// 
			this.MBUTButton.Location = new System.Drawing.Point(106,37);
			this.MBUTButton.Name = "MBUTButton";
			this.MBUTButton.Size = new System.Drawing.Size(75,29);
			this.MBUTButton.TabIndex = 0;
			this.MBUTButton.Text = "Run";
			this.MBUTButton.UseVisualStyleBackColor = true;
			this.MBUTButton.Click += new System.EventHandler(this.MBUTButton_Click);
			// 
			// MLABLabel
			// 
			this.MLABLabel.Location = new System.Drawing.Point(12,9);
			this.MLABLabel.Name = "MLABLabel";
			this.MLABLabel.Size = new System.Drawing.Size(268,23);
			this.MLABLabel.TabIndex = 1;
			// 
			// MFRMMainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F,16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292,74);
			this.Controls.Add(this.MLABLabel);
			this.Controls.Add(this.MBUTButton);
			this.Name = "MFRMMainForm";
			this.Text = "MainForm";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button MBUTButton;
		private System.Windows.Forms.Label MLABLabel;
	}
}