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
	public class DrawButtonsOnBitmap : Window
	{
//-------------------------------------------------------------------------------------------------------
        public DrawButtonsOnBitmap()
        {
            Title="Draw Buttons on Bitmap";

            UniformGrid			UniGrid=new UniformGrid();

            UniGrid.Columns=4;

            for (int i=0;i<32;i++)
            {
                ToggleButton	Btn=new ToggleButton();

                Btn.Width=96;
                Btn.Height=24;
                Btn.IsChecked=(i<4 | i>27)^((i%4)==0 | (i%4)==3);
                UniGrid.Children.Add(Btn);
            }

			// !!! ELEMENT Uniform si MUSI vypocitat svoju velkost volanim Measure().
            UniGrid.Measure(new Size(Double.PositiveInfinity, Double.PositiveInfinity));

			// !!! Velkost ktoru POZADUJE Uniform a ktora bola urcena volanim Measure().
            Size				SzGrid=UniGrid.DesiredSize;

			// !!! Urci POZICIU Uniform.
            UniGrid.Arrange(new Rect(new Point(0, 0), SzGrid));

			// Vytvorim prazdu bitmapu.
            RenderTargetBitmap	Renderbitmap=new RenderTargetBitmap((int)Math.Ceiling(SzGrid.Width), (int)Math.Ceiling(SzGrid.Height), 96, 96, PixelFormats.Default);

            // Vykreslim UniformGrid do bitmapy.
            Renderbitmap.Render(UniGrid);

            // Bitmapu nastavim ako Source pre Image.
            Image				Img=new Image();

            Img.Source=Renderbitmap;

            Content=Img;
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------