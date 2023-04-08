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
namespace CustomDP
{
//------------------------------------------------------------------------------
	// Window dedi z CWindowWithDP.
	public class CMainWindow : CWindowWithDP
	{
//------------------------------------------------------------------------------
        public CMainWindow()
        {
            Title="Set Space Property";
            base.SizeToContent=SizeToContent.WidthAndHeight;
            ResizeMode=ResizeMode.CanMinimize;

            int[]					ISpaces={ 0, 1, 2 };
            Grid					MyGrid=new Grid();

            Content=MyGrid;

			// Definujem ROWS.
            for (int i=0;i<2;i++)
            {
                RowDefinition		Row=new RowDefinition();

                Row.Height=GridLength.Auto;
                MyGrid.RowDefinitions.Add(Row);
            }

			// Definujem COLUMNS.
            for (int i=0;i<ISpaces.Length;i++)
            {
                ColumnDefinition	Col=new ColumnDefinition();

                Col.Width=GridLength.Auto;
                MyGrid.ColumnDefinitions.Add(Col);
            }

			// Vytvorim BUTTONS.
            for (int i=0;i<ISpaces.Length;i++)
            {
                CButtonWithDP		Btn=new CButtonWithDP();

				Btn=new CButtonWithDP();
                Btn.ButtonText="Set WINDOW Space DP to " + ISpaces[i];
                Btn.Tag=ISpaces[i];
                Btn.HorizontalAlignment=HorizontalAlignment.Center;
                Btn.VerticalAlignment=VerticalAlignment.Center;
                Btn.Click+=WindowPropertyOnClick;
                MyGrid.Children.Add(Btn);
                Grid.SetRow(Btn, 0);
                Grid.SetColumn(Btn, i);

				Btn=new CButtonWithDP();
                Btn.ButtonText="Set BUTTON Space DP to " + ISpaces[i];
                Btn.Tag=ISpaces[i];
                Btn.HorizontalAlignment=HorizontalAlignment.Center;
                Btn.VerticalAlignment=VerticalAlignment.Center;
                Btn.Click+=ButtonPropertyOnClick;
                MyGrid.Children.Add(Btn);
                Grid.SetRow(Btn, 1);
                Grid.SetColumn(Btn, i);
            }
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void WindowPropertyOnClick(object Sender, RoutedEventArgs Args)
        {
            CButtonWithDP			Btn=Args.Source as CButtonWithDP;

			// Nastavim hodnotu 'Space' DP pre WINDOW.
			// !!!!! Vdaka DP INHERITANCE sa APLIKUJE na CHILD BUTTONS.
            Space=(int) Btn.Tag;
        }
//------------------------------------------------------------------------------
        private void ButtonPropertyOnClick(object Sender, RoutedEventArgs Args)
        {
            CButtonWithDP			Btn=Args.Source as CButtonWithDP;

			// Nastavim hodnotu 'Space' DP pre BUTTON.
            Btn.Space=(int) Btn.Tag;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------