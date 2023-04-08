using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace Transforms
{
//-------------------------------------------------------------------------------------------------------
	public class RotatedText : Window
	{
//-------------------------------------------------------------------------------------------------------
        public RotatedText()
        {
            Title = "Rotated Text";

            Canvas			Canv=new Canvas();

            Content=Canv;

            for (int Angle=0; Angle<360; Angle+=20)
            {
                TextBlock	Txtblk=new TextBlock();

                Txtblk.FontFamily=new FontFamily("Arial");
                Txtblk.FontSize=24;
                Txtblk.Text="     Rotated Text";
                Txtblk.RenderTransformOrigin=new Point(0, 0.5);
                Txtblk.RenderTransform=new RotateTransform(Angle);

                Canv.Children.Add(Txtblk);
                Canvas.SetLeft(Txtblk, 200);
                Canvas.SetTop(Txtblk, 200);
            }
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------