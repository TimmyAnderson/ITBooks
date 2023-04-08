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
	public partial class PrintFlowDocumentWithHeader:Window
	{
//------------------------------------------------------------------------
		public PrintFlowDocumentWithHeader()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Metoda pomocou impementacie CUSTOM PAGINATOR (CHeaderedFlowDocumentPaginator) prida Header do textu.
		// !!! pridanim Header sa NEMENI Page SIZE.
        private void CmdPrint_Click(object Sender, RoutedEventArgs E)
        {
            PrintDialog			PD=new PrintDialog();

            if (PD.ShowDialog()==true)
            {
                // Ulozim povodne nastavenie Page.
                double			PageHeight=MDocReader.Document.PageHeight;
                double			PageWidth=MDocReader.Document.PageWidth;
                Thickness		PagePadding=MDocReader.Document.PagePadding;
                double			ColumnGap=MDocReader.Document.ColumnGap;
                double			ColumnWidth=MDocReader.Document.ColumnWidth;

                // Nsatvim velkost Page na velkost papiera.
                MDocReader.Document.PageHeight=PD.PrintableAreaHeight;
                MDocReader.Document.PageWidth=PD.PrintableAreaWidth;
                MDocReader.Document.PagePadding=new Thickness(50);

                // Use two columns.
                MDocReader.Document.ColumnGap=25;
                MDocReader.Document.ColumnWidth=(MDocReader.Document.PageWidth-MDocReader.Document.ColumnGap-MDocReader.Document.PagePadding.Left-MDocReader.Document.PagePadding.Right)/2;

				// !!! Kedze zmena FlowDocument je mozne IBA KED NIE JE ZOBRAZENY, docasne HO VYHODIM Z CONTAINER.
                FlowDocument	Document=MDocReader.Document;

                MDocReader.Document=null;
                
                CHeaderedFlowDocumentPaginator	Paginator=new CHeaderedFlowDocumentPaginator(Document);

				// Vytlacim document.
                PD.PrintDocument(Paginator, "A Flow Document");

				// Znovu zobrazim document.
                MDocReader.Document=Document;

                // Vratim povodne hodnoty Page.
                MDocReader.Document.PageHeight=PageHeight;
                MDocReader.Document.PageWidth=PageWidth;
                MDocReader.Document.PagePadding=PagePadding;
                MDocReader.Document.ColumnGap=ColumnGap;
                MDocReader.Document.ColumnWidth=ColumnWidth;
            }
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------