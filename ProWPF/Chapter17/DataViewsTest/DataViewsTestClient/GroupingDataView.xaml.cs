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
	public partial class GroupingDataView:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameCollection				MNames1;
		private CNameCollection				MNames2;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public GroupingDataView()
		{
			MNames1=new CNameCollection();

			MNames1.Add(new CName("Jenny","Thompson",13));
			MNames1.Add(new CName("Timmy","Anderson",12));
			MNames1.Add(new CName("Atreyu","",12));
			MNames1.Add(new CName("Bubu","",15));

			MNames2=new CNameCollection();

			MNames2.Add(new CName("Jenny","Thompson",13));
			MNames2.Add(new CName("Timmy","Anderson",12));
			MNames2.Add(new CName("Atreyu","",12));
			MNames2.Add(new CName("Bubu","",15));

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
			ListCollectionView				View2=(ListCollectionView) CollectionViewSource.GetDefaultView(MListBox2.ItemsSource);

			View1.SortDescriptions.Add(new SortDescription("Age",ListSortDirection.Descending));
			View1.SortDescriptions.Add(new SortDescription("FirstName",ListSortDirection.Ascending));

			// Vytvaram Grouping na zaklade property Age.
			View1.GroupDescriptions.Add(new PropertyGroupDescription("Age"));

			// Evaluujem Sort.
			View1.Refresh();

			// Custom Sort.
			View2.CustomSort=new CAgeSorter();

			// Vytvaram Grouping na zaklade property Age.
			// !!! Pridam CUSTOM Converter, ktory vytvori 3 Groups pre Pre-teen, Teenegerov a Adults.
			View2.GroupDescriptions.Add(new PropertyGroupDescription("Age",new CAgeGroupConverter()));

			// Evaluujem Sort.
			View2.Refresh();
		}
//------------------------------------------------------------------------
		private void OnRemoveFilterClick(object Sender, RoutedEventArgs E)
		{
			ICollectionView					View1=CollectionViewSource.GetDefaultView(MListBox1.ItemsSource);
			ListCollectionView				View2=(ListCollectionView) CollectionViewSource.GetDefaultView(MListBox2.ItemsSource);

			// Zrusim sort a tym aj sorting.
			View1.SortDescriptions.Clear();

			View1.GroupDescriptions.Clear();

			// Zrusim sort a tym aj sorting.
			View2.CustomSort=null;

			View2.GroupDescriptions.Clear();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------