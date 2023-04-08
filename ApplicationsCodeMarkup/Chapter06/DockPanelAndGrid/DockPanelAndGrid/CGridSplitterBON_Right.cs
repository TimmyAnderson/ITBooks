﻿using System;
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
	public class CGridSplitterBON_Right : Window
	{
//------------------------------------------------------------------------------
		public CGridSplitterBON_Right()
		{
			Grid				MyGrid=new Grid();

			Content=MyGrid;
			Title="Grid";

			// Definujem riadky.
			RowDefinition		RD=new RowDefinition(){Height=new GridLength(1,GridUnitType.Star)};

			// Pridam riadky do Grid.
			MyGrid.RowDefinitions.Add(RD);

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
			
			// Pridam BUTTONS do Grid.
			MyGrid.Children.Add(B1);
			MyGrid.Children.Add(B2);
			MyGrid.Children.Add(B3);

			// Nastavim AP Row a Columns.
			Grid.SetColumn(B1,0);
			Grid.SetColumn(B2,1);
			Grid.SetColumn(B3,2);

			GridSplitter		GS=new GridSplitter();

			GS.Background=new SolidColorBrush(Colors.Red);
			GS.Width=15;
			Grid.SetColumn(GS,1);

			MyGrid.Children.Add(GS);

			// Urcuje, ze RESIZE bude spraveny na COLUMNS.
			GS.ResizeDirection=GridResizeDirection.Columns;

			// !!!!! Ak nastavim ResizeBehavior na 'BasedOnAlignment', tak to, ktore CELLS su SIZED je urcene hondotu HorizontalAligment, resp. VerticalAligment.
			GS.ResizeBehavior=GridResizeBehavior.BasedOnAlignment;

			// Nastavenie na 'RIGHT' sposobi, ze sa budu menit velkosti CLOUMN 1 a 2.
			GS.HorizontalAlignment=HorizontalAlignment.Right;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------