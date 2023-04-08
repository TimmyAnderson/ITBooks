using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Shapes;
//-------------------------------------------------------------------------------------------------------
namespace Animations
{
//-------------------------------------------------------------------------------------------------------
	public partial class SplineKeyFrameExperiment : Window
	{
//-------------------------------------------------------------------------------------------------------
		// Riadiace body.
        public static DependencyProperty						ControlPoint1Property=DependencyProperty.Register("ControlPoint1", typeof(Point),typeof(SplineKeyFrameExperiment),new PropertyMetadata(new Point(0, 0), ControlPointOnChanged));
        public static DependencyProperty						ControlPoint2Property=DependencyProperty.Register("ControlPoint2", typeof(Point),typeof(SplineKeyFrameExperiment),new PropertyMetadata(new Point(1, 1), ControlPointOnChanged));
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public SplineKeyFrameExperiment()
        {
            InitializeComponent();

            for (int i=0;i<=10;i++)
            {
                TextBlock			Txtblk=new TextBlock();

                Txtblk.Text=(i/10m).ToString("N1");

                MCanvMain.Children.Add(Txtblk);
                Canvas.SetLeft(Txtblk, 40 + 48 * i);
                Canvas.SetTop(Txtblk, 14);

                Line				LLine=new Line();

                LLine.X1=48*(i+1);
                LLine.Y1=30;
                LLine.X2=LLine.X1;
                LLine.Y2=528;
                LLine.Stroke=Brushes.Black;
                MCanvMain.Children.Add(LLine);

                Txtblk=new TextBlock();
                Txtblk.Text=(i/10m).ToString("N1");
                MCanvMain.Children.Add(Txtblk);
                Canvas.SetLeft(Txtblk, 5);
                Canvas.SetTop(Txtblk, 40+(48*i));

                LLine=new Line();
                LLine.X1=30;
                LLine.Y1=48*(i+1);
                LLine.X2=528;
                LLine.Y2=LLine.Y1;
                LLine.Stroke=Brushes.Black;
                MCanvMain.Children.Add(LLine);
            }

            UpdateLabel();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public Point											ControlPoint1
        {
            get
			{
				return((Point)GetValue(ControlPoint1Property));
			}
            set
			{
				SetValue(ControlPoint1Property, value);
			}
        }
//-------------------------------------------------------------------------------------------------------
        public Point											ControlPoint2
        {
            get
			{
				return((Point)GetValue(ControlPoint2Property));
			}
            set
			{
				SetValue(ControlPoint2Property, value);
			}
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private static void ControlPointOnChanged(DependencyObject Obj, DependencyPropertyChangedEventArgs Args)
        {
            SplineKeyFrameExperiment	Win=Obj as SplineKeyFrameExperiment;

            if (Args.Property==ControlPoint1Property)
                Win.MSpline.ControlPoint1=(Point) Args.NewValue;
            else if (Args.Property==ControlPoint2Property)
                Win.MSpline.ControlPoint2=(Point) Args.NewValue;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void CanvasOnMouse(object Sender, MouseEventArgs Args)
        {
            Canvas			Canv=Sender as Canvas;
            Point			PTMouse=Args.GetPosition(Canv);

            PTMouse.X=Math.Min(1, Math.Max(0, PTMouse.X/Canv.ActualWidth));
            PTMouse.Y=Math.Min(1, Math.Max(0, PTMouse.Y/Canv.ActualHeight));

            if (Args.LeftButton==MouseButtonState.Pressed)
                ControlPoint1=PTMouse;

            if (Args.RightButton==MouseButtonState.Pressed)
                ControlPoint2=PTMouse;

            if (Args.LeftButton==MouseButtonState.Pressed || Args.RightButton==MouseButtonState.Pressed)
                    UpdateLabel();
        }
//-------------------------------------------------------------------------------------------------------
        private void UpdateLabel()
        {
            MLblInfo.Content=string.Format("Left mouse button changes ControlPoint1 = ({0:F2}) !\nRight mouse button changes ControlPoint2 = ({1:F2}) !", ControlPoint1, ControlPoint2);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------