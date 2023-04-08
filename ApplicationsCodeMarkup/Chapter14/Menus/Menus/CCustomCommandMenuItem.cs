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
	public class CCustomCommandMenuItem : Window
	{
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CCustomCommandMenuItem()
        {
            Title = "Command the Menu";

            DockPanel				MyDock=new DockPanel();

            Content=MyDock;

            Menu				MyMenu=new Menu();

            MyDock.Children.Add(MyMenu);
            DockPanel.SetDock(MyMenu, Dock.Top);

            MenuItem				File=new MenuItem();

            File.Header="_File";
            MyMenu.Items.Add(File);

			// Vytvorim kolekciu GESTURES.
			InputGestureCollection	IGC=new InputGestureCollection();

			// Pridam aspon 1 GESTURE.
			IGC.Add(new KeyGesture(Key.Q,ModifierKeys.Control));

			// Vytvorim CUSTOM COMMAND.
			RoutedUICommand			CustomCommand=new RoutedUICommand("My _exit","MyExit",GetType(),IGC);

            MenuItem				CustomExitCommand=new MenuItem();

			// Priradim Command CUSTOM COMMAND do Command.
            CustomExitCommand.Command=CustomCommand;
            File.Items.Add(CustomExitCommand);

            // Vykonam BINDING pre CUSTOM COMMAND.
            CommandBindings.Add(new CommandBinding(CustomCommand, MyExitOnExecute, MyExitCanExecute));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void MyExitCanExecute(object Sender, CanExecuteRoutedEventArgs Args)
        {
            Args.CanExecute=true;
        }
//------------------------------------------------------------------------------
        private void MyExitOnExecute(object Sender, ExecutedRoutedEventArgs Args)
        {
			Close();
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------