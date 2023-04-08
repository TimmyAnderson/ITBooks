using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Shapes;
//-------------------------------------------------------------------------------------------------------
namespace Transforms
{
//-------------------------------------------------------------------------------------------------------
	public class WheelAndSpokes : Window
	{
//-------------------------------------------------------------------------------------------------------
        public WheelAndSpokes()
        {
            Title = "Wheel and Spokes";

            Canvas			Canv=new Canvas();

            Content=Canv;

            Ellipse			Elips=new Ellipse();

            Elips.Stroke=SystemColors.WindowTextBrush;
            Elips.Width=200;
            Elips.Height=200;
            Canv.Children.Add(Elips);
            Canvas.SetLeft(Elips, 50);
            Canvas.SetTop(Elips, 50);

            for (int i = 0; i < 72; i++)
            {
                Line		LLine=new Line();

                LLine.Stroke=SystemColors.WindowTextBrush;
                LLine.X1=150;
                LLine.Y1=150;
                LLine.X2=250;
                LLine.Y2=150;
				
                LLine.RenderTransform=new RotateTransform(5 * i, 150, 150);
                Canv.Children.Add(LLine);
            }

            Elips=new Ellipse();
            Elips.Stroke=SystemColors.WindowTextBrush;
            Elips.Width=200;
            Elips.Height=200;
            Canv.Children.Add(Elips);
            Canvas.SetLeft(Elips, 300);
            Canvas.SetTop(Elips, 50);

            for (int i = 0; i < 72; i++)
            {
                Line		LLine=new Line();

                LLine.Stroke=SystemColors.WindowTextBrush;
                LLine.X1=0;
                LLine.Y1=0;
                LLine.X2=100;
                LLine.Y2=0;

                LLine.RenderTransform=new RotateTransform(5 * i);

                Canv.Children.Add(LLine);
                Canvas.SetLeft(LLine, 400);
                Canvas.SetTop(LLine, 150);
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------