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
// 1. Prorgam demonstruje pouzitie Menu a ContextMenu.
// 2. Menu je mozne zorbaovat luboolne na ploche Window, dokocna aj viacero Menus na jednom Window.
// 3. Menu ma property IsMainMenu, ktore urcuje ci je Menu hlavne. Ak stlacim Alt potom sa podciarkne prave toto menu znakmi na ktorych su Shortcuts.
// 4. Pomocou property StaysOpenOnClick ak ju nastavim na TRUE tak ostane Menu viditelne az pokym neklepnem niekde inde.
// 5. Menu moze obsahovat MenuItem, Seprator, alebo lubovolny iny Element. No je lepsie ine Elements nepouzivat, kedze maju casto velmi zvlasnte chovania. Napriklad ked tam dam TextBox a nemam nastvene StaysOpenOnClick na TRUE, tak pri rpesune mysly Menu zmizne.
// !!! 6. Controls ako Buttons su v Menu AKTIVNE a je po nich MOZNE KLEPNUT.
// 7. Kiknutie po MenuItem je mozne spracovat zachytanem eventu OnClick, alebo asociovanim Command. V druhom pripade ziskavam uz aj shortcut, ktory sa zobrazi vedla textu MenuItem.
// 8. S MenuItem je mozne asociovat aj ikonu, ci check mark.
// !!! 9. ContextMenu NEMOZU BYT UMIESTNENE PRAIMO NA Window, ALE IBA na nastavenie property ContextMenu INEHO ELEMENTU. Pomocou ShowOnDisabled na TRUE sa moze ContextMenu aktiovovat s klavesnice aj ked Element, ktoremu je priradeny je disabled.
// !!! 10. Separator vdaka moznosti zmenit jeho CT je mozne prerobit tak aby zobrazoval napriklad napdis menu. S MenuItem sa TO NEDA UROBIT aj ked tam dam don Label, pretoze stale pri presune myskou na nom sa bude zvyraznovat.
//------------------------------------------------------------------------
namespace MenusTest
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
			SimpleMenu				Win=new SimpleMenu();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			ContextMenu				Win=new ContextMenu();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------