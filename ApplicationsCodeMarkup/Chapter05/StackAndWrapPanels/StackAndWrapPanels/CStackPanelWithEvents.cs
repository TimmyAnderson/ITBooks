using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
//------------------------------------------------------------------------------
namespace StackAndWrapPanels
{
//------------------------------------------------------------------------------
	public class CStackPanelWithEvents : Window
	{
//------------------------------------------------------------------------------
		public CStackPanelWithEvents()
		{
            Title = "Stack Ten Buttons";

            StackPanel		Stack=new StackPanel();

            Content=Stack;

			// !!!!! Kedze StackPanel NEMA 'Button.ClickEvent', avsak funguje ROUTOVANIE EVENTS do PARENT ELEMENTS, tak i na urovni PARENT StackPanel je mozne pomocou funkcie AddHandler() zachytavat EVENTS.
			Stack.AddHandler(Button.ClickEvent,new RoutedEventHandler(StackPanelOnClick));

            Random			Rand=new Random();

            for (int i=0;i<10;i++)
            {
                Button		Btn=new Button();

                Btn.Name=((char)('A' + i)).ToString();
                Btn.FontSize+=Rand.Next(10);
                Btn.Content="Button " + Btn.Name + " says 'Click me'";
                Btn.Click+=ButtonOnClick;

                Stack.Children.Add(Btn);
            }
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
			// Ziskam Button zo Sender, kedze ButtonOnClick() je viazany 
            Button			Btn=Sender as Button;

			Console.WriteLine(string.Format("ButtonOnClick() - Sender: [{0}], RoutedEventArgs.Source: [{1}] !",Sender,Args.Source));

            MessageBox.Show(string.Format("Button [{0}] has been clicked !",Btn.Name),"Button Click");
        }
//------------------------------------------------------------------------------
        private void StackPanelOnClick(object Sender, RoutedEventArgs Args)
        {
			Console.WriteLine(string.Format("StackPanelOnClick() - Sender: [{0}], RoutedEventArgs.Source: [{1}] !",Sender,Args.Source));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------