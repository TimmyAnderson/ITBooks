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
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace LocalizationTestLibrary
{
//------------------------------------------------------------------------
	public partial class SubWindowFromOtherLibrary:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SubWindowFromOtherLibrary()
		{
			InitializeComponent();

		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnButtonClick(object Sender, RoutedEventArgs E)
		{
			string		Message=(string) MWindow.Resources["MB_Text"];
			string		Caption=(string) MWindow.Resources["MB_Caption"];

			if (MessageBox.Show(Message,Caption,MessageBoxButton.YesNo)==MessageBoxResult.Yes)
				Close();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------