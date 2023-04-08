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
	public partial class CustomResources:System.Windows.Window
	{
//------------------------------------------------------------------------
		private int						MCounter1=0;
		private int						MCounter2=0;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CustomResources()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			CMyCustomClass		MCC=(CMyCustomClass) this.Resources["MCC"];

			MCC.SomeValue=string.Format("{0} - {1}",MCC.SomeValue,MCounter1++);
			MLabel1.Content=MCC;
			MLabel11.Content=MCC;
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			CMyFreezableClass	MFC=(CMyFreezableClass) this.Resources["MFC"];

			MFC.MyCustomValue=string.Format("Hello Jenny {0}",MCounter2++);
			MLabel2.Content=MFC;
			MLabel12.Content=MFC;
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			SolidColorBrush		SCB=(SolidColorBrush) this.Resources["MBrush"];

			SCB.Color=Colors.Blue;
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			CHasFreezableProperty	MHFP=(CHasFreezableProperty) this.Resources["MHFP"];

			MHFP.SomeFrozenValue=new CMyFreezableClass("Hi ALL !");
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			this.Resources["MHFP"]=new CHasFreezableProperty(new CMyFreezableClass("DeltaMK3"));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------