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
using System.Windows.Documents;
//------------------------------------------------------------------------------
namespace DependencyProperties
{
//------------------------------------------------------------------------------
	public class CDPInheritance : Window
	{
//------------------------------------------------------------------------------
		public CDPInheritance()
		{
            Title="Set FontSize Property";
            SizeToContent=SizeToContent.WidthAndHeight;
            ResizeMode=ResizeMode.CanMinimize;
            FontSize=16;

            double[]				FntSizes={ 8, 16, 32 };
            Grid					MyGrid=new Grid();

            Content = MyGrid;

            for (int i=0;i<2;i++)
            {
                RowDefinition		Row=new RowDefinition();

                Row.Height=GridLength.Auto;
                MyGrid.RowDefinitions.Add(Row);
            }

            for (int i=0;i<FntSizes.Length;i++)
            {
                ColumnDefinition	Col=new ColumnDefinition();

                Col.Width=GridLength.Auto;
                MyGrid.ColumnDefinitions.Add(Col);
            }

            for (int i=0;i<FntSizes.Length;i++)
            {
                Button				Btn=new Button();

                Btn.Content=new TextBlock(new Run("Set window FontSize to " + FntSizes[i]));
                Btn.Tag=FntSizes[i];
                Btn.HorizontalAlignment=HorizontalAlignment.Center;
                Btn.VerticalAlignment=VerticalAlignment.Center;
                Btn.Click+=WindowFontSizeOnClick;
                MyGrid.Children.Add(Btn);
                Grid.SetRow(Btn, 0);
                Grid.SetColumn(Btn, i);

                Btn=new Button();
                Btn.Content=new TextBlock(new Run("Set button FontSize to " + FntSizes[i]));
                Btn.Tag=FntSizes[i];
                Btn.HorizontalAlignment=HorizontalAlignment.Center;
                Btn.VerticalAlignment=VerticalAlignment.Center;
                Btn.Click+=ButtonFontSizeOnClick;
                MyGrid.Children.Add(Btn);
                Grid.SetRow(Btn, 1);
                Grid.SetColumn(Btn, i);
            }
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void WindowFontSizeOnClick(object Sender, RoutedEventArgs Args)
        {
            Button			Btn=Args.Source as Button;

            FontSize=(double) Btn.Tag;
        }
//------------------------------------------------------------------------------
        private void ButtonFontSizeOnClick(object Sender, RoutedEventArgs Args)
        {
            Button			Btn=Args.Source as Button;

            Btn.FontSize=(double) Btn.Tag;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------