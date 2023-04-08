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
namespace Menus
{
//------------------------------------------------------------------------------
	public class CDisableMenuItem : Window
	{
//------------------------------------------------------------------------------
        protected TextBlock										MText;
        protected MenuItem										MItemCut;
		protected MenuItem										MItemCopy;
		protected MenuItem										MItemPaste;
		protected MenuItem										MItemDelete;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CDisableMenuItem()
        {
            Title = "Cut, Copy, and Paste";

            DockPanel			MyDock=new DockPanel();

            Content=MyDock;

            Menu				MainMenu=new Menu();

            MyDock.Children.Add(MainMenu);
            DockPanel.SetDock(MainMenu, Dock.Top);

            MText=new TextBlock();
            MText.Text="Sample clipboard text";
            MText.HorizontalAlignment=HorizontalAlignment.Center;
            MText.VerticalAlignment=VerticalAlignment.Center;
            MText.FontSize=32;
            MText.TextWrapping=TextWrapping.Wrap;
            MyDock.Children.Add(MText);

            MenuItem			ItemEdit=new MenuItem();

            ItemEdit.Header="_Edit";
            ItemEdit.SubmenuOpened+=EditOnOpened;
            MainMenu.Items.Add(ItemEdit);

            MItemCut=new MenuItem();
            MItemCut.Header="Cu_t";
            MItemCut.Click+=CutOnClick;

            Image				Img=new Image();

            Img.Source=new BitmapImage(new Uri("pack://application:,,/Images/CutHS.png"));
            MItemCut.Icon=Img;
            ItemEdit.Items.Add(MItemCut);

            MItemCopy=new MenuItem();
            MItemCopy.Header="_Copy";
            MItemCopy.Click+=CopyOnClick;
            Img=new Image();
            Img.Source=new BitmapImage(new Uri("pack://application:,,/Images/CopyHS.png"));
            MItemCopy.Icon=Img;
            ItemEdit.Items.Add(MItemCopy);

            MItemPaste=new MenuItem();
            MItemPaste.Header="_Paste";
            MItemPaste.Click+=PasteOnClick;
            Img=new Image();
            Img.Source=new BitmapImage(new Uri("pack://application:,,/Images/PasteHS.png"));
            MItemPaste.Icon=Img;
            ItemEdit.Items.Add(MItemPaste);

            MItemDelete=new MenuItem();
            MItemDelete.Header="_Delete";
            MItemDelete.Click+=DeleteOnClick;
            Img=new Image();
            Img.Source=new BitmapImage(new Uri("pack://application:,,/Images/DeleteHS.png"));
            MItemDelete.Icon=Img;
            ItemEdit.Items.Add(MItemDelete);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected void EditOnOpened(object Sender, RoutedEventArgs Args)
        {
			// Enable nastavuje podla toho ci je v TextBox aspon 1 znak.
            MItemCut.IsEnabled=MItemCopy.IsEnabled=MItemDelete.IsEnabled=(MText.Text!=null && MText.Text.Length>0);

			// Enable nastavuje podla toho ci CLIPBOARD obsahuje TEXT.
            MItemPaste.IsEnabled=Clipboard.ContainsText();
        }
//------------------------------------------------------------------------------
        protected void CutOnClick(object Sender, RoutedEventArgs Args)
        {
            CopyOnClick(Sender, Args);
            DeleteOnClick(Sender, Args);
        }
//------------------------------------------------------------------------------
        protected void CopyOnClick(object Sender, RoutedEventArgs Args)
        {
            if (MText.Text!=null && MText.Text.Length>0)
                Clipboard.SetText(MText.Text);
        }
//------------------------------------------------------------------------------
        protected void PasteOnClick(object Sender, RoutedEventArgs Args)
        {
            if (Clipboard.ContainsText()==true)
                MText.Text=Clipboard.GetText();
        }
//------------------------------------------------------------------------------
        protected void DeleteOnClick(object Sender, RoutedEventArgs Args)
        {
            MText.Text=null;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------