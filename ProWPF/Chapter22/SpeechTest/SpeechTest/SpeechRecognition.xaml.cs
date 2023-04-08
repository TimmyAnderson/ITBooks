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
using System.Speech.Recognition;
//------------------------------------------------------------------------
namespace SpeechTest
{
//------------------------------------------------------------------------
	public partial class SpeechRecognition:Window
	{
//------------------------------------------------------------------------
		// Kedze SpeechRecognizer je wrapper COM objektu, je nutne ho deklarovae ako member premennu triedy aby ho GC neznicil a samozrejme ho uvolnit ked sa window zatvara.
        private SpeechRecognizer		MRecognizer=new SpeechRecognizer();
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public SpeechRecognition()
		{
			InitializeComponent();

            GrammarBuilder			Grammar=new GrammarBuilder();

            Grammar.Append(new Choices("red", "blue", "green", "black", "white"));
            Grammar.Append(new Choices("on", "off"));
            
            MRecognizer.LoadGrammar(new Grammar(Grammar));

            MRecognizer.SpeechDetected+=Recognizer_SpeechDetected;            
            MRecognizer.SpeechRecognized+=Recognizer_SpeechReconized;
            MRecognizer.SpeechRecognitionRejected+=Recognizer_SpeechRejected;
            MRecognizer.SpeechHypothesized+=Recognizer_SpeechHypothesized;
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void Recognizer_SpeechReconized(object Sender, SpeechRecognizedEventArgs E)
        {
            MLabel.Content=string.Format("You said: {0} !", E.Result.Text);
        }
//------------------------------------------------------------------------
        private void Recognizer_SpeechDetected(object Sender, SpeechDetectedEventArgs E)
        {
            MLabel.Content="Speech detected.";
        }
//------------------------------------------------------------------------
        private void Recognizer_SpeechHypothesized(object Sender, SpeechHypothesizedEventArgs E)
        {
            MLabel.Content="Speech uncertain.";
        }
//------------------------------------------------------------------------
        private void Recognizer_SpeechRejected(object Sender, SpeechRecognitionRejectedEventArgs E)
        {
            MLabel.Content="Speech rejected.";
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        protected override void OnClosed(EventArgs E)
        {
            MRecognizer.Dispose();
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------