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
	public class CFollowTheRainbow : Window
	{
//------------------------------------------------------------------------------
        public CFollowTheRainbow()
        {
			Title="Follow the Rainbow";

            LinearGradientBrush			Brush=new LinearGradientBrush();
            
			Brush.StartPoint=new Point(0, 0);
            Brush.EndPoint=new Point(1, 0);
            Background=Brush;

            // Posledny parameter je relativna hodnota v intervale <0,1>.
            Brush.GradientStops.Add(new GradientStop(Colors.Red, 0));
            Brush.GradientStops.Add(new GradientStop(Colors.Orange, .17));
            Brush.GradientStops.Add(new GradientStop(Colors.Yellow, .33));
            Brush.GradientStops.Add(new GradientStop(Colors.Green, .5));
            Brush.GradientStops.Add(new GradientStop(Colors.Blue, .67));
            Brush.GradientStops.Add(new GradientStop(Colors.Indigo, .84));
            Brush.GradientStops.Add(new GradientStop(Colors.Violet, 1));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------