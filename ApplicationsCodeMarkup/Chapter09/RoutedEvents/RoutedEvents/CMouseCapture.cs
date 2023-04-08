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
using System.Windows.Documents;
//------------------------------------------------------------------------------
namespace RoutedEvents
{
//------------------------------------------------------------------------------
	public class CMouseCapture : Window
	{
//------------------------------------------------------------------------------
        private Canvas								MCanvas;
        private bool								MIsDrawing;
        private Ellipse								MEllipse;
        private Point								MPTCenter;
        private bool								MIsDragging;
        private FrameworkElement					MElementDragging;
        private Point								MPTMouseStart;
		private Point								MPTElementStart;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CMouseCapture()
		{
            Title="Draw Circles";
            Content=MCanvas=new Canvas();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs Args)
        {
            base.OnMouseLeftButtonDown(Args);

            if (MIsDragging==true)
                return;

            MPTCenter=Args.GetPosition(MCanvas);
            MEllipse=new Ellipse();
            MEllipse.Stroke=SystemColors.WindowTextBrush;
            MEllipse.StrokeThickness=1;
            MEllipse.Width=0;
            MEllipse.Height=0;
            MCanvas.Children.Add(MEllipse);
            Canvas.SetLeft(MEllipse, MPTCenter.X);
            Canvas.SetTop(MEllipse, MPTCenter.Y);

            CaptureMouse();
            MIsDrawing=true;
        }
//------------------------------------------------------------------------------
        protected override void OnMouseRightButtonDown(MouseButtonEventArgs Args)
        {
            base.OnMouseRightButtonDown(Args);

            if (MIsDrawing==true)
                return;

            MPTMouseStart=Args.GetPosition(MCanvas);
            MElementDragging=MCanvas.InputHitTest(MPTMouseStart) as FrameworkElement;

            if (MElementDragging!=null)
            {
                MPTElementStart=new Point(Canvas.GetLeft(MElementDragging), Canvas.GetTop(MElementDragging));
                MIsDragging=true;
            }
        }
//------------------------------------------------------------------------------
        protected override void OnMouseDown(MouseButtonEventArgs Args)
        {
            base.OnMouseDown(Args);

            if (Args.ChangedButton==MouseButton.Middle)
            {
                Shape		LShape=MCanvas.InputHitTest(Args.GetPosition(MCanvas)) as Shape;

                if (LShape!=null)
                    LShape.Fill=(LShape.Fill==Brushes.Red ? Brushes.Transparent : Brushes.Red);
            }
        }
//------------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs Args)
        {
            base.OnMouseMove(Args);

            Point			LPTMouse=Args.GetPosition(MCanvas);

            if (MIsDrawing==true)
            {
                double		DRadius=Math.Sqrt(Math.Pow(MPTCenter.X - LPTMouse.X, 2) + Math.Pow(MPTCenter.Y - LPTMouse.Y, 2));

                Canvas.SetLeft(MEllipse, MPTCenter.X-DRadius);
                Canvas.SetTop(MEllipse, MPTCenter.Y-DRadius);
                MEllipse.Width=2*DRadius;
                MEllipse.Height=2*DRadius;
            }
            else if (MIsDragging==true)
            {
                Canvas.SetLeft(MElementDragging, MPTElementStart.X+LPTMouse.X - MPTMouseStart.X);
                Canvas.SetTop(MElementDragging, MPTElementStart.Y+LPTMouse.Y - MPTMouseStart.Y);
            }
        }
//------------------------------------------------------------------------------
        protected override void OnMouseUp(MouseButtonEventArgs Args)
        {
            base.OnMouseUp(Args);

            if (MIsDrawing==true && Args.ChangedButton==MouseButton.Left)
            {
                MEllipse.Stroke=Brushes.Blue;
                MEllipse.StrokeThickness=Math.Min(24, MEllipse.Width/2);
                MEllipse.Fill=Brushes.Red;

                MIsDrawing=false;
                ReleaseMouseCapture();
            }
            else if (MIsDragging==true && Args.ChangedButton==MouseButton.Right)
            {
                MIsDragging=false;
            }
        }
//------------------------------------------------------------------------------
        protected override void OnTextInput(TextCompositionEventArgs Args)
        {
            base.OnTextInput(Args);

            if (Args.Text.IndexOf('\x1B')!=-1)
            {
                if (MIsDrawing==true)
                    ReleaseMouseCapture();

                else if (MIsDragging==true)
                {
                    Canvas.SetLeft(MElementDragging, MPTElementStart.X);
                    Canvas.SetTop(MElementDragging, MPTElementStart.Y);
                    MIsDragging=false;
                }
            }
        }
//------------------------------------------------------------------------------
        protected override void OnLostMouseCapture(MouseEventArgs Args)
        {
            base.OnLostMouseCapture(Args);

            if (MIsDrawing==true)
            {
                MCanvas.Children.Remove(MEllipse);
                MIsDrawing=false;
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------