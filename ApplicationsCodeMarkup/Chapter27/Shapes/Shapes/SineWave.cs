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
	public class SineWave : Window
	{
//-------------------------------------------------------------------------------------------------------
		public SineWave()
		{
            Title="Sine Wave";

            Polyline		Poly=new Polyline();

            Poly.VerticalAlignment=VerticalAlignment.Center;
            Poly.Stroke=SystemColors.WindowTextBrush;
            Poly.StrokeThickness=2;
            Content=Poly;

            for (int i = 0; i < 2000; i++)
                Poly.Points.Add(new Point(i, 96*(1-Math.Sin(i*Math.PI/192))));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------