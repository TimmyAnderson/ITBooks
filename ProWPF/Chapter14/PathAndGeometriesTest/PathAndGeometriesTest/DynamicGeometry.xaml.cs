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
namespace PathAndGeometriesTest
{
//------------------------------------------------------------------------
	public partial class DynamicGeometry:System.Windows.Window
	{
//------------------------------------------------------------------------
		public DynamicGeometry()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			MPath.Fill=new SolidColorBrush(Colors.Red);

			RectangleGeometry		RG=(RectangleGeometry) MPath.Data;

			RG.Rect=new Rect(new Point(50,50),new Point(100,100));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------