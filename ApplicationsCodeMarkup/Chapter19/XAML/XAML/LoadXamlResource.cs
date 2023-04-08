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
	public class LoadXamlResource : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        public LoadXamlResource()
        {
            Title = "Load Xaml Resource";

            Uri					URI=new Uri("pack://application:,,,/LoadXamlResource.xml");
            Stream				Stream=Application.GetResourceStream(URI).Stream;
            FrameworkElement	El=XamlReader.Load(Stream) as FrameworkElement;

            Content=El;

            Button				Btn=El.FindName("MyButton") as Button;

            if (Btn!=null)
                Btn.Click+=ButtonOnClick;
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            MessageBox.Show(string.Format("The button labeled '{0}' has been clicked !",(Args.Source as Button).Content));
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------