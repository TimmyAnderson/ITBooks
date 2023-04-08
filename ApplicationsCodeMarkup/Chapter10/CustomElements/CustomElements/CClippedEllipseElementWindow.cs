using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace CustomElements
{
//------------------------------------------------------------------------------
	public class CClippedEllipseElementWindow : Window
	{
//------------------------------------------------------------------------------
		private CClippedEllipseElement				MEllipse;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CClippedEllipseElementWindow(int Index)
		{
            Title="Render the Better Ellipse";

            MEllipse=new CClippedEllipseElement();

            MEllipse.Fill=Brushes.AliceBlue;
            MEllipse.Stroke=new Pen(new LinearGradientBrush(Colors.CadetBlue, Colors.Chocolate, new Point(1, 0), new Point(0, 1)),24);

            Content=MEllipse;

			MEllipse.Margin=new Thickness(2);

			MEllipse.Width=50;
			MEllipse.Height=50;

			if (Index==2)
			{
				MEllipse.HorizontalAlignment=HorizontalAlignment.Center;
				MEllipse.VerticalAlignment=VerticalAlignment.Center;
			}
		}
//------------------------------------------------------------------------------
		protected override void OnKeyDown(KeyEventArgs E)
		{
			base.OnKeyDown(E);

			Console.WriteLine(string.Format("Render size: [{0},{1}] !",MEllipse.RenderSize.Width,MEllipse.RenderSize.Height));
			Console.WriteLine(string.Format("Actual size: [{0},{1}] !",MEllipse.ActualWidth,MEllipse.ActualHeight));
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------