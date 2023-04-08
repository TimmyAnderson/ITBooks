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
namespace WavPlayerTest
{
//------------------------------------------------------------------------
	public partial class SynchronizedAnimation:Window
	{
//------------------------------------------------------------------------
        private bool					MSuppressSeek;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public SynchronizedAnimation()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void SliderPosition_ValueChanged(object Sender, RoutedEventArgs E)
        {
            if (MSuppressSeek==false)
                MMediaStoryboard.Storyboard.Seek(MDocumentRoot, TimeSpan.FromSeconds(MSliderPosition.Value), TimeSeekOrigin.BeginTime);
        }
//------------------------------------------------------------------------
        private void Media_MediaOpened(object Sender, RoutedEventArgs E)
        {
            MSliderPosition.Maximum=MMedia.NaturalDuration.TimeSpan.TotalSeconds;
        }
//------------------------------------------------------------------------
        private void Storyboard_CurrentTimeInvalidated(object Sender, EventArgs E)
        {
            // Sender is the clock that was created for this storyboard.
            Clock			StoryboardClock=(Clock) Sender;

            if (StoryboardClock.CurrentProgress==null)
            {
                MLBLTime.Text="[[ stopped ]]";                   
            }
            else
            {
                MLBLTime.Text=string.Format("Position: {0} !",StoryboardClock.CurrentTime.ToString());
                MSuppressSeek=true;
                MSliderPosition.Value=StoryboardClock.CurrentTime.Value.TotalSeconds;
                MSuppressSeek=false;
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------