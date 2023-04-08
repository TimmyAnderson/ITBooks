using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace NavigationServiceTest
{
//------------------------------------------------------------------------
	public partial class SubPage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		public SubPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			NavigationService		NS=NavigationService.GetNavigationService(this);

			NS.Navigate(new Uri("ContentPage1.xaml",UriKind.RelativeOrAbsolute));
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			NavigationService		NS=NavigationService.GetNavigationService(this);

			NS.Navigate(new Uri("ContentPage2.xaml",UriKind.RelativeOrAbsolute));
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			NavigationService		NS=NavigationService.GetNavigationService(this);

			if (NS.CanGoBack==true)
				NS.GoBack();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			NavigationService		NS=NavigationService.GetNavigationService(this);

			if (NS.CanGoForward==true)
				NS.GoForward();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------