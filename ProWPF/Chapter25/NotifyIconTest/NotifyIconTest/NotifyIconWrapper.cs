using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;
//------------------------------------------------------------------------
namespace NotifyIconTest
{
//------------------------------------------------------------------------
	public partial class NotifyIconWrapper:Component
	{
//------------------------------------------------------------------------
		public NotifyIconWrapper()
		{
			InitializeComponent();

			MMNUShowMessageBox.Click+=new EventHandler(MMNUShowMessageBox_Click);
			MMNUClose.Click+=new EventHandler(MMNUClose_Click);
		}
//------------------------------------------------------------------------
		public NotifyIconWrapper(IContainer Container)
		{
			Container.Add(this);

			InitializeComponent();

			MMNUShowMessageBox.Click+=new EventHandler(MMNUShowMessageBox_Click);
			MMNUClose.Click+=new EventHandler(MMNUClose_Click);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void MMNUShowMessageBox_Click(object Sender, EventArgs E)
		{
			MessageBox.Show("Hello !!!","Action");
		}
//------------------------------------------------------------------------
		private void MMNUClose_Click(object Sender, EventArgs E)
		{
			System.Windows.Application.Current.Shutdown();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------