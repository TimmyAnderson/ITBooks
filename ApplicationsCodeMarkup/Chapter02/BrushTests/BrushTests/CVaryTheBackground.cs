using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace BrushTests
{
//------------------------------------------------------------------------------
    public class CVaryTheBackground : Window
    {
//------------------------------------------------------------------------------
        private SolidColorBrush						MBrush=new SolidColorBrush(Colors.Black);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CVaryTheBackground()
        {
            Title="Vary the Background";
            Width=384;
            Height=384;
            Background=MBrush;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs Args)
        {
            double			Width=ActualWidth-(2*SystemParameters.ResizeFrameVerticalBorderWidth);
            double			Height=ActualHeight-(2*SystemParameters.ResizeFrameHorizontalBorderHeight-SystemParameters.CaptionHeight);
            Point			PTMouse=Args.GetPosition(this);
            Point			PTCenter=new Point(Width/2,Height/2);
            Vector			VectMouse=PTMouse-PTCenter;
            double			Angle=Math.Atan2(VectMouse.Y,VectMouse.X);
            Vector			VectEllipse=new Vector((Width/2)*Math.Cos(Angle),(Height/2)*Math.Sin(Angle));
            byte			ByLevel=(byte) (255 * (1-Math.Min(1,VectMouse.Length/VectEllipse.Length)));
            Color			Clr=MBrush.Color;

            Clr.R=Clr.G=Clr.B=ByLevel;
            MBrush.Color=Clr;

			Console.WriteLine(string.Format("RGB: [{0}, {1}, {2}], SCRGB: [{3}, {4}, {5}] !",MBrush.Color.R,MBrush.Color.G,MBrush.Color.B,MBrush.Color.ScR,MBrush.Color.ScG,MBrush.Color.ScB));
        }
//------------------------------------------------------------------------------
    }
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------