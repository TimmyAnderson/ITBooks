using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.ComponentModel;
//------------------------------------------------------------------------------
namespace BrushTests
{
//------------------------------------------------------------------------------
	public class CSimpleGradientBrush
	{
//------------------------------------------------------------------------------
		private static void ShowWindow(string Title, Brush Brush)
		{
            Window			Win=new Window();

            Win.Title=Title;
            Win.Background=Brush;

			Win.Show();
		}
//------------------------------------------------------------------------------
		private static void Win_SizeChanged(object Sender, SizeChangedEventArgs E)
		{
			Window				Win=(Window) Sender;
			LinearGradientBrush Brush=new LinearGradientBrush(Colors.Red,Colors.Blue,0);
            double				Width=Win.ActualWidth-(2*SystemParameters.ResizeFrameVerticalBorderWidth);
            double				Height=Win.ActualHeight-(2*SystemParameters.ResizeFrameHorizontalBorderHeight)-SystemParameters.CaptionHeight;
			// Stredovy bod.
            Point				PTCenter=new Point(Width/2,Height/2);
			// Diagonala medzi <0,1> a <1,0>.
            Vector				VectDiag=new Vector(Width,-Height);
			// Kolmica na diagonalu.
            Vector				VectPerp=new Vector(VectDiag.Y,-VectDiag.X);

            VectPerp.Normalize();
            VectPerp*=Width*Height/VectDiag.Length;

            Brush.StartPoint=PTCenter+VectPerp;
            Brush.EndPoint=PTCenter-VectPerp;
            Brush.MappingMode=BrushMappingMode.Absolute;

            Win.Background=Brush;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public static void Do1()
		{
            Application				App=new Application();

            LinearGradientBrush		Brush1=new LinearGradientBrush(Colors.Red, Colors.Blue, new Point(0, 0), new Point(1, 1));
            LinearGradientBrush		Brush2=new LinearGradientBrush(Colors.Red, Colors.Blue, new Point(0, 0), new Point(1, 1));
            LinearGradientBrush		Brush3=new LinearGradientBrush(Colors.Red, Colors.Blue, new Point(0.25, 0.25), new Point(0.75, 0.75));
            LinearGradientBrush		Brush4=new LinearGradientBrush(Colors.Red, Colors.Blue, new Point(0.25, 0.25), new Point(0.75, 0.75));
            LinearGradientBrush		Brush5=new LinearGradientBrush(Colors.Red, Colors.Blue, new Point(0.25, 0.25), new Point(0.75, 0.75));

			Brush2.ColorInterpolationMode=ColorInterpolationMode.ScRgbLinearInterpolation;

			Brush3.SpreadMethod=GradientSpreadMethod.Pad;
			Brush4.SpreadMethod=GradientSpreadMethod.Reflect;
			Brush5.SpreadMethod=GradientSpreadMethod.Repeat;

			ShowWindow("<0,0> - <1,1>",Brush1);
			ShowWindow("SCRGB - <0,0> - <1,1>",Brush2);
			ShowWindow("Pad - <0.25,0.25> - <0.75,0.75>",Brush3);
			ShowWindow("Reflect - <0.25,0.25> - <0.75,0.75>",Brush4);
			ShowWindow("Repeat - <0.25,0.25> - <0.75,0.75>",Brush5);

            App.Run();
		}
//------------------------------------------------------------------------------
		// Lepsie vidiet gradient, kedze prechadza po diagonale <0,1> - <1,0>.
		public static void Do2()
		{
            Application			App=new Application();
            Window				Win=new Window();

            Win.Title="Gradient";
			Win.Show();

			Win.SizeChanged+=new SizeChangedEventHandler(Win_SizeChanged);

			Win_SizeChanged(Win,null);

            App.Run();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------