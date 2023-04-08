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
using System.Speech.Synthesis;
//------------------------------------------------------------------------
namespace SpeechTest
{
//------------------------------------------------------------------------
	public partial class SpeechSimpleTest:Window
	{
//------------------------------------------------------------------------
		public SpeechSimpleTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdSpeak_Click(object Sender, RoutedEventArgs E)
        {
            SpeechSynthesizer		Synthesizer=new SpeechSynthesizer();

            Synthesizer.Speak(MTXTWords.Text);
        }
//------------------------------------------------------------------------
        private void CmdPromptTest_Click(object Sender, RoutedEventArgs E)
        {
            PromptBuilder			Prompt=new PromptBuilder();
            
            Prompt.AppendText("How are you");            
            Prompt.AppendBreak(TimeSpan.FromSeconds(2));
            Prompt.AppendText("How ", PromptEmphasis.Reduced);

			// Ked chcem kombinovat viacero Speech effects musim pouzit PromptStyle.
            PromptStyle				Style = new PromptStyle();

            Style.Rate=PromptRate.ExtraSlow;
            Style.Emphasis=PromptEmphasis.Strong;
            Prompt.StartStyle(Style);
            Prompt.AppendText("are ");
            Prompt.EndStyle();            
            Prompt.AppendText("you?");          
            
            SpeechSynthesizer		Synthesizer=new SpeechSynthesizer();

            Synthesizer.Speak(Prompt);
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------