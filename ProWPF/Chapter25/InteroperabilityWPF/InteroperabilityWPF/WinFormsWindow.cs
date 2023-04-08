using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
//------------------------------------------------------------------------
namespace InteroperabilityWPF
{
//------------------------------------------------------------------------
	public partial class WinFormsWindow:Form
	{
//------------------------------------------------------------------------
		public WinFormsWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void MClose_Click(object Sender, EventArgs E)
		{
			Close();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------