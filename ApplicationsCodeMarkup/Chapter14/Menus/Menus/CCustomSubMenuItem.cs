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
//------------------------------------------------------------------------------
namespace Menus
{
//------------------------------------------------------------------------------
	public class CCustomSubMenuItem : Window
	{
//------------------------------------------------------------------------------
        public CCustomSubMenuItem()
        {
            Title="Check the Color";

            DockPanel			MyDock=new DockPanel();

            Content=MyDock;

            Menu				MainMenu=new Menu();

            MyDock.Children.Add(MainMenu);
            DockPanel.SetDock(MainMenu, Dock.Top);

            MenuItem			ItemColor=new MenuItem();

            ItemColor.Header="_Custom objects";
            MainMenu.Items.Add(ItemColor);

			// Ako menu item dam Rectangle.
			Rectangle			RectMenuItem=new Rectangle();

			RectMenuItem.Width=40;
			RectMenuItem.Height=20;
			RectMenuItem.Fill=new SolidColorBrush(Colors.Green);
			RectMenuItem.MouseLeftButtonDown += new MouseButtonEventHandler(RectMenuItem_MouseLeftButtonDown);
            ItemColor.Items.Add(RectMenuItem);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public void RectMenuItem_MouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			MessageBox.Show("You have clicked on GREEN RECTANGLE !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------