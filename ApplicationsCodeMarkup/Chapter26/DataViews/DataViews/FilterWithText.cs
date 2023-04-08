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
	public partial class FilterWithText : Window
	{
//-------------------------------------------------------------------------------------------------------
        private ListCollectionView								MCollView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public FilterWithText()
        {
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        void OpenOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            People			LPeople=People.Load(this);

            if (LPeople!=null)
            {
                MCollView=new ListCollectionView(LPeople);

                MCollView.SortDescriptions.Add(new SortDescription("BirthDate", ListSortDirection.Ascending));

                MTxtboxFilter.Text="";
                MCollView.Filter=LastNameFilter;

                MLstbox.ItemsSource=MCollView;

                if (MLstbox.Items.Count>0)
                    MLstbox.SelectedIndex=0;
            }
        }
//-------------------------------------------------------------------------------------------------------
        private bool LastNameFilter(object Obj)
        {
            return((Obj as Person).LastName.StartsWith(MTxtboxFilter.Text, StringComparison.CurrentCultureIgnoreCase));
        }
//-------------------------------------------------------------------------------------------------------
        private void TextBoxOnTextChanged(object Sender, TextChangedEventArgs Args)
        {
            if (MCollView==null)
                return;

			// Musim pri kazdom novom znaku zavolat Refresh().
            MCollView.Refresh();
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------