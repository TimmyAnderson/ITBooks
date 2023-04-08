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
// 1. Program demonstruje pouzitie DataBinding Direction.
// 2. DB Direction ma 5 moznych hodnot.
//    A. OneWay - Binding zo zdroja do ciela.
//    B. OneWayToSource - Binding z ciela do zdroja.
//    C. TwoWay - OBOJSMERNY Binding medzi zdrojom a cielom.
//    D. OneTime - OneWay Binding, kde sa hodnota zo zdroja do ciela prenesie IBA RAZ a zmeny zdroja NIE SU POTOM REFLEKTOVANE NA CIELI.
//    E. Default - Smer Bindingu sa urcuje podla registracie DP, kde sa urci Default DB.
// !!! 3. Vyhodou OneWayToSource, ktory je obrateny OneWayBinding je, ze Source, ktory bude z Target naplnany MOZE BY AJ non-DP property. V DB totizto plati, ze Target property MUSI BYT DP, no a pomocou tohto typu DB sa to DA OBIST.
// !!! 4. Pre TextBox.Text je Default TwoWay Binding, zatial co vsetky ostatne DB maju default na OneWay.
// !!!!! 5. Zatial co zmena Source sa OKAMZITE PREMIETNE NA Destination, tak v pripade TwoWay a OneWayToSource Binding sa zmena z Destination na Source udeje AZ KED Destination Element STRATI FOCUS.
// !!! 6. Toto Default nastavenie casu toku zmien z Destination na Source je mozne zmenit property UpdateSourceTrigger. Tuto property MA ZMYSEL NASTAVIT IBA PRI TwoWay a OneWayToSource Bindings.
//    A. PropertyChanged - k zmene Source okamzite po zmene Desination.
//    B. LostFocus - k zmene Source okamzite po strate Focusu na Desination Elemente.
//    C. Explicit - k zmene Source okamzite po volani UpdateSource().
//    D. Default - k zmene Source na zaklade nastavenia pri registracii DP.
//------------------------------------------------------------------------
namespace BindingDirectionTest
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
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------