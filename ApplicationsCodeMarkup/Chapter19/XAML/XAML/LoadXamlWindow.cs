using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
//-----------------------------------------------------------------------------------------------------------------
namespace XAML
{
//-----------------------------------------------------------------------------------------------------------------
	// Nededi z WINDOW.
	public static class LoadXamlWindow
	{
//-----------------------------------------------------------------------------------------------------------------
        private static void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            MessageBox.Show(string.Format("The button labeled '{0}' has been clicked !",(Args.Source as Button).Content));
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public static void Start()
        {
            Application			App=new Application();
            Uri					URI=new Uri("pack://application:,,,/LoadXamlWindow.xml");
            Stream				Stream=Application.GetResourceStream(URI).Stream;
            Window				Win=XamlReader.Load(Stream) as Window;

            Win.AddHandler(Button.ClickEvent, new RoutedEventHandler(ButtonOnClick));
            App.Run(Win);
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------