using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace WavPlayerTest
{
//------------------------------------------------------------------------
	// !!!!! NATO ABY TO PREHRAVALO MUSIM MAT V OUTPUT VYTVORENY ADRESAR Sounds A V NOM SUBOR Test.mp3.
	public partial class MediaElementTest:Window
	{
//------------------------------------------------------------------------
		public MediaElementTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void SliderSpeed_ValueChanged(object Sender, RoutedEventArgs E)
        {
             MMedia.SpeedRatio=((Slider) Sender).Value;
        }
//------------------------------------------------------------------------
        private void CmdPlay_Click(object Sender, RoutedEventArgs E)
        {
            MMedia.Play();
        }
//------------------------------------------------------------------------
        private void CmdPause_Click(object Sender, RoutedEventArgs E)
        {
            MMedia.Pause();
        }
//------------------------------------------------------------------------
        private void CmdStop_Click(object Sender, RoutedEventArgs E)
        {            
            MMedia.Stop();
            MMedia.SpeedRatio=1;
        }
//------------------------------------------------------------------------
        private void Media_MediaOpened(object Sender, RoutedEventArgs E)
        {
            MSliderPosition.Maximum=MMedia.NaturalDuration.TimeSpan.TotalSeconds;
        }
//------------------------------------------------------------------------
        private void SliderPosition_ValueChanged(object Sender, RoutedEventArgs E)
        {
            MMedia.Pause();
            MMedia.Position=TimeSpan.FromSeconds(MSliderPosition.Value);
            MMedia.Play();
        }
//------------------------------------------------------------------------
		private void MMedia_MediaFailed(object Sender, ExceptionRoutedEventArgs E)
		{
			MessageBox.Show(E.ErrorException.ToString());
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------