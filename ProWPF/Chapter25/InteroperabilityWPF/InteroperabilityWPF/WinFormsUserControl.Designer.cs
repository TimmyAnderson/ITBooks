namespace InteroperabilityWPF
{
	partial class WinFormsUserControl
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.MButton = new System.Windows.Forms.Button();
			this.MTextBox = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// MButton
			// 
			this.MButton.Location = new System.Drawing.Point(3,59);
			this.MButton.Name = "MButton";
			this.MButton.Size = new System.Drawing.Size(276,23);
			this.MButton.TabIndex = 0;
			this.MButton.Text = "Show Text";
			this.MButton.UseVisualStyleBackColor = true;
			this.MButton.Click += new System.EventHandler(this.MButton_Click);
			// 
			// MTextBox
			// 
			this.MTextBox.Location = new System.Drawing.Point(3,31);
			this.MTextBox.Name = "MTextBox";
			this.MTextBox.Size = new System.Drawing.Size(276,22);
			this.MTextBox.TabIndex = 1;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(3,11);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(155,17);
			this.label1.TabIndex = 2;
			this.label1.Text = "Win Form User Control:";
			// 
			// WinFormUserControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F,16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.label1);
			this.Controls.Add(this.MTextBox);
			this.Controls.Add(this.MButton);
			this.Name = "WinFormUserControl";
			this.Size = new System.Drawing.Size(282,92);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button MButton;
		private System.Windows.Forms.TextBox MTextBox;
		private System.Windows.Forms.Label label1;
	}
}
