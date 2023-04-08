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
//------------------------------------------------------------------------------
namespace DockPanelAndGrid
{
//------------------------------------------------------------------------------
	public class CGridWithSpanedElements : Window
	{
//------------------------------------------------------------------------------
		public CGridWithSpanedElements()
		{
            Title="Span the Cells";
            SizeToContent=SizeToContent.WidthAndHeight;

            Grid					MyGrid=new Grid();

            MyGrid.Margin=new Thickness(5);
            Content=MyGrid;

            for (int i=0;i<6;i++)
            {
                RowDefinition		RowDef=new RowDefinition();

                RowDef.Height=GridLength.Auto;
                MyGrid.RowDefinitions.Add(RowDef);
            }

            for (int i=0;i<4;i++)
            {
                ColumnDefinition	ColDef=new ColumnDefinition();

                if (i==1)
                    ColDef.Width=new GridLength(100, GridUnitType.Star);
                else
                    ColDef.Width=GridLength.Auto;

                MyGrid.ColumnDefinitions.Add(ColDef);
            }

            string[]				AstrLabel={"_First name:", "_Last name:", "_Social security number:", "_Credit card number:", "_Other personal stuff:"};

            for(int i=0;i<AstrLabel.Length;i++)
            {
                Label				Lbl=new Label();

                Lbl.Content=AstrLabel[i];
                Lbl.VerticalContentAlignment=VerticalAlignment.Center;
                MyGrid.Children.Add(Lbl);
                Grid.SetRow(Lbl, i);
                Grid.SetColumn(Lbl, 0);

                TextBox				TxtBox=new TextBox();

                TxtBox.Margin=new Thickness(5);
                MyGrid.Children.Add(TxtBox);
                Grid.SetRow(TxtBox, i);
                Grid.SetColumn(TxtBox, 1);
                Grid.SetColumnSpan(TxtBox, 3);
            }

            Button					Btn=new Button();

            Btn.Content="Submit";
            Btn.Margin=new Thickness(5);
            Btn.IsDefault=true;
            Btn.Click+=delegate { Close(); };
            MyGrid.Children.Add(Btn);
            Grid.SetRow(Btn, 5);
            Grid.SetColumn(Btn, 2);

            Btn=new Button();
            Btn.Content="Cancel";
            Btn.Margin=new Thickness(5);
            Btn.IsCancel= true;
            Btn.Click+=delegate { Close(); };
            MyGrid.Children.Add(Btn);
            Grid.SetRow(Btn, 5);
            Grid.SetColumn(Btn, 3);

            MyGrid.Children[1].Focus();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------