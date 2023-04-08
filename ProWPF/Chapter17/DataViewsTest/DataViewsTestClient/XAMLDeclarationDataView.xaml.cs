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
using DataViewsTestLibrary;
//------------------------------------------------------------------------
namespace DataViewsTestClient
{
//------------------------------------------------------------------------
	public partial class XAMLDeclarationDataView:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameCollection				MNames;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public XAMLDeclarationDataView()
		{
			MNames=new CNameCollection();

			MNames.Add(new CName("Jenny","Thompson",13));
			MNames.Add(new CName("Timmy","Anderson",12));
			MNames.Add(new CName("Atreyu","",12));
			MNames.Add(new CName("Bubu","",15));

			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoaded(object Sender, RoutedEventArgs E)
		{
			// Vytiahnem CollectionViewSource z Resource.
			CollectionViewSource		ViewSource=(CollectionViewSource) this.FindResource("MGroupByRangeView");

			ViewSource.Source=MNames;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------