using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Printing
{
//------------------------------------------------------------------------------
	public class CSimplePrinting : Window
	{
//------------------------------------------------------------------------------
        public CSimplePrinting()
        {
            Title="Print Ellipse";
            FontSize=24;

            StackPanel			LStack=new StackPanel();

            Content=LStack;

            Button				LButton=new Button();

            LButton.Content="_Print...";
            LButton.HorizontalAlignment=HorizontalAlignment.Center;
            LButton.Margin=new Thickness(24);
            LButton.Click+=PrintOnClick;
            LStack.Children.Add(LButton);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void PrintOnClick(object sender, RoutedEventArgs args)
        {
            PrintDialog				LDialog=new PrintDialog();

            if (((bool)LDialog.ShowDialog().GetValueOrDefault())==true)
            {
                DrawingVisual		LVisual=new DrawingVisual();
                DrawingContext		DC=LVisual.RenderOpen();

                DC.DrawEllipse(Brushes.LightGray, new Pen(Brushes.Black, 3), new Point(LDialog.PrintableAreaWidth / 2, LDialog.PrintableAreaHeight / 2), LDialog.PrintableAreaWidth / 2, LDialog.PrintableAreaHeight / 2);
                DC.Close();

                LDialog.PrintVisual(LVisual, "My first print job");
            }
        }            
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------