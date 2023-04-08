using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Printing;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Printing
{
//------------------------------------------------------------------------------
	public class CPrintBanner : Window
	{
//------------------------------------------------------------------------------
        private TextBox											MTxtBox;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public CPrintBanner()
        {
            Title="Print Banner";
            SizeToContent=SizeToContent.WidthAndHeight;

            StackPanel				Stack=new StackPanel();

            Content=Stack;

            MTxtBox=new TextBox();
            MTxtBox.Width=250;
            MTxtBox.Margin=new Thickness(12);
            Stack.Children.Add(MTxtBox);

            Button					Btn=new Button();

            Btn.Content="_Print...";
            Btn.Margin=new Thickness(12);
            Btn.Click+=PrintOnClick;
            Btn.HorizontalAlignment=HorizontalAlignment.Center;
            Stack.Children.Add(Btn);

            MTxtBox.Focus();
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private void PrintOnClick(object Sender, RoutedEventArgs Args)
        {
            PrintDialog						Dlg=new PrintDialog();

            if (Dlg.ShowDialog().GetValueOrDefault()==true)
            {
                PrintTicket					MPrnTkt=Dlg.PrintTicket;

                MPrnTkt.PageOrientation=PageOrientation.Portrait;
                Dlg.PrintTicket=MPrnTkt;

				// Vytvorim objekt typu DocumentPaginator.
				CBannerDocumentPaginator	Paginator=new CBannerDocumentPaginator();

                Paginator.Text=MTxtBox.Text;

                Paginator.PageSize=new Size(Dlg.PrintableAreaWidth, Dlg.PrintableAreaHeight);

                // Vytlacim dokument, pricom ako parameter dam DocumentPaginator.
                Dlg.PrintDocument(Paginator, "Banner: " + MTxtBox.Text);
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------