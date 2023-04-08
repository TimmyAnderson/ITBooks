using System;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace ToolbarsAndStatusBars
{
//------------------------------------------------------------------------------
	public class CToolBarsInTrays : Window
	{
//------------------------------------------------------------------------------
        public CToolBarsInTrays()
		{
            Title = "Move the Toolbar";

            DockPanel			MyDock=new DockPanel();

            Content=MyDock;

			// Vytvorim 1. TRAY.
            ToolBarTray			TrayTop=new ToolBarTray();

            MyDock.Children.Add(TrayTop);
            DockPanel.SetDock(TrayTop, Dock.Top);

			// Vytvorim 2. TRAY.
            ToolBarTray			TrayLeft=new ToolBarTray();

			// Zmenim orientaciu na VERTICAL.
            TrayLeft.Orientation=Orientation.Vertical;
            MyDock.Children.Add(TrayLeft);
            DockPanel.SetDock(TrayLeft, Dock.Left);

            TextBox				MyTxtBox=new TextBox();

            MyDock.Children.Add(MyTxtBox);

            // Vytvorim 6 TOOL BARS.
            for (int i=0;i<6;i++)
            {
                ToolBar			MyToolBar=new ToolBar();

                MyToolBar.Header="Toolbar " + (i + 1);

                if (i<3)
                    TrayTop.ToolBars.Add(MyToolBar);
                else
                    TrayLeft.ToolBars.Add(MyToolBar);

                for (int j = 0; j < 6; j++)
                {
                    Button		SomeButton=new Button();

                    SomeButton.FontSize = 16;
                    SomeButton.Content=(char)('A' + j);
                    MyToolBar.Items.Add(SomeButton);
                }
            }
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------