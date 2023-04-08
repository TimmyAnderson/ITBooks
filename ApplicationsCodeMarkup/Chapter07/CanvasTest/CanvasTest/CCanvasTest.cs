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
namespace CanvasTest
{
//------------------------------------------------------------------------------
	public class CCanvasTest : Window
	{
//------------------------------------------------------------------------------
		public CCanvasTest()
		{
            Title = "Paint the Button";

            Button			Btn=new Button();

            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.VerticalAlignment=VerticalAlignment.Center;
            Content=Btn;

            Canvas			Canv=new Canvas();

            Canv.Width=144;
            Canv.Height=144;
            Btn.Content=Canv;

            Rectangle		Rect=new Rectangle();

            Rect.Width=Canv.Width;
            Rect.Height=Canv.Height;
            Rect.RadiusX=24;
            Rect.RadiusY=24;
            Rect.Fill=Brushes.Blue;
            Canv.Children.Add(Rect);
            Canvas.SetLeft(Rect, 0);
            Canvas.SetRight(Rect, 0);

            Polygon			Poly=new Polygon();

            Poly.Fill=Brushes.Yellow;
            Poly.Points=new PointCollection();

            for (int i=0;i<5;i++)
            {
                double		Angle = i*4*Math.PI/5;
                Point		PT=new Point(48 * Math.Sin(Angle), -48 * Math.Cos(Angle));

                Poly.Points.Add(PT);
            }

            Canv.Children.Add(Poly);
            Canvas.SetLeft(Poly, Canv.Width/2);
            Canvas.SetTop(Poly, Canv.Height/2);
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------