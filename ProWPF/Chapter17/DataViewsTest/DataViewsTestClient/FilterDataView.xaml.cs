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
using System.ComponentModel;
using DataViewsTestLibrary;
//------------------------------------------------------------------------
namespace DataViewsTestClient
{
//------------------------------------------------------------------------
	public partial class FilterDataView:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameCollection				MNames1;
		private CNameCollection				MNames2;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public FilterDataView()
		{
			MNames1=new CNameCollection();

			MNames1.Add(new CName("Jenny","Thompson",13));
			MNames1.Add(new CName("Atreyu","",12));
			MNames1.Add(new CName("Bubu","",15));
			MNames1.Add(new CName("Timmy","Anderson",12));

			MNames2=new CNameCollection();

			MNames2.Add(new CName("Jenny","Thompson",13));
			MNames2.Add(new CName("Atreyu","",12));
			MNames2.Add(new CName("Bubu","",15));
			MNames2.Add(new CName("Timmy","Anderson",12));

			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoaded(object Sender, RoutedEventArgs E)
		{
			MListBox1.ItemsSource=MNames1;
			MListBox2.ItemsSource=MNames2;
		}
//------------------------------------------------------------------------
		private void OnReevaluateFilterClick(object Sender, RoutedEventArgs E)
		{
			ICollectionView					View1=CollectionViewSource.GetDefaultView(MListBox1.ItemsSource);
			ICollectionView					View2=CollectionViewSource.GetDefaultView(MListBox2.ItemsSource);
			CTeenagerFilter					TeenagerFilter=new CTeenagerFilter();

			View1.Filter=TeenagerFilter.FilterOnlyTeenegers;
			// Evaluujem Filter.
			View1.Refresh();

			View2.Filter=TeenagerFilter.FilterOnlyNonTeenegers;
			// Evaluujem Filter.
			View2.Refresh();
		}
//------------------------------------------------------------------------
		private void OnRemoveFilterClick(object Sender, RoutedEventArgs E)
		{
			ICollectionView					View1=CollectionViewSource.GetDefaultView(MListBox1.ItemsSource);
			ICollectionView					View2=CollectionViewSource.GetDefaultView(MListBox2.ItemsSource);

			// Zrusim filter a tym aj filtraciu.
			View1.Filter=null;

			// Zrusim filter a tym aj filtraciu.
			View2.Filter=null;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------