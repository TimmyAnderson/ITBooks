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
// 1. Program demonsturje rozlicne moznosti prehravania zvuku.
// 2. Najjednoduchsim sposobom ako prehrat zvuk je pouzit SoundPlayer. Ten umoznuje prehravat zvuk dvoma sposobmi.
//    A. SoundLocation - obsahuje URI na SUBOR, kde je ulzeny WAV subor.
//    B. Stream - umoznuje prehravat WAV zo Stremu. NEVYHODOU JE, ze STREAM SA PRED PREHRAVANIM MUSI NACITAT CELY A PRETO REAL-TIME STREAMING NIE JE MOZNY.
// 3. SoundPlayerAction je akysi wrapper okolo SoundPlayer, ktory pomocou XAML Trigger umoznuje prehrat zvuk.
// !!! 4. MediaPlayer je trieda umoznujuca daleko pohodlnejsie prehravanie ako videa tak aj audia. Umoznuje prehravat rozlicne formaty a ma mnozstvo properties, ktorym je mozne prehravanie ovladat. Podmienkou je mat Windows Media Player aspon vo verzii 10.
// !!!!! 5. Kedze MediaPlayer VZDY PREHRAVA ASYNCHRONNE MUSIM SI DRZAT JEJ REFERENCIU AZ DO KOCNA PREHRAVANIA, CO ZNACI, VYTVORIT JU AKO MEMBER PREMENNU A NIE LOKALNU LOKALNU PRMENNU, ktora by MOHLA SKONCI V GC.
// !!! 6. MediaPlayer NEHADZE EXCEPTION a SAM SI MUSIM KONTROLOVAT ZISTEIM STAVU CI DOCHADZA K PREHRAVANIU.
// !!! 7. Do MediaPlayer MUSIM VZDY ZADAT URI a TO NEPODPORUJE PACKED SYNTAX, takze nemoze pouzit DATA Z RESOURCES.
// 8. Trieda MediaElement wrapruje MediaElement a poskytuje lepsiu moznost riadenia prehravania zvuku a videa. Oproti MediaElement ma tieto vyhody.
//    A. Dokaze prehravat aj VIDEO.
//    B. Spolu s triedou MediaTimeline dokazem prehravat aj cisto v XAML.
//    C. Aj ked jednotlive volania metod NEHADZU PRIAMO EXCEPTION, tieto je mozne zachytavat pomocou eventu MediaFailed.
// 9. Prehravat viacero zvukovych suborov NARAZ je mozne, ale IBA VTEDY ak bude KAZDY ZVUK PREHRAVANY OSOBITNYM OBJEKTOM MediaPlayer (MediaElement).
// 10. Vyuzitim KeyFrame animacie mozem synchronizovat prehravnie zvuku a inych animacii. Pri tejto sycnhronizacii je dolezite nastavit Storyboard.SlipBehavior na Slip, aby pri bufferovani audia ci videa nedoslo k chybe synchronizacie.
//------------------------------------------------------------------------
namespace WavPlayerTest
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
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			SoundPlayerTest				Win=new SoundPlayerTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			MediaElementTest			Win=new MediaElementTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click3(object Sender, RoutedEventArgs E)
		{
			MediaTimelineTest			Win=new MediaTimelineTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click4(object Sender, RoutedEventArgs E)
		{
			MultipleSounds				Win=new MultipleSounds();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click5(object Sender, RoutedEventArgs E)
		{
			SynchronizedAnimation		Win=new SynchronizedAnimation();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------