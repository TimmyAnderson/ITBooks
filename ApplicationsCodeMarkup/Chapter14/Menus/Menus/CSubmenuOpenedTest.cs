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
	public class CSubmenuOpenedTest : Window
	{
//------------------------------------------------------------------------------
        private TextBlock										MText;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CSubmenuOpenedTest()
        {
            Title="Check the Color";

            DockPanel			MyDock=new DockPanel();

            Content=MyDock;

            Menu				MainMenu=new Menu();

            MyDock.Children.Add(MainMenu);
            DockPanel.SetDock(MainMenu, Dock.Top);

            MText=new TextBlock();
            MText.Text=Title;
            MText.TextAlignment=TextAlignment.Center;
            MText.FontSize=32;
            MText.Background=SystemColors.WindowBrush;
            MText.Foreground=SystemColors.WindowTextBrush;
            MyDock.Children.Add(MText);

            MenuItem			ItemColor=new MenuItem();

            ItemColor.Header="_Color";
            MainMenu.Items.Add(ItemColor);

            MenuItem			ItemForeground=new MenuItem();

            ItemForeground.Header="_Foreground";
			// V EVENT SubmenuOpened sa nastavuje SELECTED COLOR.
            ItemForeground.SubmenuOpened+=ForegroundOnOpened;
            ItemColor.Items.Add(ItemForeground);

            FillWithColors(ItemForeground, ForegroundOnClick);

            MenuItem			ItemBackground=new MenuItem();

            ItemBackground.Header="_Background";
			// V EVENT SubmenuOpened sa nastavuje SELECTED COLOR.
            ItemBackground.SubmenuOpened+=BackgroundOnOpened;
            ItemColor.Items.Add(ItemBackground);

            FillWithColors(ItemBackground, BackgroundOnClick);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void FillWithColors(MenuItem ItemParent, RoutedEventHandler Handler)
        {
            foreach (PropertyInfo Prop in typeof(Colors).GetProperties())
            {
                Color			Clr=(Color)Prop.GetValue(null, null);
                int				ICount=0;

                ICount+=(Clr.R == 0 || Clr.R == 255) ? 1 : 0;
                ICount+=(Clr.G == 0 || Clr.G == 255) ? 1 : 0;
                ICount+=(Clr.B == 0 || Clr.B == 255) ? 1 : 0;

                if (Clr.A==255 && ICount>1)
                {
                    MenuItem	Item=new MenuItem();

                    Item.Header = "_" + Prop.Name;
                    Item.Tag = Clr;
                    Item.Click += Handler;
                    ItemParent.Items.Add(Item);
                }
            }
        }
//------------------------------------------------------------------------------
        private void ForegroundOnOpened(object Sender, RoutedEventArgs Args)
        {
            MenuItem			ItemParent=Sender as MenuItem;

            foreach (MenuItem Item in ItemParent.Items)
                Item.IsChecked=((MText.Foreground as SolidColorBrush).Color==(Color)Item.Tag);
        }
//------------------------------------------------------------------------------
        private void BackgroundOnOpened(object Sender, RoutedEventArgs Args)
        {
            MenuItem			ItemParent=Sender as MenuItem;

            foreach (MenuItem Item in ItemParent.Items)
                Item.IsChecked=((MText.Background as SolidColorBrush).Color==(Color)Item.Tag);
        }
//------------------------------------------------------------------------------
        private void ForegroundOnClick(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;
            Color				Clr=(Color)Item.Tag;

            MText.Foreground=new SolidColorBrush(Clr);
        }
//------------------------------------------------------------------------------
        private void BackgroundOnClick(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;
            Color				Clr=(Color)Item.Tag;

            MText.Background=new SolidColorBrush(Clr);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------