using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//-------------------------------------------------------------------------------------------------------
namespace BitmapsDrawingsAndBrushes
{
//-------------------------------------------------------------------------------------------------------
	public class DrawGraphicsOnBitmap : Window
	{
//-------------------------------------------------------------------------------------------------------
        public DrawGraphicsOnBitmap()
        {
            Title="Draw Graphics on Bitmap";

            Background=Brushes.Khaki;

			// Vytvorim bitmapu do ktorej budem renderovat.
            RenderTargetBitmap		Renderbitmap=new RenderTargetBitmap(100, 100, 96, 96, PixelFormats.Default);
			// Vytvorim Visual, ktory budem renderovat do bitmapy.
            DrawingVisual			DrawVis=new DrawingVisual();
			// Ziskam DC.
            DrawingContext			DC=DrawVis.RenderOpen();

			// Vykreslim obsah Visual.
            DC.DrawRoundedRectangle(Brushes.Blue, new Pen(Brushes.Red, 10), new Rect(25, 25, 50, 50), 10, 10);
            DC.Close();

			// Renderujem Visual do bitmapy.
            Renderbitmap.Render(DrawVis);

            Image					Img=new Image();

			// Nastavim bitmapu ako Source pre Image.
            Img.Source=Renderbitmap;

            Content=Img;
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------