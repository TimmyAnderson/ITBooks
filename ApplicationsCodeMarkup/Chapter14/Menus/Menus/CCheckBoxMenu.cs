using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Menus
{
//------------------------------------------------------------------------------
	public class CCheckBoxMenu : Window
	{
//------------------------------------------------------------------------------
        private MenuItem										MItemChecked;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CCheckBoxMenu()
        {
            Title = "Check the Window Style";

            DockPanel			MyDock=new DockPanel();

            Content=MyDock;

            Menu				MyMenu=new Menu();

            MyDock.Children.Add(MyMenu);
            DockPanel.SetDock(MyMenu, Dock.Top);

            TextBlock			Text=new TextBlock();

            Text.Text=Title;
            Text.FontSize=32;
            Text.TextAlignment=TextAlignment.Center;
            MyDock.Children.Add(Text);

            MenuItem			ItemStyle=new MenuItem();

            ItemStyle.Header = "_Style";
            MyMenu.Items.Add(ItemStyle);

            ItemStyle.Items.Add(CreateMenuItem("_No border or caption", WindowStyle.None));
            ItemStyle.Items.Add(CreateMenuItem("_Single-border window", WindowStyle.SingleBorderWindow));
            ItemStyle.Items.Add(CreateMenuItem("3_D-border window", WindowStyle.ThreeDBorderWindow));
            ItemStyle.Items.Add(CreateMenuItem("_Tool window", WindowStyle.ToolWindow));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private MenuItem CreateMenuItem(string Str, WindowStyle Style)
        {
            MenuItem		Item=new MenuItem();

            Item.Header=Str;
            Item.Tag=Style;
            Item.IsChecked=(Style==WindowStyle);
            Item.Click+=StyleOnClick;

            if (Item.IsChecked==true)
                MItemChecked=Item;

            return(Item);
        }
//------------------------------------------------------------------------------
        private void StyleOnClick(object Sender, RoutedEventArgs Args)
        {
            MItemChecked.IsChecked=false;
            MItemChecked=Args.Source as MenuItem;
            MItemChecked.IsChecked=true;

            WindowStyle=(WindowStyle)MItemChecked.Tag;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------