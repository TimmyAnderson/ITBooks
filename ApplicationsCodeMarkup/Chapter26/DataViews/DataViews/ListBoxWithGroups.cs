using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	public partial class ListBoxWithGroups : Window
	{
//-------------------------------------------------------------------------------------------------------
        private ListCollectionView								MCollView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public ListBoxWithGroups()
        {
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void OpenOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            People			LPeople=People.Load(this);

            if (LPeople!=null)
            {
                MCollView=new ListCollectionView(LPeople);

                MCollView.SortDescriptions.Add(new SortDescription("BirthDate", ListSortDirection.Ascending));

                // Pridam CUSTOM TRIEDU impelementujucu GroupDescription.
                MCollView.GroupDescriptions.Add(new PeriodGroupDescription());

                MLstbox.ItemsSource=MCollView;

                if (MLstbox.Items.Count>0)
                    MLstbox.SelectedIndex=0;
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------