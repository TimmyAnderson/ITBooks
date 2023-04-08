using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
//------------------------------------------------------------------------
namespace InteroperabilityWPF
{
//------------------------------------------------------------------------
	public partial class WinFormsUserControl:UserControl
	{
//------------------------------------------------------------------------
		public WinFormsUserControl()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public string						TextBoxString
		{
			get
			{
				return(MTextBox.Text);
			}
			set
			{
				MTextBox.Text=value;
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void MButton_Click(object Sender, EventArgs E)
		{
			MessageBox.Show(string.Format("WinForms Text: {0} !",MTextBox.Text));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------