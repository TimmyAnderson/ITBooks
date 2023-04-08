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
namespace PageInNavigationWindowTest
{
//------------------------------------------------------------------------
	public partial class MySimplePage:System.Windows.Controls.Page
	{
		public MySimplePage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Rucna navigacia na inu Page.
		private void OnHyperlinkClick(object Sender, RoutedEventArgs E)
		{
			this.NavigationService.Navigate(new Uri("SubPage2.xaml",UriKind.Relative));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------