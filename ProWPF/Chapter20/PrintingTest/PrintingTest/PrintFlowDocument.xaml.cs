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
namespace PrintingTest
{
//------------------------------------------------------------------------
	public partial class PrintFlowDocument:Window
	{
//------------------------------------------------------------------------
		public PrintFlowDocument()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Vytlacim FlowDocument bez prisposobenia Page velkosti papiera.
        private void CmdPrint_Click(object Sender, RoutedEventArgs E)
        {
            PrintDialog			PD=new PrintDialog();

            if (PD.ShowDialog()==true)
            {                
                PD.PrintDocument(((IDocumentPaginatorSource) MDocReader.Document).DocumentPaginator, "A Flow Document");
            }
        }
//------------------------------------------------------------------------
		// !!! Vytlacim FlowDocument bez prisposobenia Page velkosti papiera.
        private void CmdPrintCustom_Click(object Sender, RoutedEventArgs E)
        {
            PrintDialog			PD=new PrintDialog();

            if (PD.ShowDialog() == true)
            {
                FlowDocument	Doc=MDocReader.Document;
                
				// !!! Idem prisposobit velkost Page FlowDocument velkosti Papiera.

                // Ulozim si povodnu velkost Page.
                double			PageHeight=Doc.PageHeight;
                double			PageWidth=Doc.PageWidth;
                Thickness		PagePadding=Doc.PagePadding;
                double			ColumnGap=Doc.ColumnGap;
                double			ColumnWidth=Doc.ColumnWidth;

                // Nastavim aby velkost Page FlowDoument bola taka ista ako velkost papiera.
                Doc.PageHeight=PD.PrintableAreaHeight;
                Doc.PageWidth=PD.PrintableAreaWidth;
                Doc.PagePadding=new Thickness(50);

                // Pouzijem 2 stlpce.
                Doc.ColumnGap=25;
                Doc.ColumnWidth=(Doc.PageWidth-Doc.ColumnGap-Doc.PagePadding.Left-Doc.PagePadding.Right)/2;

				// Uskutocnim tlac.
                PD.PrintDocument(((IDocumentPaginatorSource)Doc).DocumentPaginator, "A Flow Document");
                
                // Vratim vekost Page FlowDocument na povodnu velkost.
                Doc.PageHeight=PageHeight;
                Doc.PageWidth=PageWidth;
                Doc.PagePadding=PagePadding;
                Doc.ColumnGap=ColumnGap;
                Doc.ColumnWidth=ColumnWidth;
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------