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
	public class CComplexEllipseElementWindow : Window
	{
//------------------------------------------------------------------------------
		private CCompexEllipseElement						MEllipse;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CComplexEllipseElementWindow(int Index)
		{
            Title="Render the Better Ellipse";

            MEllipse=new CCompexEllipseElement();

            MEllipse.Fill=Brushes.AliceBlue;
            MEllipse.Stroke=new Pen(new LinearGradientBrush(Colors.CadetBlue, Colors.Chocolate, new Point(1, 0), new Point(0, 1)),24);

            Content=MEllipse;

			MEllipse.Margin=new Thickness(2);

			if (Index==2)
			{
				// !!! Tym, ze ZRUSIM DEFUALT hodnoty pre Alignment, ktore boli nastavene na Stretch, dostane Ellipse velkost 0 a vykresli sa IBA PEN o sirke 24 pixelov.
				MEllipse.HorizontalAlignment=HorizontalAlignment.Center;
				MEllipse.VerticalAlignment=VerticalAlignment.Center;
			}
			else if (Index==3)
			{
				MEllipse.HorizontalAlignment=HorizontalAlignment.Center;
				MEllipse.VerticalAlignment=VerticalAlignment.Center;

				MEllipse.Width=30;
				MEllipse.Height=30;
			}
			else if (Index==4)
			{
				MEllipse.HorizontalAlignment=HorizontalAlignment.Center;
				MEllipse.VerticalAlignment=VerticalAlignment.Center;

				MEllipse.Width=10;
				MEllipse.Height=10;
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