namespace InteroperabilityWindowsForms
{
	partial class MainForm
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
			this.MButton1 = new System.Windows.Forms.Button();
			this.MButton2 = new System.Windows.Forms.Button();
			this.MGroupBox = new System.Windows.Forms.GroupBox();
			this.MElementHost = new System.Windows.Forms.Integration.ElementHost();
			this.MGroupBox.SuspendLayout();
			this.SuspendLayout();
			// 
			// MButton1
			// 
			this.MButton1.Location = new System.Drawing.Point(50,12);
			this.MButton1.Name = "MButton1";
			this.MButton1.Size = new System.Drawing.Size(193,23);
			this.MButton1.TabIndex = 0;
			this.MButton1.Text = "Modal WPF Window";
			this.MButton1.UseVisualStyleBackColor = true;
			this.MButton1.Click += new System.EventHandler(this.MButton_Click1);
			// 
			// MButton2
			// 
			this.MButton2.Location = new System.Drawing.Point(50,53);
			this.MButton2.Name = "MButton2";
			this.MButton2.Size = new System.Drawing.Size(193,23);
			this.MButton2.TabIndex = 1;
			this.MButton2.Text = "Modeless WPF Window";
			this.MButton2.UseVisualStyleBackColor = true;
			this.MButton2.Click += new System.EventHandler(this.MButton2_Click);
			// 
			// MGroupBox
			// 
			this.MGroupBox.Controls.Add(this.MElementHost);
			this.MGroupBox.Location = new System.Drawing.Point(12,96);
			this.MGroupBox.Name = "MGroupBox";
			this.MGroupBox.Size = new System.Drawing.Size(268,100);
			this.MGroupBox.TabIndex = 2;
			this.MGroupBox.TabStop = false;
			this.MGroupBox.Text = "WPF Content Inside";
			// 
			// MElementHost
			// 
			this.MElementHost.Dock = System.Windows.Forms.DockStyle.Fill;
			this.MElementHost.Location = new System.Drawing.Point(3,18);
			this.MElementHost.Name = "MElementHost";
			this.MElementHost.Size = new System.Drawing.Size(262,79);
			this.MElementHost.TabIndex = 0;
			this.MElementHost.Text = "elementHost1";
			this.MElementHost.Child = null;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F,16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292,268);
			this.Controls.Add(this.MGroupBox);
			this.Controls.Add(this.MButton2);
			this.Controls.Add(this.MButton1);
			this.Name = "MainForm";
			this.Text = "Form1";
			this.MGroupBox.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button MButton1;
		private System.Windows.Forms.Button MButton2;
		private System.Windows.Forms.GroupBox MGroupBox;
		private System.Windows.Forms.Integration.ElementHost MElementHost;
	}
}

