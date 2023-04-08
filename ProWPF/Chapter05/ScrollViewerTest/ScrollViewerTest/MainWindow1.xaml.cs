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
// 1. Program demonstruje ScrollViewer.
// 2. Scrolling sa realizuje pomocou ScrollViewer, ktory umoznuje umiestnit do svojho Content JEDINY Element a ten scrolovat.
// !!! 3. ScrollViewer umoznuje mat iba jeden Child Element a od neho zavisi ci skutocne sa bude robit scrolling, alebo nie.
// !!!!! 4. Princip ScrollViewer je ten, ze ZOBERIE VELKOST CHILD Element A AK TEN PRESIAHNE VELKOST VIDITELNEJ OBLASTI TAK ZAPNE SCROLL BAR NA SCROLLING.
// !!!!! 5. Bezne Element, ak im nastavim vecsiu velkost ako tu, ktoru maju moznost zobrazit tak za zapne SCROLL BAR a je MOZNY SCROLLING.
// !!!!! 6. StackPanel UMOZNUJE scrolling, kedze DYNAMICKY OD POCTU JEJ CHILD Elements ZVECSUJE SVOJU VELKOS A AK TA PRESIAHNE VIZUALNU VELKOST TAK SA SCROLLING ZAPNE.
// !!!!! 7. Grid Cell NEUMOZNUJE scrolling, kedze DYNAMICKY NEMENI SOVJU VELKOST OD POCTU JEJ Child Elements. Ak do Grid Cell hodim viac Elements TAK SA PREKRRUJU A JE VIDIET IBA POSLEDNY. VELKOST CELL SA NEZVECSI A TEDA NIE JE DOVOD NA SCROLLING.
// !!!!! 8. Implementovanim rozhrania IScrollInfo mozem spravit CUSTOM SCROLLING. Zo standardnych komponent ho implementuje StackPanel vdaka ktoremu pri nastaveni ScrollViewer.CanContentScroll na TRUE a scrollingu sa scroluje nie PO PIXELOCH, ALE MEDZI Child Elements.
// !!! 9. ScrollViewer obsahuje sadu metod, ktorym mozem robit scrolling programovo. Demonstruje to MainWindow6.xaml.
//------------------------------------------------------------------------
namespace ScrollViewerTest
{
//------------------------------------------------------------------------
	public partial class MainWindow1:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow1()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------