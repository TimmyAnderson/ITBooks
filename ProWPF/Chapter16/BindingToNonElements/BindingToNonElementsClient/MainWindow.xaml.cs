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
// 1. Program demonstruje pouzitie DB na mapovacie voci non-Element objects.
// !!! 2. Pri DB na non-Element objects MUSI BYT SOURCE PROPERTY TYPU PUBLIC.
// !!! 3. Ak chcem spravit toto mapovanie potom musim (namiesto ElementName ak mapujem na Element) nastavit niektoru z tychto property.
//    A. Source - obsahuje referenciu na objekt, ktory je Source objektom.
//    B. RelativeSource - dovoluje sa dokazat na Destination Element, alebo Element vyssie v Tree nad tymto Elementom, popripade na Element asociovany s CT, alebo predchadzajuci DataItem pri ItemControls. Vyuziva RelativeSource objekt. Pouziva sa najme pri CT Binddings.
//    C. DataContext - vyhladava v Tree objekty ulozene v DataContext, pricom postupuje v strome od Destination Elementu az k rootu a hlada Element s non-null property DataContext. Ak ho najde tak tento DataContext pouzije AKO SOURCE pre Binding.
// !!! 4. ReferenceSource pomocou objektu RelativeSource a jeho property RelativeSourceMode umoznuje nastavit nasledujuce rezimy hladania Source.
//    A. Self - odkazujem sa na sam seba - na ten isty Element.
//    B. FindAncestor - najde parent Element v Tree bud podla typu, alebo podla AncestorLevel.
//    C. PreviousData - predchadzajuci DataItem pri ItemControl.
//    D. TemplatedParent - Element, na ktory som aplikoval CT. Pouziva sa pri deklaracii CT.
//------------------------------------------------------------------------
namespace BindingToNonElementsClient
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
			SourceBinding				Win=new SourceBinding();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			RelativeSource				Win=new RelativeSource();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			DataContext					Win=new DataContext();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------