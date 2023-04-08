using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using BindingCollectionLibrary;
//------------------------------------------------------------------------
namespace BindingCollectionClient
{
//------------------------------------------------------------------------
	public partial class ObservableCollectionWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CMyCustomObservableCollection	MCollection;
		private int								MCounter=0;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public ObservableCollectionWindow()
		{
			MCollection=new CMyCustomObservableCollection();

			MCollection.Add(new CName("Jenny","Thompson",13));
			MCollection.Add(new CName("Atreyu","",12));
			MCollection.Add(new CName("Timmy","Anderson",12));

			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnGetData(object Sender, RoutedEventArgs E)
		{
			// Namapujem MCollection na ItemsSource.
			MList.ItemsSource=MCollection;
		}
//------------------------------------------------------------------------
		private void OnPrintData(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine(MCollection.ToString());
		}
//------------------------------------------------------------------------
		private void OnSetFirstName(object Sender, RoutedEventArgs E)
		{
			if (MList.SelectedIndex==-1)
				return;

			CName		Name=MCollection[MList.SelectedIndex];

			Name.FirstName="Bubu";
		}
//------------------------------------------------------------------------
		private void OnSetLastName(object Sender, RoutedEventArgs E)
		{
			if (MList.SelectedIndex==-1)
				return;

			CName		Name=MCollection[MList.SelectedIndex];

			Name.LastName="???0";
		}
//------------------------------------------------------------------------
		private void OnSetAge(object Sender, RoutedEventArgs E)
		{
			if (MList.SelectedIndex==-1)
				return;

			CName		Name=MCollection[MList.SelectedIndex];

			Name.Age=15;
		}
//------------------------------------------------------------------------
		private void OnAddNewItem(object Sender, RoutedEventArgs E)
		{
			MCounter++;

			CName		Name=new CName(string.Format("Timmy {0}",MCounter),string.Format("Anderson {0}",MCounter),12+MCounter);

			MCollection.Add(Name);
		}
//------------------------------------------------------------------------
		private void OnRemoveItem(object Sender, RoutedEventArgs E)
		{
			if (MList.SelectedIndex==-1)
				return;

			MCollection.RemoveAt(MList.SelectedIndex);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------