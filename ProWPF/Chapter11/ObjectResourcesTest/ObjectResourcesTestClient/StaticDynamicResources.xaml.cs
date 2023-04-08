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
using ObjectResourcesTestLibrary;
//------------------------------------------------------------------------
namespace ObjectResourcesTestClient
{
//------------------------------------------------------------------------
	public partial class StaticDynamicResources:System.Windows.Window
	{
//------------------------------------------------------------------------
		public StaticDynamicResources()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			this.Resources["MRes"]=new CSimpleClass("Jenny");
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			Label		Lab=new Label();

			Lab.Content="YYY";
			this.Resources["MLabelResource"]=Lab;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------