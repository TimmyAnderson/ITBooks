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
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje prehravanie videa.
// 2. Na prehravanie videa sa pouziva komponenta MediaElement, pre ktoru palti vsetko to co plati pri prehravani audia.
// !!! 3. Rozdiel medzi prehravani videa a audia je v tom, ze pri videu je UMIESTNENIE MediaElement a velkost. Dosleiza je property Stretch, StretchDirection urcujuce aka bude velkost MediaElement pri prehravani videa.
// !!! 4. Pri prehravanie videa cez MediaElement, kdeze ten JE ELEMENT tak je mozne robit na nom LUBOVOLNE TRANSFORMACIE AKO NA KAZDOM INOM ELEMENTE.
// !!! 5. Na vykreslenie videa na nejaky surface su mozne pouzit tieto dve Elementy.
//    A. VisualBrush - interne pouziva MediaElement a preto je o nieco menej efektivny.
//    B. VideoDrawing - interne pouziva MediaPlayer. Je efektivnejsi, ale na spustenie prehravania je nutny C# kod.
//------------------------------------------------------------------------
namespace VideoPlayerTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			VideoDrawing			Win=new VideoDrawing();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			Video					Win=new Video();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------