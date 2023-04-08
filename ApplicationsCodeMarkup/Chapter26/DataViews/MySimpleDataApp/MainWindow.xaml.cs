using System;
using System.Collections.Generic;
using System.Collections;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
//-------------------------------------------------------------------------------------------------------
namespace MySimpleDataApp
{
//-------------------------------------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//-------------------------------------------------------------------------------------------------------
		private CPersonCollection								MPersons;
        private ICollectionView									MCollectionView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MPersons=new CPersonCollection();

			MPersons.Add(new CPerson("Timmy","Anderson",12));
			MPersons.Add(new CPerson("Atreyu","",12));
			MPersons.Add(new CPerson("Jenny","Thompson",13));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void Window_Loaded(object Sender, RoutedEventArgs E)
		{
			MCollectionView=CollectionViewSource.GetDefaultView(MPersons);
			MGrid.DataContext=MCollectionView;
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTLeft_Click(object Sender, RoutedEventArgs E)
		{
			if (MCollectionView.CurrentPosition>0)
				MCollectionView.MoveCurrentToPrevious();
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTRight_Click(object Sender, RoutedEventArgs E)
		{
			if (MCollectionView.CurrentPosition<(MPersons.Count-1))
				MCollectionView.MoveCurrentToNext();
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTAdd_Click(object Sender, RoutedEventArgs E)
		{
			MPersons.Add(new CPerson());
			MCollectionView.MoveCurrentToLast();
		}
//-------------------------------------------------------------------------------------------------------
		private void MBUTRemove_Click(object Sender, RoutedEventArgs E)
		{
			if (MCollectionView.CurrentItem!=null)
				MPersons.Remove((CPerson) MCollectionView.CurrentItem);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------