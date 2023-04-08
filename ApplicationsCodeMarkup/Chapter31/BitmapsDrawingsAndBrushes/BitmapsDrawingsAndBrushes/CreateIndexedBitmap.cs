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
	public class CreateIndexedBitmap : Window
	{
//-------------------------------------------------------------------------------------------------------
        public CreateIndexedBitmap()
        {
            Title = "Create Indexed Bitmap";

            List<Color>			Colors=new List<Color>();

            for (int R=0;R<256;R+=17)
				for (int B=0;B<256;B+=17)
					Colors.Add(Color.FromRgb((byte)R, 0, (byte)B));

            BitmapPalette		Palette=new BitmapPalette(Colors);
			// Toto pole bude obsahovat pixely bitmapy.
            byte[]				Array=new byte[256*256];

            for (int X=0;X<256;X++)
	            for (int Y=0;Y<256;Y++)
					Array[(256*Y)+X]=(byte)(((int)Math.Round(Y / 17.0) << 4) | (int)Math.Round(X / 17.0));

            BitmapSource		Bitmap=BitmapSource.Create(256, 256, 96, 96, PixelFormats.Indexed8, Palette, Array, 256);
            Image				Img=new Image();

            Img.Source=Bitmap;

            Content=Img;
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------