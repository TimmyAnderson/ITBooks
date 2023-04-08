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
	public partial class DataEntryWithNavigation
	{
//-------------------------------------------------------------------------------------------------------
        private People											MPeople;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public DataEntryWithNavigation()
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
            MNavbar.Collection=MPeople;
            MNavbar.ItemType=typeof(Person);
            MPnlPerson.DataContext=MPeople;
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------