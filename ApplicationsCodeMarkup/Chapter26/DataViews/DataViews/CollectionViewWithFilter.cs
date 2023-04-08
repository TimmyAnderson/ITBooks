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
	public partial class CollectionViewWithFilter : Window
	{
//-------------------------------------------------------------------------------------------------------
        private ListCollectionView								MCollView;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CollectionViewWithFilter()
        {
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void OpenOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            People		LPeople=People.Load(this);

            if (LPeople!=null)
            {
                MCollView=new ListCollectionView(LPeople);

                MCollView.SortDescriptions.Add(new SortDescription("LastName",ListSortDirection.Ascending));

                MLstbox.ItemsSource=MCollView;

                if (MLstbox.Items.Count>0)
                    MLstbox.SelectedIndex=0;

                MRadioAll.IsChecked=true;
            }
        }
//-------------------------------------------------------------------------------------------------------
        private void RadioOnChecked(object Sender, RoutedEventArgs Args)
        {
            if (MCollView==null)
                return;

            RadioButton			Radio=Args.Source as RadioButton;

			// Pouzijem Name na identifikaciu CheckBox.
            switch (Radio.Name)
            {
                case "MRadioLiving":
                    MCollView.Filter=PersonIsLiving;
                break;

                case "MRadioDead":
                    MCollView.Filter=PersonIsDead;
                break;

                case "MRadioAll":
                    MCollView.Filter=null;
                break;
            }
        }
//-------------------------------------------------------------------------------------------------------
		// Filter.
        private bool PersonIsLiving(object Obj)
        {
            return((Obj as Person).DeathDate==null);
        }
//-------------------------------------------------------------------------------------------------------
		// Filter.
        private bool PersonIsDead(object Obj)
        {
            return((Obj as Person).DeathDate!=null);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------