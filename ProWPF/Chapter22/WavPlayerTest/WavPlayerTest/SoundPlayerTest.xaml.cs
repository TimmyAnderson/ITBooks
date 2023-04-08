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
using System.Media;
using System.ComponentModel;
using System.IO;
//------------------------------------------------------------------------
namespace WavPlayerTest
{
//------------------------------------------------------------------------
	public partial class SoundPlayerTest:Window
	{
//------------------------------------------------------------------------
		// Kedze MediaPlayer VZDY PREHRAVA ASYNCHRONNE MUSIM SI DRZAT JEJ REFERENCIU AZ DO KOCNA PREHRAVANIA, CO ZNACI, VYTVORIT JU AKO MEMBER PREMENNU A NIE LOKALNU LOKALNU PRMENNU, ktora by MOHLA SKONCI V GC.
        private MediaPlayer					MPlayer=new MediaPlayer();
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public SoundPlayerTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Pouzivam SoundPlayer na SYNCHRONNE prehravanie.
        private void CmdPlayAudio_Click(object sender, RoutedEventArgs e)
        {
            SoundPlayer				Player=new SoundPlayer();

			// !!! Subor Chimes je ulozeny v Resources.resx.
            Player.Stream=Properties.Resources.Chimes;

            try
            {
                Player.Load();
                Player.PlaySync();
            }
            catch (System.IO.FileNotFoundException Err)
            {
				MessageBox.Show(string.Format("ERROR: {0} !",Err.Message));
            }
            catch (FormatException Err)
            {
				MessageBox.Show(string.Format("ERROR: {0} !",Err.Message));
            }
        }
//------------------------------------------------------------------------
		// Pouzivam SoundPlayer na ASYNCHRONNE prehravanie.
        private void CmdPlayAudioAsync_Click(object sender, RoutedEventArgs e)
        {
            SoundPlayer				Player=new SoundPlayer();

            Player.SoundLocation="..\\..\\Sounds\\Test.wav";

            try
            {
                Player.Load();
                Player.Play();
            }
            catch (System.IO.FileNotFoundException Err)
            {
				MessageBox.Show(string.Format("ERROR: {0} !",Err.Message));
            }
            catch (FormatException Err)
            {
				MessageBox.Show(string.Format("ERROR: {0} !",Err.Message));
            }
        }
//------------------------------------------------------------------------
		// !!! Pouzivam MediaPlayer na prehratie MP3.
        private void CmdPlayWithMediaPlayer_Click(object Sender, RoutedEventArgs E)
        {            
			// Kedze MediaPlayer VZDY PREHRAVA ASYNCHRONNE MUSIM SI DRZAT JEJ REFERENCIU AZ DO KOCNA PREHRAVANIA, CO ZNACI, VYTVORIT JU AKO MEMBER PREMENNU A NIE LOKALNU LOKALNU PRMENNU, ktora by MOHLA SKONCI V GC.
            MPlayer.Open(new Uri("..\\..\\Sounds\\Test.mp3", UriKind.Relative));
            MPlayer.Play();
        }
//------------------------------------------------------------------------
        private void Window_Closed(object Sender, EventArgs E)
        {
			// Pri uzatvoreni okna musim uzavriet Player.
            MPlayer.Close();
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------