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
using ComboBoxTestLibrary;
//------------------------------------------------------------------------
namespace ComboBoxTestClient
{
//------------------------------------------------------------------------
	public partial class EditableComboBox:System.Windows.Window
	{
//------------------------------------------------------------------------
		private CNameCollection				MNames;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public EditableComboBox()
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
			MComboBox1.ItemsSource=MNames;
			MComboBox2.ItemsSource=MNames;
			MComboBox3.ItemsSource=MNames;
			MComboBox4.ItemsSource=MNames;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------