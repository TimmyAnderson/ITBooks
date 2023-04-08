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
	public class CScrollViewer : Window
	{
//------------------------------------------------------------------------------
		public CScrollViewer()
		{
            Title="Scroll Fifty Buttons";
            SizeToContent=SizeToContent.Width;
            AddHandler(Button.ClickEvent, new RoutedEventHandler(ButtonOnClick));

            ScrollViewer		Scroll=new ScrollViewer();

            Content=Scroll;

            StackPanel			Stack=new StackPanel();

            Stack.Margin=new Thickness(5);
            Scroll.Content=Stack; 

            for (int i=0;i<50;i++)
            {
                Button			Btn = new Button();

                Btn.Name="Button"+(i + 1);
                Btn.Content=Btn.Name + " says 'Click me'";
                Btn.Margin=new Thickness(5);

                Stack.Children.Add(Btn);
            }
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Zachytava i Events z buttons ScrollViewer.
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
			// Ziskam Button zo Sender, kedze ButtonOnClick() je viazany 
            Button			Btn=Sender as Button;

			Console.WriteLine(string.Format("ButtonOnClick() - Sender: [{0}], RoutedEventArgs.Source: [{1}] !",Sender,Args.Source));

			if (Btn!=null)
				MessageBox.Show(string.Format("Button [{0}] has been clicked !",Btn.Name),"Button Click");
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------