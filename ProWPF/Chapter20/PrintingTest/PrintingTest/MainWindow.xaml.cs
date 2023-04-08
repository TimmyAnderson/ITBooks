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
using System.Printing;
//------------------------------------------------------------------------
// 1. Prorgam demonstruje Printing pod WPF.
// 2. Printing vo WPF sa najjednoduchsie da urobit vyuzitim PrintDialog.
// 3. PrintDialog podporuje tlac dvoch typov udajov.
//    A. PrintVisual() - umoznuje tlac lubovolneho Visual objektu, teda lubovolneho Elementu.
//    B. PrintDocument() - umoznuje tlac lubovolneho Document a DocumentPaginator objektu.
// !!! 4. Tlac cez PrintVisual() nie je velmi sikovne urobena a prakticky sa neda nijako konfigurovat, ci tlacit na pozadi. Okrem toho vytlaceny Element je casto maly na papieri.
// !!! 5. Dalsou nevyhodou PrintDialog je ze JE VZDY MODALNE voci MAIN WINDOW. NEDA SA TO ZMENIT. Dokonca aj ked vo vyvolam z ineho okna tka voci tomuto oknu SA NEBUDE CHOVAT MODALNE. Iba voci MainWindow. Vyplyva to z internej implementacie.
// !!!!! 6. Velkost okna je mozne ziskat z properties PrintDialogs: PrintableAreaWidth a PrintableAreaHeight.
// !!! 7. Jednym zo sposobov ako obist problem, ze pri tlaci Elementu ho nemozem zvecsit, ani posunut, je pouzit LayoutTransformation. Problem je vsak, ze WPF zoberie tu LayoutTransformation, ktoru som nastavil pri zobrazeni Elementu na obrazovku - takze NULL. Aby som problem obisiel tak musim TESNE PRED TLACOU zvecsit velkost Elementu a potom ho zasa zmensit. Aby to nebolo vidiet tak docastne skryjem Parent Element - iba pocas tlace, aby ho nebolo vidiet zvecseny. Element, ktory tlacim nemozem skryt, inak by sa nevytlacil, ale parent Element ano.
// 8. Pri tlaci FlowDocuments pouzivam metodu PrintDocument(). Tato metoda ma ako parameter IDocumentPaginatorSource, ktory implementuje FlowDocument.
// !!! 9. Interface IDocumentPaginatorSource rozdeluje FlowDocument na stranky. V zavislosti od typu kontajnera vykonava toto delenie. V pripade FlowDocumentScrollViewer ho rozdeli korektne podla velkosti papiera. Avsak v pripade FlowDocumentPageViewer a FlowDocumentReader ich deli podla definovanych stranok. Ak chcem aby teito stranky boli zhodne s velkostou papiera musim nastavit PageHeight a PageWidth na velkost PrintDialog.
// !!! 10. Ak do metody PrintDocument() podhodim AnnotationDocumentPaginator potom mozem tlacit aj anotacie.
// !!! 11. Ak chcem napriklad do kazdej stranky prihodit vlastny Header, alebo Footer jednym z rieseni je vytvorit vlastny DocumentPaginator, ktory bude wraprovat existujuci a jedina zmena bude, ze v metode GetPage(), ktora je volana ked je Paginator poziadany o vratenie stranky dohodi Header, alebo Footer. Zmytok vypoctov, vratanie rozdelenia FlowDocument na Pages je na vnorenom Paginator objekte.
// 12. Ak chcem realizovat CUSTOM tlac, teda taku, kde vsetok Content vykrsluje rucne potom musim pouzit DrawingVisual triedu, ktoru vykreslim Content a do metody PrintVisual() poslat tento objekt.
// !!!!! 13. Ak chcem realizovat CUSTOM tlac na viacerych strankach, tak musim IMPLEMENTOVAT CUSTOM PAGINATOR objekt, ktory MANUALNE rozdeli Content do Pages a a pre kazdy Page vytvori PageDocument objekt, ktory potom poskytne pri volani metody GetPage() objektu PAGINATOR.
// 13. Vdaka triedam PrintServer, LocalPrintServer, PrintQueue a PrintSystemJobInfo je mozne sledovat a riadit PrintQueues, a PrintJobs. Pomocou PrintServer je mozne sa pripojit aj na vzdialeny Print Server a riadit jeho Jobs - ak mam opravnenie.
// !!! 14. Ak chcem zachovat nastavenie PrintDialog aj medzi zobrazeniami PrintDialog potom musim si uchovat hodnoty je properties PrintQueue a PrintTicket medzi 2 zobrazniami PrintDialogu.
// !!!!! 15. Tlac vo WPF sa na pozadi vykonava cez XPS format. TEda ako FixedDocument. Zvycajne to nie je vidiet, pretoze sa pouziva na pozadi. Avsak niekey je dobre realizovat praimy pristup a XPS VYTVORIT AUTOMATICKY POMOCOU XpsDocumentWriter a to napriklad pre vytvorenie Preview, alebo ASYNCHRONNOM PRINTINGU.
//------------------------------------------------------------------------
namespace PrintingTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		private PrintQueue				MPrintQueue;
		private PrintTicket				MPrintTicket;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
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
			ElementPrint			Win=new ElementPrint();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			PrintDialog				PD=new PrintDialog();

			if (PD.ShowDialog()==true)
			{
				// Create the text.
				Run					Run=new Run("This is a test of the printing functionality in the Windows Presentation Foundation.");

				// Wrap it in a TextBlock.
				TextBlock			Visual=new TextBlock();

				Visual.Inlines.Add(Run);

				// Use margin to get a page border.
				Visual.Margin=new Thickness(15);

				// Allow wrapping to fit the page width.
				Visual.TextWrapping=TextWrapping.Wrap;

				// Scale the TextBlock up in both dimensions by a factor of 5.
				// (In this case, increasing the font would have the same effect, because the TextBlock is the only element.)
				Visual.LayoutTransform=new ScaleTransform(5, 5);

				// Size the element.
				Size				PageSize=new Size(PD.PrintableAreaWidth, PD.PrintableAreaHeight);

				Visual.Measure(PageSize);
				Visual.Arrange(new Rect(0,0, PageSize.Width, PageSize.Height));

				// Print the element.
				PD.PrintVisual(Visual, "A Scaled Drawing");
			}
		}
//------------------------------------------------------------------------
		private void Button_Click3(object Sender, RoutedEventArgs E)
		{
			PrintFlowDocument		Win=new PrintFlowDocument();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click4(object Sender, RoutedEventArgs E)
		{
			PrintFlowDocumentWithHeader	Win=new PrintFlowDocumentWithHeader();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click5(object Sender, RoutedEventArgs E)
		{
			PrintCustomPage			Win=new PrintCustomPage();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click6(object Sender, RoutedEventArgs E)
		{
			PrintCustomPages		Win=new PrintCustomPages();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click7(object Sender, RoutedEventArgs E)
		{
			PrintQueues				Win=new PrintQueues();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click8(object Sender, RoutedEventArgs E)
		{
			PrintDialog				PD=new PrintDialog();

			if (MPrintQueue!=null)
			{
				PD.PrintQueue=MPrintQueue;
				PD.PrintTicket=MPrintTicket;
			}

			PD.ShowDialog();

			MPrintQueue=PD.PrintQueue;
			MPrintTicket=PD.PrintTicket;
		}
//------------------------------------------------------------------------
		private void Button_Click9(object Sender, RoutedEventArgs E)
		{
			Xps						Win=new Xps();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------