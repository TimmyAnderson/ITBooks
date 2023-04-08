namespace NotifyIconTest
{
	partial class NotifyIconWrapper
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
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NotifyIconWrapper));
			this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
			this.MMNUMain = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.MMNUClose = new System.Windows.Forms.ToolStripMenuItem();
			this.MMNUShowMessageBox = new System.Windows.Forms.ToolStripMenuItem();
			this.MMNUMain.SuspendLayout();
			// 
			// notifyIcon1
			// 
			this.notifyIcon1.ContextMenuStrip = this.MMNUMain;
			this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
			this.notifyIcon1.Text = "This is my WPF Application !";
			this.notifyIcon1.Visible = true;
			// 
			// MMNUMain
			// 
			this.MMNUMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MMNUShowMessageBox,
            this.MMNUClose});
			this.MMNUMain.Name = "MMNUShowMessageBox";
			this.MMNUMain.Size = new System.Drawing.Size(126,26);
			this.MMNUMain.Text = "Show Message";
			// 
			// MMNUClose
			// 
			this.MMNUClose.Name = "MMNUClose";
			this.MMNUClose.Size = new System.Drawing.Size(125,22);
			this.MMNUClose.Text = "Close";
			// 
			// MMNUShowMessageBox
			// 
			this.MMNUShowMessageBox.Name = "MMNUShowMessageBox";
			this.MMNUShowMessageBox.Size = new System.Drawing.Size(218,22);
			this.MMNUShowMessageBox.Text = "Show Message Box";
			this.MMNUMain.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.NotifyIcon notifyIcon1;
		private System.Windows.Forms.ContextMenuStrip MMNUMain;
		private System.Windows.Forms.ToolStripMenuItem MMNUClose;
		private System.Windows.Forms.ToolStripMenuItem MMNUShowMessageBox;
	}
}
