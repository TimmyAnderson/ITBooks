using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
//-----------------------------------------------------------------------------------------------------------------
namespace WindowsApplication
{
//-----------------------------------------------------------------------------------------------------------------
	public partial class YellowPadWindow : Window
	{
//-----------------------------------------------------------------------------------------------------------------
        private void HelpOnExecuted(object Sender, ExecutedRoutedEventArgs Args)
        {
            YellowPadHelp		Win=new YellowPadHelp();

            Win.Owner=this;
            Win.Show();
        }
//-----------------------------------------------------------------------------------------------------------------
        private void AboutOnClick(object Sender, RoutedEventArgs Args)
        {
            YellowPadAboutDialog	Dlg=new YellowPadAboutDialog();

            Dlg.Owner=this;
            Dlg.ShowDialog();
        }
//-----------------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------------