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
using TreeViewTestLibrary;
//------------------------------------------------------------------------
namespace TreeViewTestClient
{
//------------------------------------------------------------------------
	public partial class DBTreeView:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CGenderCollection				MGenders;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public DBTreeView()
		{
			MGenders=new CGenderCollection();

			CNameCollection			Girls=new CNameCollection();

			Girls.Add(new CName("Jenny","Thompson",12));
			Girls.Add(new CName("Tina","RRR",11));

			MGenders.Add(new CGender("Girls",Girls));

			CNameCollection			Boys=new CNameCollection();

			Boys.Add(new CName("Timmy","Anderson",12));
			Boys.Add(new CName("Atreyu","",12));
			Boys.Add(new CName("Bubu","???0",15));

			MGenders.Add(new CGender("Boys",Boys));

			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnLoaded(object Sender, RoutedEventArgs E)
		{
			MTreeView.ItemsSource=MGenders;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------