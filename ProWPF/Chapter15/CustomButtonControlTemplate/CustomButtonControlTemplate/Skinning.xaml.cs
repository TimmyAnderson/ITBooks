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
namespace CustomButtonControlTemplate
{
//------------------------------------------------------------------------
	public partial class Skinning:System.Windows.Window
	{
//------------------------------------------------------------------------
		private bool						MDefaultSkin=true;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public Skinning()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			MDefaultSkin=!MDefaultSkin;

			string					RDName;

			if (MDefaultSkin==true)
				RDName="Resources/MyTemplateRD1.xaml";
			else
				RDName="Resources/MyTemplateRD2.xaml";

			ResourceDictionary		NewDictionary=new ResourceDictionary();

			NewDictionary.Source=new Uri(RDName,UriKind.Relative);
			// Vlozim RD do Collection na 0. poziciu.
			this.Resources.MergedDictionaries[0]=NewDictionary;
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			MDefaultSkin=!MDefaultSkin;

			ResourceDictionary		NewDictionary;

			if (MDefaultSkin==true)
				NewDictionary=new MyTemplateRD1();
			else
				NewDictionary=new MyTemplateRD2();

			// Vlozim RD do Collection na 0. poziciu.
			this.Resources.MergedDictionaries[0]=NewDictionary;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------