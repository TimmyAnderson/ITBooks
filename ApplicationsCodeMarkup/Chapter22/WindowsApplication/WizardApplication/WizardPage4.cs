using System;
using System.Windows;
using System.Windows.Controls;
//-----------------------------------------------------------------------------------------------------------------
namespace WizardApplication
{
//-----------------------------------------------------------------------------------------------------------------
    public partial class WizardPage4: Page
    {
//-----------------------------------------------------------------------------------------------------------------
        public WizardPage4(Vitals Vitals)
        {
            InitializeComponent();

            MRunName.Text=Vitals.Name;
            MRunHome.Text=Vitals.Home;
            MRunGender.Text=Vitals.Gender;
            MRunOS.Text=Vitals.FavoriteOS;
            MRunDirectory.Text=Vitals.Directory;
            MRunMomsMaidenName.Text=Vitals.MomsMaidenName;
            MRunPet.Text=Vitals.Pet;
            MRunIncome.Text=Vitals.Income;
        }
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        private void PreviousButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            NavigationService.GoBack();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void SubmitButtonOnClick(object Sender, RoutedEventArgs Args)
        {
            MessageBox.Show("Thank you!\n\nYou will be contacted by email in four to six months.", Application.Current.MainWindow.Title, MessageBoxButton.OK, MessageBoxImage.Exclamation);
            Application.Current.Shutdown();
        }
//-----------------------------------------------------------------------------------------------------------------
    }
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------