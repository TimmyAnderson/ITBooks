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
using ListViewTestLibrary;
//------------------------------------------------------------------------
namespace ListViewTestClient
{
//------------------------------------------------------------------------
	public partial class CustomListView:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameWithPhotoCollection	MNames;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CustomListView()
		{
			MNames=new CNameWithPhotoCollection();

			MNames.Add(new CNameWithPhoto("Jenny","Thompson",13,"Images/Photo1.jpg"));
			MNames.Add(new CNameWithPhoto("Atreyu","",12,"Images/Photo2.jpg"));
			MNames.Add(new CNameWithPhoto("Timmy","Anderson",12,"Images/Photo3.jpg"));
			MNames.Add(new CNameWithPhoto("Bubu","???0",15,"Images/Photo4.jpg"));

			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoaded(object Sender, RoutedEventArgs E)
		{
			MListView1.ItemsSource=MNames;
			MListView2.ItemsSource=MNames;
			MListView3.ItemsSource=MNames;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------