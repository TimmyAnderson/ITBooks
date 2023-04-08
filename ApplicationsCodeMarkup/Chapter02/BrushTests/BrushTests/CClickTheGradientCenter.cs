using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace BrushTests
{
//------------------------------------------------------------------------------
	public class CClickTheGradientCenter : Window
	{
//------------------------------------------------------------------------------
        private RadialGradientBrush					MBrush;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CClickTheGradientCenter()
        {
            Title="Click the Gradient Center";

            MBrush=new RadialGradientBrush(Colors.White, Colors.Red);
            MBrush.RadiusX=MBrush.RadiusY = 0.10;
            MBrush.SpreadMethod=GradientSpreadMethod.Repeat;
            Background=MBrush;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override void OnMouseDown(MouseButtonEventArgs Args)
        {
            double			Width=ActualWidth-(2*SystemParameters.ResizeFrameVerticalBorderWidth);
            double			Height=ActualHeight-(2*SystemParameters.ResizeFrameHorizontalBorderHeight)-SystemParameters.CaptionHeight;
            Point			PTMouse=Args.GetPosition(this);

            PTMouse.X/=Width;
            PTMouse.Y/=Height;

			// Zmenim Center i GradientOrigin.
            if (Args.ChangedButton==MouseButton.Left)
            {
                MBrush.Center=PTMouse;
                MBrush.GradientOrigin=PTMouse;
            }
			// Zmenim iba GradientOrigin.
            else if (Args.ChangedButton==MouseButton.Right)
                MBrush.GradientOrigin=PTMouse;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------