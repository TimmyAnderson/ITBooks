using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
//-----------------------------------------------------------------------------------------------------------------
namespace WizardApplication
{
//-----------------------------------------------------------------------------------------------------------------
    public partial class WizardPage2
    {
//-----------------------------------------------------------------------------------------------------------------
        private Vitals											MVitals;
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public WizardPage2(Vitals Vitals)
        {
            InitializeComponent();

            MVitals=Vitals;
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void BrowseButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            DirectoryPage		Page=new DirectoryPage();
			
			// Zaregistrujem EVENT, ktory sa zavola po skonceni PageFunction<Type>.
            Page.Return+=DirPageOnReturn;

			// Skocim na PageFunction<Type>.
            NavigationService.Navigate(Page);
        }
//-----------------------------------------------------------------------------------------------------------------
        private void DirPageOnReturn(object Sender, ReturnEventArgs<DirectoryInfo> Args)
        {
            if (Args.Result!=null)
                MTxtBoxFavoriteDir.Text=Args.Result.FullName;
        }
//-----------------------------------------------------------------------------------------------------------------
        private void PreviousButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            NavigationService.GoBack();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void NextButtonOnClick(object sender, RoutedEventArgs Args)
        {
            MVitals.FavoriteOS=MTxtBoxFavoriteOS.Text;
            MVitals.Directory=MTxtBoxFavoriteDir.Text;

            if (NavigationService.CanGoForward==true)
                NavigationService.GoForward();
            else
            {
                WizardPage3			Page=new WizardPage3(MVitals);

                NavigationService.Navigate(Page);
            }
        }
//-----------------------------------------------------------------------------------------------------------------
    }
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------