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
	public class CMoreEelementsInCellGrid : Window
	{
//------------------------------------------------------------------------------
		public CMoreEelementsInCellGrid()
		{
			Grid				MyGrid=new Grid();

			MyGrid.ShowGridLines=true;

			Content=MyGrid;
			Title="Grid";

			// Definujem riadky.
			RowDefinition		RD1=new RowDefinition(){Height=new GridLength(1,GridUnitType.Star)};
			RowDefinition		RD2=new RowDefinition(){Height=new GridLength(1,GridUnitType.Star)};

			// Pridam riadky do Grid.
			MyGrid.RowDefinitions.Add(RD1);
			MyGrid.RowDefinitions.Add(RD2);

			// Definujem stlpce.
			ColumnDefinition	CD1=new ColumnDefinition(){Width=new GridLength(1,GridUnitType.Star)};
			ColumnDefinition	CD2=new ColumnDefinition(){Width=new GridLength(1,GridUnitType.Star)};

			// Pridam stlpce do Grid.
			MyGrid.ColumnDefinitions.Add(CD1);
			MyGrid.ColumnDefinitions.Add(CD2);

			// Vytvorim BUTTONS.
			Button				B1=new Button(){Content="Button 1"};
			Button				B2=new Button(){Content="Button 2"};
			Button				B3=new Button(){Content="Button 3"};
			Button				B4=new Button(){Content="Button 4"};

			// Pridam BUTTONS do Grid.
			MyGrid.Children.Add(B1);
			MyGrid.Children.Add(B2);
			MyGrid.Children.Add(B3);
			MyGrid.Children.Add(B4);

			// Nastavim AP Row a Columns.
			Grid.SetRow(B1,0);
			Grid.SetColumn(B1,0);

			Grid.SetRow(B2,0);
			Grid.SetColumn(B2,1);

			Grid.SetRow(B3,1);
			Grid.SetColumn(B3,0);

			Grid.SetRow(B4,1);
			Grid.SetColumn(B4,1);

			// Nastavim HorizontalAlignment a VerticalAlignment, aby bolo vidiet ako to ovplyvnuje umiestnenie komponent.
			B1.HorizontalAlignment=HorizontalAlignment.Center;
			B1.VerticalAlignment=VerticalAlignment.Center;

			B2.HorizontalAlignment=HorizontalAlignment.Center;

			B3.VerticalAlignment=VerticalAlignment.Center;

			// Pridam dalsie BUTTONS do CELL(0,0).
			Button				B5=new Button(){Content="Button 5"};
			Button				B6=new Button(){Content="Button 6"};
			Button				B7=new Button(){Content="Button 7"};
			Button				B8=new Button(){Content="Button 8"};

			// Pridam BUTTONS do Grid.
			MyGrid.Children.Add(B5);
			MyGrid.Children.Add(B6);
			MyGrid.Children.Add(B7);
			MyGrid.Children.Add(B8);

			Grid.SetRow(B5,0);
			Grid.SetColumn(B5,0);

			Grid.SetRow(B6,0);
			Grid.SetColumn(B6,0);

			Grid.SetRow(B7,0);
			Grid.SetColumn(B7,0);

			Grid.SetRow(B8,0);
			Grid.SetColumn(B8,0);

			// Umiestnim BUTTONS v CELL(0,0), tak aby ich bolo vidiet.
			B5.HorizontalAlignment=HorizontalAlignment.Left;
			B5.VerticalAlignment=VerticalAlignment.Center;

			B6.HorizontalAlignment=HorizontalAlignment.Right;
			B6.VerticalAlignment=VerticalAlignment.Center;

			B7.HorizontalAlignment=HorizontalAlignment.Center;
			B7.VerticalAlignment=VerticalAlignment.Top;

			B8.HorizontalAlignment=HorizontalAlignment.Center;
			B8.VerticalAlignment=VerticalAlignment.Bottom;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------