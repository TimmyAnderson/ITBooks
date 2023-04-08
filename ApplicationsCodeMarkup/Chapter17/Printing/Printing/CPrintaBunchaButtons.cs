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
	public class CPrintaBunchaButtons : Window
	{
//------------------------------------------------------------------------------
        public CPrintaBunchaButtons()
        {
            Title="Print a Bunch of Buttons";
            SizeToContent=SizeToContent.WidthAndHeight;
            ResizeMode=ResizeMode.CanMinimize;

            Button				Btn=new Button();

            Btn.FontSize=24;
            Btn.Content="Print ...";
            Btn.Padding=new Thickness(12);
            Btn.Margin=new Thickness(96);
            Btn.Click+=PrintOnClick;
            Content=Btn;
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void PrintOnClick(object Sender, RoutedEventArgs Args)
        {
            PrintDialog					Dlg=new PrintDialog();

            if (((bool)Dlg.ShowDialog().GetValueOrDefault())==true)
            {
                Grid					LGrid=new Grid();

                for (int i=0;i<5;i++)
                {
                    ColumnDefinition	ColDef=new ColumnDefinition();

                    ColDef.Width=GridLength.Auto;
                    LGrid.ColumnDefinitions.Add(ColDef);

                    RowDefinition		RowDef=new RowDefinition();

                    RowDef.Height=GridLength.Auto;
                    LGrid.RowDefinitions.Add(RowDef);
                }

                LGrid.Background=new LinearGradientBrush(Colors.Gray, Colors.White, new Point(0, 0), new Point(1, 1));

                Random					Rand=new Random();

                for (int i=0;i<25;i++)
                {
                    Button				Btn=new Button();

                    Btn.FontSize=12+Rand.Next(8);
                    Btn.Content="Button No. " + (i + 1);
                    Btn.HorizontalAlignment=HorizontalAlignment.Center;
                    Btn.VerticalAlignment=VerticalAlignment.Center;
                    Btn.Margin=new Thickness(6);
                    LGrid.Children.Add(Btn);
                    Grid.SetRow(Btn, i % 5);
                    Grid.SetColumn(Btn, i / 5);
                }

				// MUSIM SPRAVIT MEASURE FAZU.
                LGrid.Measure(new Size(Double.PositiveInfinity, Double.PositiveInfinity));

                Size					SizeGrid=LGrid.DesiredSize;
                Point					PtGrid=new Point((Dlg.PrintableAreaWidth-SizeGrid.Width)/2, (Dlg.PrintableAreaHeight-SizeGrid.Height)/2);

				// MUSIM SPRAVIT ARRANGE FAZU.
                LGrid.Arrange(new Rect(PtGrid, SizeGrid));

                // !!! Az TERAZ mozem tlacit ELEMENT.
                Dlg.PrintVisual(LGrid, Title);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------