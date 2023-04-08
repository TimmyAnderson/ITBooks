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
// 1. Program demonstruje pouzitie NavigationService umoznujuceho z kodu ovladat navigaciu medzi Pages.
// !!! 2. NavigationService je NUTNE VZDY ZISAKT POMOCOU GetNavigationService(). Iba tak dosiahnem NEZAVISLOST NA HOST.
// 3. NavigationService dokaze vysielat mnoho Events. Tieto je mozne vsak zachytavat IBA na UROVNI PageContainer NIE SAMOTNEJ PAGE. Takisto je ich mozne zachytavat na urovni Application co je NAJIDEALNEJSIE.
//------------------------------------------------------------------------
namespace NavigationServiceTest
{
//------------------------------------------------------------------------
	public partial class MainPage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		public MainPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLargePage(object Sender, RoutedEventArgs E)
		{
			NavigationService		NS=NavigationService.GetNavigationService(this);

			// !!! Mozem prenasat CUSTOM OBJECT.
			NS.Navigate(new Uri("LargePage.xaml",UriKind.RelativeOrAbsolute),"Hello WORLD !!!");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------