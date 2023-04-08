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
	public class CContextMenu : Window
	{
//------------------------------------------------------------------------------
		private ContextMenu										MCM;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CContextMenu()
        {
            Title = "Command the Menu";

			Button					MyButton=new Button();

			this.MouseLeftButtonDown+=new MouseButtonEventHandler(CContextMenu_MouseLeftButtonDown);

			MyButton.Content="Button has CONTEXT MENU";
			MyButton.Click+=new RoutedEventHandler(MyButton_Click);
			MyButton.HorizontalAlignment=HorizontalAlignment.Center;
			MyButton.VerticalAlignment=VerticalAlignment.Center;

			AddChild(MyButton);

			MCM=new ContextMenu();

			// Vytvorim kolekciu GESTURES.
			InputGestureCollection	IGC=new InputGestureCollection();

			// Pridam aspon 1 GESTURE.
			IGC.Add(new KeyGesture(Key.Q,ModifierKeys.Control));

			// Vytvorim CUSTOM COMMAND.
			RoutedUICommand			CustomCommand=new RoutedUICommand("My _exit","MyExit",GetType(),IGC);

            MenuItem				CustomExitCommand=new MenuItem();

			// !!!!! Kvoli CHYBE WPF, ktora je tam ESTE OD ROKU 2007 je treba vykonat toto nastavenie, inak ROUTING EVENTU XXXCanExecute() NEPREJDE cez TREE a NEZAVOLA SA MOJA VERZIA XXXCanExecute() co je v tomto pripade metoda MyExitCanExecute().
			// !!!!! Pouzijem 'this', kedze NIZSIE v kode som spravil COMMAND BINDING prave na Window, teda 'this' objekt.
			CustomExitCommand.CommandTarget=this;

			// Priradim Command CUSTOM COMMAND do Command.
            CustomExitCommand.Command=CustomCommand;

			// Pridam MenuItem do CONTEXT MENU.
            MCM.Items.Add(CustomExitCommand);

            // Vykonam BINDING pre CUSTOM COMMAND.
            CommandBindings.Add(new CommandBinding(CustomCommand, MyExitOnExecute, MyExitCanExecute));

			// !!! Zapnem AUTOMATICKE VYVOLANIE CONTEXT MENU.
			MyButton.ContextMenu=MCM;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void MyExitCanExecute(object Sender, CanExecuteRoutedEventArgs Args)
        {
			Console.WriteLine("CanExecute() CALLED !");

            Args.CanExecute=true;
        }
//------------------------------------------------------------------------------
        private void MyExitOnExecute(object Sender, ExecutedRoutedEventArgs Args)
        {
			MessageBox.Show("Some EVENT !");
        }
//------------------------------------------------------------------------------
		private void MyButton_Click(object Sender, RoutedEventArgs E)
		{
			// Manualne zobrazim ContextMenu.
			if (MCM.IsOpen==false)
				MCM.IsOpen=true;
		}
//------------------------------------------------------------------------------
		private void CContextMenu_MouseLeftButtonDown(object Sender, MouseButtonEventArgs e)
		{
			// Manualne zobrazim ContextMenu.
			if (MCM.IsOpen==false)
				MCM.IsOpen=true;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------