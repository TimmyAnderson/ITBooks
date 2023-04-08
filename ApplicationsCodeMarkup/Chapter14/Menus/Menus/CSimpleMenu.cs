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
	public class CSimpleMenu : Window
	{
//------------------------------------------------------------------------------
        public CSimpleMenu()
        {
            Title="Peruse the Menu";

            // Create DockPanel.
            DockPanel				MyDock = new DockPanel();

            Content=MyDock;

            Menu					MainMenu=new Menu();

            MyDock.Children.Add(MainMenu);
            DockPanel.SetDock(MainMenu, Dock.Top);

            TextBlock				Text=new TextBlock();

            Text.Text=Title;
            Text.FontSize=32;
            Text.TextAlignment=TextAlignment.Center;
            MyDock.Children.Add(Text);

            MenuItem				ItemFile=new MenuItem();

            ItemFile.Header="_File";
            MainMenu.Items.Add(ItemFile);

            MenuItem				ItemNew=new MenuItem();

            ItemNew.Header="_New";
            ItemNew.Click+=UnimplementedOnClick;
            ItemFile.Items.Add(ItemNew);

            MenuItem				ItemOpen=new MenuItem();

            ItemOpen.Header="_Open";
            ItemOpen.Click+=UnimplementedOnClick;
            ItemFile.Items.Add(ItemOpen);

            MenuItem				ItemSave=new MenuItem();

            ItemSave.Header="_Save";
            ItemSave.Click+=UnimplementedOnClick;
            ItemFile.Items.Add(ItemSave);

            ItemFile.Items.Add(new Separator());

            MenuItem				ItemExit=new MenuItem();

            ItemExit.Header="E_xit";
            ItemExit.Click+=ExitOnClick;
            ItemFile.Items.Add(ItemExit);

            MenuItem				ItemWindow=new MenuItem();

            ItemWindow.Header="_Window";
            MainMenu.Items.Add(ItemWindow);

            MenuItem				ItemTaskbar=new MenuItem();

            ItemTaskbar.Header="_Show in Taskbar";
            ItemTaskbar.IsCheckable=true;
            ItemTaskbar.IsChecked=ShowInTaskbar;
            ItemTaskbar.Click+=TaskbarOnClick;
            ItemWindow.Items.Add(ItemTaskbar);

            MenuItem				ItemSize=new MenuItem();

            ItemSize.Header="Size to _Content";
            ItemSize.IsCheckable=true;
            ItemSize.IsChecked=(SizeToContent==SizeToContent.WidthAndHeight);
            ItemSize.Checked+=SizeOnCheck;
            ItemSize.Unchecked+=SizeOnCheck;
            ItemWindow.Items.Add(ItemSize);

            MenuItem				ItemResize=new MenuItem();

            ItemResize.Header="_Resizable";
            ItemResize.IsCheckable=true;
            ItemResize.IsChecked=(ResizeMode==ResizeMode.CanResize);
            ItemResize.Click+=ResizeOnClick;
            ItemWindow.Items.Add(ItemResize);

            MenuItem				ItemTopmost=new MenuItem();

            ItemTopmost.Header="_Topmost";
            ItemTopmost.IsCheckable=true;
            ItemTopmost.IsChecked=Topmost;
            ItemTopmost.Checked+=TopmostOnCheck;
            ItemTopmost.Unchecked+=TopmostOnCheck;
            ItemWindow.Items.Add(ItemTopmost);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void UnimplementedOnClick(object Sender, RoutedEventArgs args)
        {
            MenuItem			Item=Sender as MenuItem;
            string				StrItem=Item.Header.ToString().Replace("_", "");

            MessageBox.Show(string.Format("The {0} option has not yet been implemented !",StrItem), Title);
        }
//------------------------------------------------------------------------------
        private void ExitOnClick(object Sender, RoutedEventArgs Args)
        {
            Close();
        }
//------------------------------------------------------------------------------
        private void TaskbarOnClick(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            ShowInTaskbar=Item.IsChecked;
        }
//------------------------------------------------------------------------------
        private void SizeOnCheck(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            SizeToContent=(Item.IsChecked==true) ? SizeToContent.WidthAndHeight : SizeToContent.Manual;
        }
//------------------------------------------------------------------------------
        private void ResizeOnClick(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            ResizeMode=(Item.IsChecked==true) ? ResizeMode.CanResize : ResizeMode.NoResize;
        }
//------------------------------------------------------------------------------
        private void TopmostOnCheck(object Sender, RoutedEventArgs Args)
        {
            MenuItem			Item=Sender as MenuItem;

            Topmost=Item.IsChecked;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------