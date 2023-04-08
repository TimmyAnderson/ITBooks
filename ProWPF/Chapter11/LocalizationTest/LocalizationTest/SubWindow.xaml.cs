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
namespace LocalizationTest
{
//------------------------------------------------------------------------
	public partial class SubWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SubWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnButtonClick(object Sender, RoutedEventArgs E)
		{
			// !!! Tento text NIE JE LOKALIZOVANY. Finta ako to urobit je v SubWindowFromOtherLibrary.xaml.
			if (MessageBox.Show("Do You want to Close Window ?","Question",MessageBoxButton.YesNo)==MessageBoxResult.Yes)
				Close();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------