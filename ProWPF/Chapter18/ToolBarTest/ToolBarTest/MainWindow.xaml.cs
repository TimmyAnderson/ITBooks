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
// 1. Program demonstruje pouzite ToolBars.
// 2. Na plochu ToolBar je mozne ukladat LUBOVOLNE Elements, ale doporucuje sa iba Button, ComboBox, CheckBox, RadioButton a Separator. Ine vyzeraju trochu divne.
// !!! 3. ToolBar PREPISE STYLE SVOJICH Child Elements preto aby napriklad Buttons vyzerali ako Buttons na ToolBare. Teda nemali tien. Podobne aj CheckBox, ci RadioButton vyzeraju inac. Implementovane je to prave tak, ze ToolBar AUTOMATICKY ZMENI Defaul Style svojich Child Elements.
// !!! 4. ToolBar nema nieco ako ToolBarItem, ktory by obaloval Content ako je to v pripade ListBoxu napriklad.
// 5. ToolBar je zdedeny z HeaderedItemsControl a teda ma property Header. Ta sa vsak praimo NEZOBRAZUJE, ale je ju mozne pouzit napriklad v Menu, kde si zapinam a vypinam jednotlive ToolBars. Tam to mozem vyuzit.
// 6. ToolBar ak sa vsetky Child Items nezmestia na jeho plochu moze vyuzit Overflow Menu na zobrazenie zbytku. To kedy a ako sa bude toto menu zobrazovat urcuje property OverflowMode.
// 7. Aj ked ToolBars je mozne umiestnit hockde, daleko lepsie je pouzit ToolBarTray, ktory umoznuje robit operacie Drag and Drop, posvat a menit pozicie ToolBars, ktre na svojej ploche obsahuje. Kazdy ToolBar, ktory je sucastou ToolBarTray moze menit sovju poziciu pokial to explicitne nezakazem property IsLocked na FALSE.
// !!! 8. Na ToolBarTray je mozne jednotlive ToolBars zaradzovat do takzvanych Bands - teda skupin. ToolBars v jednom Band su zvycajne ukladane do toho isteho riadku. Band sa definuje pomocou property ToolBar.Band. Ked uzivatel meni pozicie ToolBars tak, ze sa zmenia ich Band, tak sa zmeni aj hodnota DP Band.
//------------------------------------------------------------------------
namespace ToolBarTest
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
			SimpleToolBar				Win=new SimpleToolBar();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			OverflowMenu				Win=new OverflowMenu();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			ToolBarTrayTest				Win=new ToolBarTrayTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------