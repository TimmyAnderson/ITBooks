using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace ToolBarTest
{
//------------------------------------------------------------------------
	public partial class ToolBarTrayTest:System.Windows.Window
	{
//------------------------------------------------------------------------
		public ToolBarTrayTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(string.Format("ToolBar1.Band={0} !",MToolBar1.Band));
			Debug.WriteLine(string.Format("ToolBar2.Band={0} !",MToolBar2.Band));
			Debug.WriteLine(string.Format("ToolBar3.Band={0} !",MToolBar3.Band));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------