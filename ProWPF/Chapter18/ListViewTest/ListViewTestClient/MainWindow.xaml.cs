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
// 1. Program demonstruje pouzitie ListView.
// 2. ListView je mimoriadne dobre customizovatelny Element, ktory je podobny ListBox. Je tam vsak jeden KLUCOVY ROZDIEL a to v property View.
// !!! 3. View property obsahuje objekt typu ViewBase. ViewBase je abstraktna trieda, ktora obsahuje 2 TEMPLATES. V property DefaultStyleKey obsahuje TEMPLATE PRE ListView. V property ItemContainerDefaultStyleKey je zas ulozena TEMPLATE PRE ITEM. Teda View property ma AKO TEMPLATE PRE ELEMENT TAK AJ PRE JEHO ITEM.
// !!! 4. WPF poskytuje JEDINU IMPLEMENTACIU ViewBase a to GridView, ktora umoznuje lahko vytvarat Grid zobrazenie pre dany ListView.
// !!! 5. V GridView mozem customizovat pomcou property CellTemplate vyzor jednotlivych CELLS tym, ze definujem pre ne DT. Podobne je mozne nastavit aj DT pre Header ci ColumnHeader. Je mozne pouzit aj TemplateSelectors.
// 6. Ak chce vytvorit CUSTOM View potom je potrebne spravit nasledujuce kroky.
//    A. Vytvorit CUSTOM View class - zdedenu z ViewBase (CTileView). Je to velmi jednoducha trieda s 2 properties zdedenymi z ViewBase, ktore ukazuju na DT pre ListView a ListViewItem.
//    B. Musim vytvorit dve Styles, pre ListView a ListViewItem. Nato aby mohli byt AUTOMATICKY nacitane, musia byt definovane v subore Generic.XAML a ten v adresari Themes. Ako identifikator MUSIM POUZIT ComponentResourceKey.
//    C. Teraz uz v XAML Window mozem definovat CTileView s danym DT. Tu ulozim do ItemTemplate, odkial si ju Style pre ListViewItem vycita.
// !!! 7. ComponentResourceKey je specialna trieda sluziaca ako IDENTIFIKATOR do Resources. Je zvlastnostou je, ze identifikuje assembly a typ. typ zvycajne ani NEMUSI BYT IMPLEMENTOVANY A OSTNE PRAZDNY. Sluzi iba na identifikaciu.
//------------------------------------------------------------------------
namespace ListViewTestClient
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
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			SimpleGridView				Win=new SimpleGridView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			CellTemplates				Win=new CellTemplates();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			CustomListView				Win=new CustomListView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------