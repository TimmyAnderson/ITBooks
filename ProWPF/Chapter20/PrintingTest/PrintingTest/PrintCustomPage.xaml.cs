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
using System.Globalization;
//------------------------------------------------------------------------
namespace PrintingTest
{
//------------------------------------------------------------------------
	public partial class PrintCustomPage:Window
	{
//------------------------------------------------------------------------
		public PrintCustomPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void CmdPrint_Click(object Sender, RoutedEventArgs E)
        {           
            PrintDialog				PD=new PrintDialog();

            if (PD.ShowDialog()==true)
            {
                // Vytvorim Visual objekt pre tlac.
                DrawingVisual		Visual=new DrawingVisual();

                // Get the drawing context
                using (DrawingContext DC=Visual.RenderOpen())
                {
                    // Vyberiem z TextBox text, ktory chcem tlacit.
					// !!! FormattedText umzonuje formatovat KAZDY ZNAK OSOBITNE.
                    FormattedText	Text=new FormattedText(MTxtContent.Text, CultureInfo.CurrentCulture, FlowDirection.LeftToRight, new Typeface("Calibri"), 20, Brushes.Black);

                    // Budem tlacit iba do sitky rovnej polovici papiera.
                    Text.MaxTextWidth=PD.PrintableAreaWidth/2;

                    // Zistim velkost text - FormattedText ho vypocitava AUTOAMTICKY.
                    Size			TextSize=new Size(Text.Width, Text.Height);

                    // Urcit umiestnenie, kde budem text tlacit.
                    double			Margin=96*0.25;                    
                    Point			Point=new Point((PD.PrintableAreaWidth-TextSize.Width)/2-Margin, (PD.PrintableAreaHeight-TextSize.Height)/2-Margin);

                    // Vykreslim Text.
                    DC.DrawText(Text, Point);

                    // Vykreslim border/.
                    DC.DrawRectangle(null, new Pen(Brushes.Black, 1), new Rect(Margin, Margin, PD.PrintableAreaWidth - Margin*2, PD.PrintableAreaHeight-Margin*2));
                }

                // Print the visual.
                PD.PrintVisual(Visual, "A Custom-Printed Page");
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------