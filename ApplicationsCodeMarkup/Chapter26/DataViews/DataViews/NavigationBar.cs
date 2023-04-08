using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	public partial class NavigationBar : ToolBar
	{
//-------------------------------------------------------------------------------------------------------
        private IList											MColl;
        private ICollectionView									MCollview;
        private Type											MTypeItem;
        private string											MStrOriginal;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public NavigationBar()
        {
            InitializeComponent();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public IList											Collection
        {
            get
            {
                return(MColl);
            }
            set
            {
                MColl=value;

                // Ziskam DEFAULT CollectionViewSource z COLLECTION.
                MCollview=CollectionViewSource.GetDefaultView(MColl);
				// Zaregistrujem EVENTS pre zmeny.
                MCollview.CurrentChanged+=CollectionViewOnCurrentChanged;
                MCollview.CollectionChanged+=CollectionViewOnCollectionChanged;

                CollectionViewOnCurrentChanged(null, null);

				// Ulozim velkost VIEW.
                MTxtblkTotal.Text=MColl.Count.ToString();
            }
        }
//-------------------------------------------------------------------------------------------------------
		// Typ RECORD.
        public Type												ItemType
        {
            get
			{
				return(MTypeItem);
			}
            set
			{
				MTypeItem=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        private void CollectionViewOnCollectionChanged(object Sender, NotifyCollectionChangedEventArgs Args)
        {
            MTxtblkTotal.Text=MColl.Count.ToString();
        }
//-------------------------------------------------------------------------------------------------------
        private void CollectionViewOnCurrentChanged(object Sender, EventArgs Args)
        {
			// Urobim ENABLE/DISABLE buttons podla aktualnej pozicie.
            MTxtboxCurrent.Text=(1+MCollview.CurrentPosition).ToString();
            MBtnPrev.IsEnabled=(MCollview.CurrentPosition>0);
            MBtnNext.IsEnabled=(MCollview.CurrentPosition<(MColl.Count-1));
            MBtnDel.IsEnabled=(MColl.Count>1);
        }
//-------------------------------------------------------------------------------------------------------
        private void FirstOnClick(object Sender, RoutedEventArgs Args)
        {
			// Pouzivam VIEW na pohyb v kolekcii.
            MCollview.MoveCurrentToFirst();
        }
//-------------------------------------------------------------------------------------------------------
        private void PreviousOnClick(object Sender, RoutedEventArgs Args)
        {
			// Pouzivam VIEW na pohyb v kolekcii.
            MCollview.MoveCurrentToPrevious();
        }
//-------------------------------------------------------------------------------------------------------
        private void NextOnClick(object Sender, RoutedEventArgs Args)
        {
			// Pouzivam VIEW na pohyb v kolekcii.
            MCollview.MoveCurrentToNext();
        }
//-------------------------------------------------------------------------------------------------------
        private void LastOnClick(object Sender, RoutedEventArgs Args)
        {
			// Pouzivam VIEW na pohyb v kolekcii.
            MCollview.MoveCurrentToLast();
        }
//-------------------------------------------------------------------------------------------------------
        private void AddOnClick(object Sender, RoutedEventArgs Args)
        {
			// Pri pridani noveho RECORD vytvorim jeho instanciu.
            ConstructorInfo			Info=MTypeItem.GetConstructor(Type.EmptyTypes);

			// Novy RECORD pridam do KOLEKCIE nad ktorou je postaveny VIEW.
            MColl.Add(Info.Invoke(null));

			// Pouzivam VIEW na pohyb v kolekcii.
            MCollview.MoveCurrentToLast();
        }
//-------------------------------------------------------------------------------------------------------
        private void DeleteOnClick(object Sender, RoutedEventArgs Args)
        {
            MColl.RemoveAt(MCollview.CurrentPosition);
        }
//-------------------------------------------------------------------------------------------------------
        private void TextBoxOnGotFocus(object Sender, KeyboardFocusChangedEventArgs Args)
        {
            MStrOriginal=MTxtboxCurrent.Text;
        }
//-------------------------------------------------------------------------------------------------------
        private void TextBoxOnLostFocus(object Sender, KeyboardFocusChangedEventArgs Args)
        {
            int				Current;

            if (int.TryParse(MTxtboxCurrent.Text, out Current))
			{
                if (Current>0 && Current<=MColl.Count)
                    MCollview.MoveCurrentToPosition(Current-1);
			}
            else
                MTxtboxCurrent.Text=MStrOriginal;
        }
//-------------------------------------------------------------------------------------------------------
        private void TextBoxOnKeyDown(object Sender, KeyEventArgs Args)
        {
            if (Args.Key==Key.Escape)
            {
                MTxtboxCurrent.Text=MStrOriginal;
                Args.Handled=true;
            }
            else if (Args.Key==Key.Enter)
            {
                Args.Handled=true;
            }
            else
                return;

            MoveFocus(new TraversalRequest(FocusNavigationDirection.Right));
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------