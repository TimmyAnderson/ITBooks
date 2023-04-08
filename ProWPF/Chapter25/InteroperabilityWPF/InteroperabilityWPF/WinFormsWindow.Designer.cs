namespace InteroperabilityWPF
{
	partial class WinFormsWindow
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
			this.label1 = new System.Windows.Forms.Label();
			this.MClose = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(56,19);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(180,23);
			this.label1.TabIndex = 0;
			this.label1.Text = "This is WinForms Window !";
			// 
			// MClose
			// 
			this.MClose.Location = new System.Drawing.Point(109,233);
			this.MClose.Name = "MClose";
			this.MClose.Size = new System.Drawing.Size(75,23);
			this.MClose.TabIndex = 1;
			this.MClose.Text = "Close";
			this.MClose.UseVisualStyleBackColor = true;
			this.MClose.Click += new System.EventHandler(this.MClose_Click);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12,65);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(79,17);
			this.label2.TabIndex = 2;
			this.label2.Text = "Some Text:";
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(12,85);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(268,22);
			this.textBox1.TabIndex = 3;
			// 
			// WinFormsWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F,16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292,268);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.MClose);
			this.Controls.Add(this.label1);
			this.Name = "WinFormsWindow";
			this.Text = "WinFormsWindow";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button MClose;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox1;
	}
}