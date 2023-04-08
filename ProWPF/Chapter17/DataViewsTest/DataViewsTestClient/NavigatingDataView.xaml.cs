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
	public partial class NavigatingDataView:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameCollection				MNames;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public NavigatingDataView()
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
			MListBox.ItemsSource=MNames;
            // !!!!! Pouzivam DB na DataContext, ktory JE CELA COLLECTION. ALE WPF JE DOST INTELIGENTNA NATO, ABY POCHOPILA, ZE CHCEM AKTUALNE SELECTOVANY ITEM A TAK PRAVE JEHO MI PRIRADI DO DB.
			MStackBar.DataContext=MNames;
		}
//------------------------------------------------------------------------
		private void OnUp(object Sender, RoutedEventArgs E)
		{
			ICollectionView					View=CollectionViewSource.GetDefaultView(MListBox.ItemsSource);

			View.MoveCurrentToPrevious();
		}
//------------------------------------------------------------------------
		private void OnDown(object Sender, RoutedEventArgs E)
		{
			ICollectionView					View=CollectionViewSource.GetDefaultView(MListBox.ItemsSource);

			View.MoveCurrentToNext();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------