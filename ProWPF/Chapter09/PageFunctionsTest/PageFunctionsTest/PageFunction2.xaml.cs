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
namespace PageFunctionsTest
{
//------------------------------------------------------------------------
	public partial class PageFunction2:System.Windows.Navigation.PageFunction<String>
	{
//------------------------------------------------------------------------
		public PageFunction2()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnOKClick(object Sender, RoutedEventArgs E)
		{
			string				Value1=MValue1.Text;
			string				Value2=MValue2.Text;
			string				Result=Value1 + " " + Value2;

			OnReturn(new ReturnEventArgs<string>(Result));
		}
//------------------------------------------------------------------------
		private void OnCancelClick(object Sender, RoutedEventArgs E)
		{
			// !!! FP sa skonci, ale bez navratovej hodnoty.
			OnReturn(null);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------