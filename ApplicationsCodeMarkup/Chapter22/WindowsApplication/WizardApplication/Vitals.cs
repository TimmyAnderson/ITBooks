using System;
using System.Windows;
using System.Windows.Controls;
//-----------------------------------------------------------------------------------------------------------------
namespace WizardApplication
{
//-----------------------------------------------------------------------------------------------------------------
    public class Vitals
    {
//-----------------------------------------------------------------------------------------------------------------
		// !!! Definujem si properties, ktore budu DRZAT STAV WIZARDU.
        public string											Name;
        public string											Home;
        public string											Gender;
        public string											FavoriteOS;
        public string											Directory;
        public string											MomsMaidenName;
        public string											Pet;
        public string											Income;
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
        public static RadioButton GetCheckedRadioButton(GroupBox GrpBox)
        {
            Panel					LPanel=GrpBox.Content as Panel;

            if (LPanel!=null)
            {
                foreach (UIElement El in LPanel.Children)
                {
                    RadioButton		LRadio=El as RadioButton;

                    if (LRadio!=null && ((bool)LRadio.IsChecked)==true)
                        return(LRadio);
                }
            }

            return(null);
        }
//-----------------------------------------------------------------------------------------------------------------
    }
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------