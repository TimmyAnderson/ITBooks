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
	public class CGridSplitterRD_Rows : Window
	{
//------------------------------------------------------------------------------
		public CGridSplitterRD_Rows()
		{
			Grid				MyGrid=new Grid();

			Content=MyGrid;
			Title="Grid";

			// Definujem riadky.
			RowDefinition		RD1=new RowDefinition(){Height=new GridLength(1,GridUnitType.Star)};
			RowDefinition		RD2=new RowDefinition(){Height=new GridLength(1,GridUnitType.Star)};
			RowDefinition		RD3=new RowDefinition(){Height=new GridLength(1,GridUnitType.Star)};

			// Pridam riadky do Grid.
			MyGrid.RowDefinitions.Add(RD1);
			MyGrid.RowDefinitions.Add(RD2);
			MyGrid.RowDefinitions.Add(RD3);

			// Definujem stlpce.
			ColumnDefinition	CD1=new ColumnDefinition(){Width=new GridLength(1,GridUnitType.Star)};
			ColumnDefinition	CD2=new ColumnDefinition(){Width=new GridLength(1,GridUnitType.Star)};
			ColumnDefinition	CD3=new ColumnDefinition(){Width=new GridLength(1,GridUnitType.Star)};

			// Pridam stlpce do Grid.
			MyGrid.ColumnDefinitions.Add(CD1);
			MyGrid.ColumnDefinitions.Add(CD2);
			MyGrid.ColumnDefinitions.Add(CD3);

			// Vytvorim BUTTONS.
			Button				B1=new Button(){Content="Button 1"};
			Button				B2=new Button(){Content="Button 2"};
			Button				B3=new Button(){Content="Button 3"};
			Button				B4=new Button(){Content="Button 4"};
			Button				B5=new Button(){Content="Button 5"};
			Button				B6=new Button(){Content="Button 6"};
			Button				B7=new Button(){Content="Button 7"};
			Button				B8=new Button(){Content="Button 8"};
			Button				B9=new Button(){Content="Button 9"};
			
			// Pridam BUTTONS do Grid.
			MyGrid.Children.Add(B1);
			MyGrid.Children.Add(B2);
			MyGrid.Children.Add(B3);
			MyGrid.Children.Add(B4);
			MyGrid.Children.Add(B5);
			MyGrid.Children.Add(B6);
			MyGrid.Children.Add(B7);
			MyGrid.Children.Add(B8);
			MyGrid.Children.Add(B9);

			// Nastavim AP Row a Columns.
			Grid.SetColumn(B1,0);
			Grid.SetRow(B1,0);
			Grid.SetColumn(B2,1);
			Grid.SetRow(B2,0);
			Grid.SetColumn(B3,2);
			Grid.SetRow(B3,0);
			Grid.SetColumn(B4,0);
			Grid.SetRow(B4,1);
			Grid.SetColumn(B5,1);
			Grid.SetRow(B5,1);
			Grid.SetColumn(B6,2);
			Grid.SetRow(B6,1);
			Grid.SetColumn(B7,0);
			Grid.SetRow(B7,2);
			Grid.SetColumn(B8,1);
			Grid.SetRow(B8,2);
			Grid.SetColumn(B9,2);
			Grid.SetRow(B9,2);

			GridSplitter		GS=new GridSplitter();

			GS.Background=new SolidColorBrush(Colors.Red);
			GS.Width=15;
		
			Grid.SetColumn(GS,1);
			Grid.SetRow(GS,1);

			MyGrid.Children.Add(GS);

			// Urcuje, ze RESIZE bude spraveny na ROWS.
			// !!! Meni sa teda VELKOST RIADKOV, i ked GridSplitter ma vyzor, akoby bol na zmenuy velkosti stlcov.
			GS.ResizeDirection=GridResizeDirection.Rows;

			// !!!!! Ak nastavim ResizeBehavior na 'PreviousAndNext', tak SIZED budu COLUMNS 0 a 2.
			GS.ResizeBehavior=GridResizeBehavior.PreviousAndNext;

			// Nastavenie HorizontalAlignment NEMA VPLYV na to, ktore CELLS budu RESIZED a urcuje iba UMIESTNENIE GridSplitter.
			GS.HorizontalAlignment=HorizontalAlignment.Center;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------