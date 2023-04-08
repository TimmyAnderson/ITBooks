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
// 1. Program demonstruje pouzitie FlowDocument.
// 2. FlowDocument sluzi na definovanie FORMATOVANEHO TEXTU, ktory je mozne elegantne zoomovat, zarovnavat a tak podobne.
// 3. Sklada sa z objektu FlowDocument, do ktoreho vkladam jednotlive Blocks, alebo Inlines objekty a tak vytvaram dobre formatovany dokument.
// 4. FlowDocument mozem obalit do FlowDocumentScrollViewer a tym docielit, ze FlowDocument bude scrolovatelny.
// 5. Paragraph (Block Element) moze obsahovat kolekciu Inlines objektov. Ak tam dam iba text, tak ho obali objektom Run. Ma mnozstvo properties, ktorym mozem formatovat Paragraph.
// 6. List (Block Element) umoznuje definovat bulleted list, teda zoznam z odrazkami. Property TextMarkerStyle obsahuje typ odrazky. List bud obsahovat Block Element, napriklad Paragraph.
// 7. Table (Block Element) umoznuje formatovat text do tabuliek podobnych tabulkam v HTML. Pouzitie Table je nasledovne.
//    A. TableRowGroup - vkladam ich do Table a do nej vlozit riadky. Vyhoda je, ze naraz viacero riadkom mozem formatovat pomocou tohto objektu ROVNAKO.
//    B. TableRow - vkladam ich TableRowGroup a definujem v nom riadok.
//    C. TableCell - vkladam do TableRow a tym definujem bunky tabulky v danom riadku.
//    D. Block - vkladam ho do TableCell.
// !!! 8. Sirku stlpcov mozem definovat explicitne pomocou hviezdickovej konvecie pouzitim property Table.Columns.
// 9. Section (Block Element) je jednoduchy Element, ktory sluzi na grouping ostatnych textovych Elements. Je vhody ak chcem nejaky skupinu spolocne formatovat, tak ju dam do jednej Section a potom tu formatujem.
// !!! 10. Element BlockUIContainer (Block Element) umoznuje zadefinovat Elements (Button, ListBox) do formatovaneho textu.
// 11. Run (Inline Element) umoznuje zadefinovat text. Je mozne ho formatovat.
// 12. Span (Inline Element) umoznuje grouping ine Inline Elements a spolocne ich formatovat. Je podobny Section, ale toto je Inline Element.
// 13. Bold, Italic, and Underline (Inline Element) zdedene zo Span a umoznuju formatovat dany text. LEPSIE JE VSAK POUZIT SPAN A NASTAVIT Style.
// 14. Hyperlink (Inline Element) definuje hyperlinku. Je mozne reagovat na Click Event, alebo pri Page-based aplikaciach definovat NavigationPage property.
// 15. LineBreak (Inline Element) novy riadok.
// 16. InlineUIContainer (Inline Element) umoznuje vlozit NonText Element. Je podobny ako BlockUIContainer, az nato, ze je to Inline Element.
// 17. Floater (Inline Element) sluzi na vytvorenie boxu do ktoreho mozem vkladat text a ktory bude oddeleny od zbytku textu. Zvycajne sa pouziva na zobrazenie nejakeho zvyrazneneho textu, typicky v novinach. Zbytok textu v dokumente BUDE OBTEKAT Floater. Standardne Floater zabera celu sirku Window, ale da sa nastavit maximalne velkost.
// !!! 18. Do Floater sa da vlozit aj obrazok, ale je to treba robit cez BlockUIContainer ci InlineUIContainer. Vtedy sa DOPORUCUJE NASTAVIT MAXIMALNU VELKOST Floater.
// 19. Figure (Inline Element) je podobney ako Floater avsak umoznuje daleko lepsiu kontrolu obtekania textu, zarovnania a ofsetov od okraja okna.
// !!! 20. Standardne sa medzery nezachovavaju. Ak chcem aby neboli orezane tak muzim pouzit XML ATRIBUT 'preserve'.
// 21. Text Elements je mozne ovlada aj z kodu, ale je to dost omplikovane vzhladom na velke vnorenie jednotlivych Elements do seba.
// 22. Pomocou property TextAlignment mozem zedefinovat zarovnanie textu. Pomocou property FlowDocument.IsOptimalParagraphEnabled zas nastavim algorimtus na optimalne medzery v texte, ked sa roztahuje a pomocou property FlowDocument.IsHyphenationEnabled zas to kedy sa daju znaky '-' na rozdelenie slov.
// !!! 23. Na zobrazovanie textu mozem pouzit 3 rozne TextContainters.
//     A. FlowDocumentScrollViewer - zobrazuje text tak, ze to co sa nezmesti na plochu je mozne zobrazit pomocou ScrollBar.
//     B. FlowDocumentPageViewer - zobrazuje text tak, ze ho rozdeli na stranky medzi, ktorymi sa je mozne prepinat.
//     C. FlowDocumentReader - zorazuje text tak, ze bud ho rozdeli na stranky, alebo sa pouzije ScrollBar. Medzi pohladmi sa je mozne prepinat.
// 24. Vsetky 3 Text Container maju moznost zooming. Pomocou MinZoom a MaxZoom nastavim hranice zooming a pomocou ZoomIncrement zas mieru o aku sa bude robit zooming prei volani metod IncreaseZoom() a DecreaseZoom(). Pomocou property IsToolbarVisible je mozne zapnut automaticky toolbar, ktory zobrazi ScrollBar na automaticky zooming.
// 25. Pomocou properties FlowDocument a Paragraph je mozne nastavit format strankovania.
// 26. FlowDocument je mozne dynamicky nacitat z XAML Suboru cez XamlReader a zapisat cez XamlWriter.
// 27. Cely Document je mozne tlacit, cez metodu Print().
//------------------------------------------------------------------------
namespace FlowDocumentTest
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
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			SimpleFlowDocument			Win=new SimpleFlowDocument();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			ParagraphTest				Win=new ParagraphTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			ListTest					Win=new ListTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			TableTest					Win=new TableTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			SelectionTest				Win=new SelectionTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			BlockUIContainerTest		Win=new BlockUIContainerTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			InlinesTest					Win=new InlinesTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick8(object Sender, RoutedEventArgs E)
		{
			FloaterSimple				Win=new FloaterSimple();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick9(object Sender, RoutedEventArgs E)
		{
			FloaterWithWidth			Win=new FloaterWithWidth();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick10(object Sender, RoutedEventArgs E)
		{
			FloaterWithImage			Win=new FloaterWithImage();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick11(object Sender, RoutedEventArgs E)
		{
			FigureTest					Win=new FigureTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick12(object Sender, RoutedEventArgs E)
		{
			TextManagedByCode			Win=new TextManagedByCode();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick13(object Sender, RoutedEventArgs E)
		{
			TextJustificationTest		Win=new TextJustificationTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick14(object Sender, RoutedEventArgs E)
		{
			TextContainers				Win=new TextContainers();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick15(object Sender, RoutedEventArgs E)
		{
			ZoomingTest					Win=new ZoomingTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick16(object Sender, RoutedEventArgs E)
		{
			PageTest					Win=new PageTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------