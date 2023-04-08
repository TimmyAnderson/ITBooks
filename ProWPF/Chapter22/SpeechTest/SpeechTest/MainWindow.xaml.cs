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
// 1. Program demonstruje tvorbu hlasu a jeho rekognifikaciu.
// 2. Na vytvorenie hlasu sluzi SpeechSynthesizer. Text, ktory ma povedat sa zadava pomocou objektu PromptBuilder, kde metodou AppendText() zadefinujem text a zaroven Speech effect (rychlost, hlasitost), ktory chcem pre dany text pouzit.
// 3. Ked chcem kombinovat viacero Speech effects musim pouzit PromptStyle.
// 4. Objekt SpeechRecognizer sluzi na rekognifikaciu hlasu.
// 5. Obsahuje viacero events, ktore su volane ked sa rec identifikuje, alebo nie. Event SpeechRecognized je volany ked sa identifikuje slovo.
// !!! 6. Kedze SpeechRecognizer je wrapper COM objektu, je nutne ho deklarovae ako member premennu triedy aby ho GC neznicil a samozrejme ho uvolnit ked sa window zatvara.
// !!! 7. AK CHCEM REKOGNIFIKOVAT IBA MALE MNOZSTVO SLOV MOZEM DEFINOVAT GRAMATIKU. A to bude pomocou objektu Gramar - ktory ju nacita zo specialneho XML suboru, alebo stanovenim v kode pomocou objektu GrammarBuilder. Je mozne stanovit aj kombinacie pripustnych slov.
//------------------------------------------------------------------------
namespace SpeechTest
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
			SpeechSimpleTest		Win=new SpeechSimpleTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			SpeechRecognition		Win=new SpeechRecognition();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------