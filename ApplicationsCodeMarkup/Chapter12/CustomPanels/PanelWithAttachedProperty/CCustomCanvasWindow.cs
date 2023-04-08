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
using System.Windows.Threading;
//------------------------------------------------------------------------------
namespace CustomPanels
{
//------------------------------------------------------------------------------
	public class CCustomCanvasWindow : Window
	{
//------------------------------------------------------------------------------
        public CCustomCanvasWindow()
        {
            Title="Paint on Canvas Clone";

            CCustomCanvas		MyCanvas=new CCustomCanvas();
            
			Content=MyCanvas;

            SolidColorBrush[]	MyBrushes={ Brushes.Red, Brushes.Green, Brushes.Blue };

            for (int i=0;i<MyBrushes.Length;i++)
            {
                Rectangle		MyRectangle=new Rectangle();

                MyRectangle.Fill=MyBrushes[i];
                MyRectangle.Width=200;
                MyRectangle.Height=200;
                MyCanvas.Children.Add(MyRectangle);

				// Nastavim AP pre CHILD.
                CCustomCanvas.SetLeft(MyRectangle, 100 * (i + 1));
                CCustomCanvas.SetTop(MyRectangle, 100 * (i + 1));
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------