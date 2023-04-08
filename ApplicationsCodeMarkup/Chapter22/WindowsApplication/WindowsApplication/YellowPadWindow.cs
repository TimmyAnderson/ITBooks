using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class YellowPadWindow : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        public static readonly double							MWidthCanvas=5*96;
        public static readonly double							MHeightCanvas=7*96;
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public YellowPadWindow()
        {
            InitializeComponent();

            double			Y=96;

            while (Y<MHeightCanvas)
            {
                Line		LLine=new Line();

                LLine.X1=0;
                LLine.Y1=Y;
                LLine.X2=MWidthCanvas;
                LLine.Y2=Y;
                LLine.Stroke=Brushes.LightBlue;

                MInkCanvas.Children.Add(LLine);
                Y+=24;
            }

            // Vypnem menu pre ERASER, ak nepracujem s tablet PC.
            if (Tablet.TabletDevices.Count==0)
                MMenuEraserMode.Visibility=Visibility.Collapsed;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------