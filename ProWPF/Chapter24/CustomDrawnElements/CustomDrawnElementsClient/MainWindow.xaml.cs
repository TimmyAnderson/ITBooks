using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje vytvorenie Custom Drawn Element.
// 2. CDE je taky Element, kde realizujem Custom Drawing implementovanim metody OnRender().
// !!! 3. Pri kresleni do DrawingContext sa v skutocnosti NEKRESLI NA OBRAZKU, ale iba do buffera odkial potom pri realnom renderingu sa obsah vykresli na obrazovku. To sa vsak uz deje PLNE V REZII WPF.
//------------------------------------------------------------------------
namespace CustomDrawnElementsClient
{
	//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			CustomDrawnElementTest		Win=new CustomDrawnElementTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			CustomDrawnElementChrome	Win=new CustomDrawnElementChrome();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------