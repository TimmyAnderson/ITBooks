using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
//-------------------------------------------------------------------------------------------------------
namespace PathAndGeometries
{
//-------------------------------------------------------------------------------------------------------
	public class BezierReproduce : BezierExperimenter
	{
//-------------------------------------------------------------------------------------------------------
        private Polyline										MBezier;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public BezierReproduce()
        {
            Title="Bezier Reproduce";

            MBezier=new Polyline();
            MBezier.Stroke = Brushes.Blue;
            MCanvas.Children.Add(MBezier);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void DrawBezierManually()
        {
            Point[]			PTS=new Point[10];

            for (int i = 0; i < PTS.Length; i++)
            {
                double		T=(double) (i/(PTS.Length-1));
                double		X=(1 - T) * (1 - T) * (1 - T) * MPtStart.Center.X + 3 * T * (1 - T) * (1 - T) * MPtCtrl1.Center.X + 3 * T * T * (1 - T) * MPtCtrl2.Center.X + T * T * T * MPtEnd.Center.X;
                double		Y=(1 - T) * (1 - T) * (1 - T) * MPtStart.Center.Y + 3 * T * (1 - T) * (1 - T) * MPtCtrl1.Center.Y + 3 * T * T * (1 - T) * MPtCtrl2.Center.Y + T * T * T * MPtEnd.Center.Y;

                PTS[i]=new Point(X, Y);
            }

            MBezier.Points=new PointCollection(PTS);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected override void CanvasOnSizeChanged(object Sender, SizeChangedEventArgs Args)
        {
            base.CanvasOnSizeChanged(Sender, Args);
            DrawBezierManually();
        }
//-------------------------------------------------------------------------------------------------------
        protected override void OnMouseDown(MouseButtonEventArgs Args)
        {
            base.OnMouseDown(Args);
            DrawBezierManually();
        }
//-------------------------------------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs Args)
        {
            base.OnMouseMove(Args);
            DrawBezierManually();
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------