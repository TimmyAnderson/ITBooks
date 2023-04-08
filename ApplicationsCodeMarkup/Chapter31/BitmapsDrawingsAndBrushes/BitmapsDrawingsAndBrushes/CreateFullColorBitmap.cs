using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//-------------------------------------------------------------------------------------------------------
namespace BitmapsDrawingsAndBrushes
{
//-------------------------------------------------------------------------------------------------------
	public class CreateFullColorBitmap : Window
	{
//-------------------------------------------------------------------------------------------------------
        public CreateFullColorBitmap()
        {
            Title="Create Full-Color Bitmap";

            int[]			Array=new int[256 * 256];

            for (int X=0;X<256;X++)
				for (int Y=0;Y<256;Y++)
				{
					int		B=X;
					int		G=0;
					int		R=Y;

					Array[(256*Y)+X]=B | (G<<8) | (R<<16);
				}

            BitmapSource	Bitmap=BitmapSource.Create(256, 256, 96, 96, PixelFormats.Bgr32, null, Array, 256 * 4);
            Image			Img=new Image();

            Img.Source=Bitmap;

            Content=Img;
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------