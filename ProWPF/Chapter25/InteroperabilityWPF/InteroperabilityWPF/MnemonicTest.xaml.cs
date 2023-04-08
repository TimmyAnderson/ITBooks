using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace InteroperabilityWPF
{
//------------------------------------------------------------------------
	public partial class MnemonicTest:Window
	{
//------------------------------------------------------------------------
		public MnemonicTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void WPFButton_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show(string.Format("WPF Button: {0} CLICKED !",Sender));
		}
//------------------------------------------------------------------------
		private void WinFormsButton_Click(object Sender, EventArgs E)
		{
			MessageBox.Show(string.Format("WinForms Button: {0} CLICKED !",Sender));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------