using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	public class CImageAsContent : Window
	{
//------------------------------------------------------------------------------
		public CImageAsContent(int Version)
		{
			Image			Img=new Image();
			Uri				Path=new Uri("Images/SadFace.jpg",UriKind.Relative);
			BitmapSource	BS=new BitmapImage(Path);

			Img.Source=BS;

			Console.WriteLine(string.Format("Width: [{0}] !",BS.Width));
			Console.WriteLine(string.Format("Height: [{0}] !",BS.Height));

			// !!! Skutocna velkost obrazka je (110,94).
			Console.WriteLine(string.Format("PixelHeight: [{0}] !",BS.PixelHeight));
			Console.WriteLine(string.Format("PixelWidth: [{0}] !",BS.PixelWidth));

			// Resolution obrazku je 120*120 - da sa to zistit cez Paint.exe.
			Console.WriteLine(string.Format("DpiX: [{0}] !",BS.DpiX));
			Console.WriteLine(string.Format("DpiY: [{0}] !",BS.DpiY));

			Content=Img;

			if (Version==1)
			{
				// Stretch urcuje ci a ako sa obrazok roztiahne na PARENT ELEMENT.
				Img.Stretch=Stretch.None;
				Img.HorizontalAlignment=HorizontalAlignment.Right;
				Img.Margin=new Thickness(10);
			}
			else if (Version==2)
			{
				Img.Stretch=Stretch.None;

				LinearGradientBrush		LGBrush=new LinearGradientBrush();

				LGBrush.StartPoint=new Point(0,0.5);
				LGBrush.EndPoint=new Point(1,0.5);

				LGBrush.GradientStops.Add(new GradientStop(Colors.Blue,0));
				LGBrush.GradientStops.Add(new GradientStop(Colors.Green,1));

				Background=LGBrush;
			}
			else if (Version==3)
			{
				Img.Stretch=Stretch.None;

				LinearGradientBrush		LGBrush=new LinearGradientBrush();

				LGBrush.StartPoint=new Point(0,0.5);
				LGBrush.EndPoint=new Point(1,0.5);

				LGBrush.GradientStops.Add(new GradientStop(Colors.Blue,0));
				LGBrush.GradientStops.Add(new GradientStop(Colors.Green,1));

				Background=LGBrush;

				// Nastavim aj OPACITY.
				Img.Opacity=0.3;
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------