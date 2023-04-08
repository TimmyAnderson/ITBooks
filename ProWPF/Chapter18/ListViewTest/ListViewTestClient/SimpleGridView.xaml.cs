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
	public partial class SimpleGridView:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameCollection				MNames;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public SimpleGridView()
		{
			MNames=new CNameCollection();

			MNames.Add(new CName("Jenny","Thompson",13));
			MNames.Add(new CName("Atreyu","",12));
			MNames.Add(new CName("Timmy","Anderson",12));
			MNames.Add(new CName("Bubu","???0",15));

			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoaded(object Sender, RoutedEventArgs E)
		{
			MListView.ItemsSource=MNames;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------