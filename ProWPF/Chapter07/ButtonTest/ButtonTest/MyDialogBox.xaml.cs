using System;
using System.Collections.Generic;
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
namespace ButtonTest
{
//------------------------------------------------------------------------
	public partial class MyDialogBox:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MyDialogBox()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnOKClick(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("OK Clicked !");

			// !!! Musim rucne zavolat Close().
			this.Close();
		}
//------------------------------------------------------------------------
		private void OnCancelClick(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("Cancel Clicked !");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------