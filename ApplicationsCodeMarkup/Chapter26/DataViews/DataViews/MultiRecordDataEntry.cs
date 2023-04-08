using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Specialized;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	public partial class MultiRecordDataEntry
	{
//-------------------------------------------------------------------------------------------------------
        private People											MPeople;
		// Udava index aktualne zobrazeneho zaznamu People.
        private int												MIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public MultiRecordDataEntry()
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

            InitializeNewPeopleObject();
        }
//-------------------------------------------------------------------------------------------------------
        private void OpenOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            MPeople=People.Load(this);

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
            MIndex=0;

            if (MPeople.Count==0)
                MPeople.Insert(0, new Person());

            MPnlPerson.DataContext=MPeople[0];
            EnableAndDisableButtons();
        }
//-------------------------------------------------------------------------------------------------------
        private void FirstOnClick(object Sender, RoutedEventArgs Args)
        {
            MPnlPerson.DataContext=MPeople[MIndex=0];
            EnableAndDisableButtons();
        }
//-------------------------------------------------------------------------------------------------------
        private void PrevOnClick(object Sender, RoutedEventArgs Args)
        {
            MPnlPerson.DataContext=MPeople[MIndex-=1];
            EnableAndDisableButtons();
        }
//-------------------------------------------------------------------------------------------------------
        private void NextOnClick(object Sender, RoutedEventArgs Args)
        {
            MPnlPerson.DataContext=MPeople[MIndex+=1];
            EnableAndDisableButtons();
        }
//-------------------------------------------------------------------------------------------------------
        private void LastOnClick(object Sender, RoutedEventArgs Args)
        {
            MPnlPerson.DataContext=MPeople[MIndex=(MPeople.Count-1)];
            EnableAndDisableButtons();
        }
//-------------------------------------------------------------------------------------------------------
        private void AddOnClick(object Sender, RoutedEventArgs Args)
        {
            MPeople.Insert(MIndex=MPeople.Count, new Person());

            MPnlPerson.DataContext=MPeople[MIndex];
            EnableAndDisableButtons();
        }
//-------------------------------------------------------------------------------------------------------
        private void DelOnClick(object Sender, RoutedEventArgs Args)
        {
            MPeople.RemoveAt(MIndex);

            if (MPeople.Count==0)
                MPeople.Insert(0,new Person());

            if (MIndex>(MPeople.Count-1))
                MIndex--;
            
            MPnlPerson.DataContext=MPeople[MIndex];
            EnableAndDisableButtons();
        }
//-------------------------------------------------------------------------------------------------------
        private void EnableAndDisableButtons()
        {
            MBtnPrev.IsEnabled=(MIndex!=0);
            MBtnNext.IsEnabled=(MIndex<(MPeople.Count-1));
            MPnlPerson.Children[1].Focus();
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------