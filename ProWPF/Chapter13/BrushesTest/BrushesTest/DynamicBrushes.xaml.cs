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
namespace BrushesTest
{
//------------------------------------------------------------------------
	public partial class DynamicBrushes:System.Windows.Window
	{
//------------------------------------------------------------------------
		public DynamicBrushes()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			MButton1.Background=new SolidColorBrush(Colors.SkyBlue);
			MButton2.Foreground=new SolidColorBrush(Colors.SkyBlue);
			MEllipse.Fill=new SolidColorBrush(Colors.SkyBlue);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------