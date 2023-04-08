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
//------------------------------------------------------------------------
// 1. Program demonstruje jednouchu aplikaciu s niekolkymi zakladnymi Elements.
// 2. V XAML je mozne vidiet, ze zadavame Elementy ako text a preto existuju Converters, bud aplikovane na property, alebo cielovy typ property, ktore su schopne vytvorit z textu XAML objekt danje triedy.
//------------------------------------------------------------------------
namespace EightBall
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdAnswer_Click(object Sender, RoutedEventArgs E)
        {           
            // Dramatic delay...
            this.Cursor=Cursors.Wait;
            System.Threading.Thread.Sleep(TimeSpan.FromSeconds(1));

            AnswerGenerator			Generator=new AnswerGenerator();

            MTXTAnswer.Text=Generator.GetRandomAnswer(MTXTQuestion.Text);
            this.Cursor=null;
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------