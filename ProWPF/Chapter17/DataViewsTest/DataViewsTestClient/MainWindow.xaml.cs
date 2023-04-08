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
// 1. Program demonstruje pouzitie DataView objektu.
// 2. DataView je objekt, ktory stoji medzi DataSource a Elementom a vytvara sa na pozadi, ked vytvorim Binding.
// 3. Default DataView je mozne ziskat pomocou CollectionViewSource.GetDefaultView().
// !!! 4. Existuju 3 objektu typu DataView, ktore sa vytvaraju podla toho AKEHO TYPU JE DataSource.
//    A. BindingListCollectionView sa vytvori ked DataSource je DataTable - implementuje IBindingList.
//    !!! B. ListCollectionView sa vytvori ked DataSource NEIMPLEMNENTUJE rozhranie IBindingList, ale IMPLEMENTUJE IList. Pouziva sa ked DataSource DEDI Z ObservableCollection.
//    !!! C. CollectionView sa vytvori ked DataSource NEIMPLEMENTUJE rozhranie IBindingList ani IList, ale IMPLEMENTUJE IEnumerable. Avsak tento DataView JE PRE VELKE COLLECTIONS POMALY. Preto je lepsie pouzivat ako DataSource ObservableCollection a teda ListCollectionView.
// 5. Sorting nad DataView je mozne realizovat pridanim objektu SortDescription do collection SortDescriptions. V kazdej SortDescription mozem specifikovat okrem mena property aj smer triedenia. Triediaci algoritmus pouziva rozhranie IComparer, ktory musim implemtnovat. Obbejkt, ktory ho implementuje musi byt zaslany pomocou CustomSort property, aby ho WPF mohla pouzit.
// !!!!! 6. Vyzera to, ze pri Filteringu a Sortingu musim ma DVE SOURCES ak chce na 2 ListBox ma INE SORT\FILTER KRITERIA. Ked som pouzival ten isty DataSource - AJ KED SOM MAL INY DATAVIEW tak sa na 2 ListBoxy s inymi DataView pouzilo TO ISTE SORTOVANIE\FILTERING.
// 7. Pomocou ItemsControl je mozne realizovat aj Grouping. Pri Grouping su podla zvolenej property jednotlive Items zoskupene do Groupy. Robi sa to nastavenim property GroupDescriptions. Samozrejme mozem vytvarat aj Groups podla viacerych properties tym, ze do GroupDescriptions dam viacero PropertyGroupDescription objektov.
// 8. Items, ktore patria jednej a tej iste Groupe su zaradene do objektu GroupItem. Group je mozne formatovat pomocou property GroupStyle, ktoru je mozne nastavit DataTemplate pre Groupu, jej Header, Container a mnoho dalsieho. Viac info v objekte GroupStyle.
// !!! 9. CUSTOM Grouping je mozne urobit vytvorenim vlasneho Convertera (dedi IValueConverter) a predanim do objektu PropertyGroupDescription.
// !!!!! 10. Ked robim Grouping tak by sortovanie malo byt nastavene nad rovnaymi properties ako Grouping.
// 11. DataView mozem deklarovat aj v XAML. V takom pripade vyuzivatm triedu CollectionViewSource, ktora ma take iste property na definovanie Filtra, Sotringu ci Groupingu ake som pouzival pri deklaracii v kode. Dany ItemsControl, ktory ma zobrazovat DataView namapujem na TENTO OBJEKT CollectionViewSource a v kode po naplnenie dat nastavim CollectionViewSource.Source na moju kolekciu a vykona sa DB.
// 12. DataView drzi informaciu o aktualne Selected Item a je mozne nan aplikovat metody presunu sa po Collection.
// !!! 13. Standardne ItemsControl NIE JE SYNCHRONIZOVANY so Selected Item v DataView. Ak chcem, aby tomu tak bolo musim nastavit ItemsControl.IsSynchronizedWithCurrentItem na TRUE.
//------------------------------------------------------------------------
namespace DataViewsTestClient
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
			NoDataView				Win=new NoDataView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			FilterDataView			Win=new FilterDataView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			SortDataView			Win=new SortDataView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			GroupingDataView		Win=new GroupingDataView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			XAMLDeclarationDataView	Win=new XAMLDeclarationDataView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			NavigatingDataView		Win=new NavigatingDataView();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------