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
//-------------------------------------------------------------------------------------------------------
namespace Shapes
{
//-------------------------------------------------------------------------------------------------------
	public class Spiral : Window
	{
//-------------------------------------------------------------------------------------------------------
        private const int										REVS=20;
        private const int										NUM_PTS=1000*REVS;
//-------------------------------------------------------------------------------------------------------
        private Polyline										MPoly;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public Spiral()
		{
            Title = "Spiral";

            Canvas				Canv=new Canvas();

            Canv.SizeChanged+=CanvasOnSizeChanged;
            Content=Canv;

            MPoly=new Polyline();
            MPoly.Stroke=SystemColors.WindowTextBrush;
            Canv.Children.Add(MPoly);

            Point[]				Pts=new Point[NUM_PTS];

            for (int i=0;i<NUM_PTS;i++)
            {
                double			Angle=i*2*Math.PI/(NUM_PTS/REVS);
                double			Scale=250*(1-(double) i/NUM_PTS);

                Pts[i].X=Scale*Math.Cos(Angle);
                Pts[i].Y=Scale*Math.Sin(Angle);
            }

            MPoly.Points=new PointCollection(Pts);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void CanvasOnSizeChanged(object Sender, SizeChangedEventArgs Args)
        {
            Canvas.SetLeft(MPoly, Args.NewSize.Width/2);
            Canvas.SetTop(MPoly, Args.NewSize.Height/2);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------