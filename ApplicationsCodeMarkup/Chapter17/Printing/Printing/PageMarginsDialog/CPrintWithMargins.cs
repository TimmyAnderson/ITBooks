using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Printing;
//------------------------------------------------------------------------------
namespace Printing
{
//------------------------------------------------------------------------------
	public class CPrintWithMargins : Window
	{
//------------------------------------------------------------------------------
        private PrintQueue										MPrnQueue;
        private PrintTicket										MPrnTkt;
        private Thickness										MMarginPage=new Thickness(96);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CPrintWithMargins()
        {
            Title="Print with Margins";
            FontSize=24;

            StackPanel			Stack=new StackPanel();

            Content=Stack;

            Button				Btn = new Button();

            Btn.Content="Page Set_up...";
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.Margin=new Thickness(24);
            Btn.Click+=SetupOnClick;
            Stack.Children.Add(Btn);

            Btn=new Button();
            Btn.Content="_Print...";
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Btn.Margin=new Thickness(24);
            Btn.Click+=PrintOnClick;
            Stack.Children.Add(Btn);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void SetupOnClick(object Sender, RoutedEventArgs Args)
        {
            CPageMarginsDialog			Dlg=new CPageMarginsDialog();

            Dlg.Owner=this;
            Dlg.PageMargins=MMarginPage;

            if (Dlg.ShowDialog().GetValueOrDefault())
            {
                // Save page margins from dialog box.
                MMarginPage = Dlg.PageMargins;
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void PrintOnClick(object Sender, RoutedEventArgs Args)
        {
            PrintDialog				Dlg=new PrintDialog();

            if (MPrnQueue!=null)
                Dlg.PrintQueue=MPrnQueue;

            if (MPrnTkt!=null)
                Dlg.PrintTicket=MPrnTkt;

            if (Dlg.ShowDialog().GetValueOrDefault()==true)
            {
                MPrnQueue=Dlg.PrintQueue;
                MPrnTkt=Dlg.PrintTicket;

                DrawingVisual		LVisual=new DrawingVisual();
                DrawingContext		DC=LVisual.RenderOpen();
				Pen					LPen=new Pen(Brushes.Black, 1);
                Rect				RectPage=new Rect(MMarginPage.Left, MMarginPage.Top, Dlg.PrintableAreaWidth-(MMarginPage.Left+MMarginPage.Right), Dlg.PrintableAreaHeight-(MMarginPage.Top+MMarginPage.Bottom));

                DC.DrawRectangle(null, LPen, RectPage);

                FormattedText		Formtxt=new FormattedText(string.Format("Hello, Printer [{0}] x [{1}] !", Dlg.PrintableAreaWidth / 96, Dlg.PrintableAreaHeight / 96),CultureInfo.CurrentCulture,FlowDirection.LeftToRight,new Typeface(new FontFamily("Times New Roman"), FontStyles.Italic, FontWeights.Normal, FontStretches.Normal), 48, Brushes.Black);
                Size				SizeText=new Size(Formtxt.Width, Formtxt.Height);
                Point				PtText=new Point(RectPage.Left+(RectPage.Width-Formtxt.Width)/2,RectPage.Top+(RectPage.Height-Formtxt.Height)/2);

                DC.DrawText(Formtxt, PtText);
                DC.DrawRectangle(null, LPen, new Rect(PtText, SizeText));

                DC.Close();

                Dlg.PrintVisual(LVisual, Title);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------