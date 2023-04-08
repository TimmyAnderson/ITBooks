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
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace WPFWindowLibrary
{
//------------------------------------------------------------------------
	public partial class MyWPFUserControl:UserControl
	{
//------------------------------------------------------------------------
		public MyWPFUserControl()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show(string.Format("WPF Text: {0} !",MTextBox.Text));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------