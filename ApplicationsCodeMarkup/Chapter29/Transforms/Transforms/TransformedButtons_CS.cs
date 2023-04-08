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
	public class TransformedButtons_CS : Window
	{
//-------------------------------------------------------------------------------------------------------
        public TransformedButtons_CS()
        {
            Title="Transformed Buttons";

            Canvas			LCanv=new Canvas();

            Content=LCanv;

            Button			Btn=new Button();

            Btn.Content="Untransformed";
            LCanv.Children.Add(Btn);
            Canvas.SetLeft(Btn, 50);
            Canvas.SetTop(Btn, 100);

            Btn=new Button();

            Btn.Content="Translated";
            Btn.RenderTransform=new TranslateTransform(-100, 150);
            LCanv.Children.Add(Btn);
            Canvas.SetLeft(Btn, 200);
            Canvas.SetTop(Btn, 100);

            Btn=new Button();

            Btn.Content="Scaled";
            Btn.RenderTransform=new ScaleTransform(1.5, 4);
            LCanv.Children.Add(Btn);
            Canvas.SetLeft(Btn, 350);
            Canvas.SetTop(Btn, 100);

            Btn=new Button();

            Btn.Content="Skewed";
            Btn.RenderTransform=new SkewTransform(0, 20);
            LCanv.Children.Add(Btn);
            Canvas.SetLeft(Btn, 500);
            Canvas.SetTop(Btn, 100);

            Btn=new Button();
            Btn.Content="Rotated";
            Btn.RenderTransform=new RotateTransform(-30);
            LCanv.Children.Add(Btn);
            Canvas.SetLeft(Btn, 650);
            Canvas.SetTop(Btn, 100);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------