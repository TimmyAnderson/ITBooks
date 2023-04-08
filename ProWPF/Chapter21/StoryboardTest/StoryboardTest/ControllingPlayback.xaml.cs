using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Media.Animation;
//------------------------------------------------------------------------
namespace StoryboardTest
{
//------------------------------------------------------------------------
	public partial class ControllingPlayback:System.Windows.Window
	{
//------------------------------------------------------------------------
		public ControllingPlayback()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Vyvola sa ked sa cas animacie posunie dopredu.
		// !!! Vtedy rendereujem poziciu animacie v ProgressBar.
		// !!! Standardne pokial nie je kod pomaly tak sa vola 60 KRAT ZA SEKUNDU.
        private void Storyboard_CurrentTimeInvalidated(object Sender, EventArgs E)
        {            
            // Sender obsahuje instanciu triedy Clock zodpovednej za realizovanie animacie.
            Clock			StoryboardClock=(Clock) Sender;
                
			// CurrentProgress bude obsahuje NULL, alebo hodnotu z intevralu <0,1>.
            if (StoryboardClock.CurrentProgress==null)
            {
                MLblTime.Text="[[ stopped ]]";
                MProgressBar.Value=0;
            }
            else
            {
                MLblTime.Text=StoryboardClock.CurrentTime.ToString();
                MProgressBar.Value=(double) StoryboardClock.CurrentProgress;
            }
        }
//------------------------------------------------------------------------
        private void SldSpeed_ValueChanged(object Sender, RoutedEventArgs E)
        {
            MFadeStoryboard.SetSpeedRatio(this, MSldSpeed.Value);
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------