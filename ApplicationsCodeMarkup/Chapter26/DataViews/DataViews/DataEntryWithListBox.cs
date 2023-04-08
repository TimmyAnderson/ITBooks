using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Specialized;
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
	public partial class DataEntryWithListBox
	{
//-------------------------------------------------------------------------------------------------------
        private ListCollectionView								MCollview;
        private People											MPeople;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public DataEntryWithListBox()
        {
            InitializeComponent();

            ApplicationCommands.New.Execute(null, this);

            MPnlPerson.Children[1].Focus();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void NewOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MPeople=new People();
            MPeople.Add(new Person());
            InitializeNewPeopleObject();
        }
//-------------------------------------------------------------------------------------------------------
        private void OpenOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MPeople=People.Load(this);

            if (MPeople!=null)
                InitializeNewPeopleObject();
        }
//-------------------------------------------------------------------------------------------------------
        private void SaveOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MPeople.Save(this);
        }
//-------------------------------------------------------------------------------------------------------
        private void InitializeNewPeopleObject()
        {
            MCollview=new ListCollectionView(MPeople);

            // Definujem SORTING.
            MCollview.SortDescriptions.Add(new SortDescription("LastName", ListSortDirection.Ascending));

            MLstbox.ItemsSource = MCollview;
            MPnlPerson.DataContext = MCollview;

            if (MLstbox.Items.Count>0)
                MLstbox.SelectedIndex=0;
        }
//-------------------------------------------------------------------------------------------------------
        private void AddOnClick(object Sender, RoutedEventArgs Args)
        {
            Person			LPerson=new Person();
			
            MPeople.Add(LPerson);
            MLstbox.SelectedItem=LPerson;
            MPnlPerson.Children[1].Focus();
            MCollview.Refresh();
        }
//-------------------------------------------------------------------------------------------------------
        private void DeleteOnClick(object Sender, RoutedEventArgs Args)
        {
            if (MLstbox.SelectedItem!=null)
            {
                MPeople.Remove(MLstbox.SelectedItem as Person);

                if (MLstbox.Items.Count > 0)
                    MLstbox.SelectedIndex = 0;
                else
                    AddOnClick(Sender, Args);
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------