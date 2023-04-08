using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Navigation;
//-----------------------------------------------------------------------------------------------------------------
namespace FrameTest
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class Page2 : Page
	{
//-----------------------------------------------------------------------------------------------------------------
        private void ButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            NavigationService.Navigate(new Uri("Page1.xaml", UriKind.Relative));
        }
//-----------------------------------------------------------------------------------------------------------------
        private void HyperlinkOnRequestNavigate(object Sender, RequestNavigateEventArgs Args)
        {
            NavigationService.Navigate(Args.Uri);
            Args.Handled = true;
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------