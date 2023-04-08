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
	public class CCommandMenuItem : Window
	{
//------------------------------------------------------------------------------
        private TextBlock										MText;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CCommandMenuItem()
        {
            Title = "Command the Menu";

            DockPanel				MyDock=new DockPanel();

            Content=MyDock;

            Menu				MyMenu=new Menu();

            MyDock.Children.Add(MyMenu);
            DockPanel.SetDock(MyMenu, Dock.Top);

            MText=new TextBlock();
            MText.Text="Sample clipboard text";
            MText.HorizontalAlignment=HorizontalAlignment.Center;
            MText.VerticalAlignment=VerticalAlignment.Center;
            MText.FontSize=32;
            MText.TextWrapping=TextWrapping.Wrap;
            MyDock.Children.Add(MText);

            MenuItem			ItemEdit=new MenuItem();

            ItemEdit.Header="_Edit";
            MyMenu.Items.Add(ItemEdit);

            MenuItem			ItemCut=new MenuItem();

            ItemCut.Header="Cu_t";
			// Priradim Command.
            ItemCut.Command=ApplicationCommands.Cut;
            ItemEdit.Items.Add(ItemCut);

            MenuItem			ItemCopy=new MenuItem();

            ItemCopy.Header="_Copy";
			// Priradim Command.
            ItemCopy.Command=ApplicationCommands.Copy;
            ItemEdit.Items.Add(ItemCopy);

            MenuItem			ItemPaste=new MenuItem();

            ItemPaste.Header="_Paste";
			// Priradim Command.
            ItemPaste.Command=ApplicationCommands.Paste;
            ItemEdit.Items.Add(ItemPaste);

            MenuItem			ItemDelete = new MenuItem();

            ItemDelete.Header="_Delete";
			// Priradim Command.
            ItemDelete.Command=ApplicationCommands.Delete;
            ItemEdit.Items.Add(ItemDelete);

            // Vykonam BINDING pre COMMANDS.
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Cut, CutOnExecute, CutCanExecute));
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Copy, CopyOnExecute, CutCanExecute));
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Paste, PasteOnExecute, PasteCanExecute));
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Delete, DeleteOnExecute, CutCanExecute));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void CutCanExecute(object Sender, CanExecuteRoutedEventArgs Args)
        {
            Args.CanExecute=(MText.Text!=null && MText.Text.Length>0);
        }
//------------------------------------------------------------------------------
        private void PasteCanExecute(object Sender, CanExecuteRoutedEventArgs Args)
        {
            Args.CanExecute=Clipboard.ContainsText();
        }
//------------------------------------------------------------------------------
        private void CutOnExecute(object Sender, ExecutedRoutedEventArgs Args)
        {
            ApplicationCommands.Copy.Execute(null, this);
            ApplicationCommands.Delete.Execute(null, this);
        }
//------------------------------------------------------------------------------
        private void CopyOnExecute(object Sender, ExecutedRoutedEventArgs Args)
        {
            Clipboard.SetText(MText.Text);
        }
//------------------------------------------------------------------------------
        private void PasteOnExecute(object Sender, ExecutedRoutedEventArgs Args)
        {
            MText.Text=Clipboard.GetText();
        }
//------------------------------------------------------------------------------
        private void DeleteOnExecute(object Sender, ExecutedRoutedEventArgs Args)
        {
            MText.Text=null;
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------