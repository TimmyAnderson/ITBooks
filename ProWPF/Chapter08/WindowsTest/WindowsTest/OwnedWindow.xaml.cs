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
namespace WindowsTest
{
//------------------------------------------------------------------------
	public partial class OwnedWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public OwnedWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			Close();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------