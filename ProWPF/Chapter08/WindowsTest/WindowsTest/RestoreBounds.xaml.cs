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
using System.Diagnostics;
//------------------------------------------------------------------------
namespace WindowsTest
{
//------------------------------------------------------------------------
	public partial class RestoreBounds:System.Windows.Window
	{
//------------------------------------------------------------------------
		public RestoreBounds()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("RestoreBounds: {0} !",this.RestoreBounds));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------