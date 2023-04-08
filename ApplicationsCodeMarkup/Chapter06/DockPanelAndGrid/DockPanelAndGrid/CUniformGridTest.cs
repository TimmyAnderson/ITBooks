using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace DockPanelAndGrid
{
//------------------------------------------------------------------------------
	public class CUniformGridTest : Window
	{
//------------------------------------------------------------------------------
		public CUniformGridTest()
		{
			UniformGrid				MyGrid=new UniformGrid();

			Content=MyGrid;
			Title="Uniform Grid";

			const int				ROWS=2;
			const int				COLUMNS=4;

			// Definujem velkost UniformGrid.
			MyGrid.Rows=ROWS;
			MyGrid.Columns=COLUMNS;

			for (int i=0;i<ROWS*COLUMNS;i++)
			{
				Button				B=new Button(){Content=string.Format("Button {0}",i+1)};

				// Pridam BUTTONS do UniformGrid.
				MyGrid.Children.Add(B);
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------