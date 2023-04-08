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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms.Integration;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzivanie WinForms komponent vo WPF aplikacii.
// 2. Zobrazenie modalneho WinForms okna je uplne bez problemov.
// 3. Pri zobrazeni NEMODALNEHO WinForms okna je treba volat najprv WindowsFormsHost.EnableWindowsFormsInterop(). Staci RAZ V CELEJ APLIKACII. To sposobi, ze nemodalne okno bude zachytavat vstup z klavesnici a mysi. Inak by ho nechytal.
// 4. Nato aby WinForms okna mali korektny styl je treba v programe RAZ zavolat System.Windows.Forms.Application.EnableVisualStyles().
// 5. WindowsFormsHost sluzi na hostovanie JEDNEJ WinForms KOMPONENTY v WPF okne. WinForms komponenta sa nastavi v poperty Child.
// 6. Nad cez WindowsFormsHost wrapped komponentanmi je mozne priamo v XAML nastavovat properties (vdaka konvertetom), alebo aj events.
// 7. Ked nastavim Name tak mozem k WinForm komponentne normalne pristupovat z kodu.
// !!! 8. Binding sice na properties WinForms komponent sice nemozem pouzi priamo, ale pri obratnej Mode (OneWayToSource) mozem.
// !!! 9. Kedze WinForms komponenty su vykreslovane WinForms runtime tak transformacie, opacity a podobne na nich nie su aplikovane a nevykonaju sa. Ignoruju sa.
// 10. WindowsFormsHost umoznuje hostovat iba JEDNU WinForms komponentu. Jednym so sposobov ako to obist je vytvorit CUSTOM WinForms User Control. Na tomto Control mozem umiestnit viacero WinForms Controls a vysvtavit spolocne properties, ktore je MOZNE NASTAVOVAT AJ Z XAML.
// !!!!! 11. WPF NEPODPORUJE ActiveX. Ale da sa do obist, ak najprv dam ActiveX do WinForms komponenty ci okna a to potom vo WPF zobrazim.
// !!! 12. Ak v jednom okne miesam WPF a WinForms komponenty tak funguje focus, aj tab-stops, action-key a podobne.
// !!! 13. Kontajnerove komponenty WindowsFormsHost a ElementHost su schopne niektore zakladne property prenasat na property vnorenych WPF\WinForms elementov\komponent. napriklad Foreground, Background, ci Fonty. Potom STACI NATSVIT TUTO PROPERTY NA KONTAJNERI A TA ZMENI PROPERTY SVOJEJ CHILD KOMPONENTY\ELEMENTU.
//------------------------------------------------------------------------
namespace InteroperabilityWPF
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			// !!! Nato aby bol pri NEMODALNOM okne smerovany INPUT do NEMODALNEHO OKNA je potrebne pouzit metodu EnableWindowsFormsInterop().
			// !!! Staci ju volat IBA RAZ V PROGRAME.
			WindowsFormsHost.EnableWindowsFormsInterop();

			// !!! Standardne WinForms okna pouzivaju preWinXP styl. Ak chcem zapnut nove styly, musim volat metodu EnableVisualStyles().
			// !!! WinForms aplikacie robia toto volanie automaticky, avsak v pripade WPF apliackie to musim spravit ja a IBA RAZ V PROGRAME.
			System.Windows.Forms.Application.EnableVisualStyles();

			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			WinFormsWindow			Win=new WinFormsWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			WinFormsWindow			Win=new WinFormsWindow();
			
			Win.Show();
		}
//------------------------------------------------------------------------
		// !!! Toto je event z WinForms komponenty.
		private void MMaskedTextBox_MaskInputRejected(object Sender, System.Windows.Forms.MaskInputRejectedEventArgs E)
		{
			MessageBox.Show(string.Format("Position: {0}, RejectionHint: {1} !",E.Position,E.RejectionHint),"REJECTED");
		}
//------------------------------------------------------------------------
		private void Button_Click3(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show(string.Format("Masked Text: {0} !",MMaskedTextBox.Text));
		}
//------------------------------------------------------------------------
		private void Button_Click4(object Sender, RoutedEventArgs E)
		{
			// !!! Cistam CUSTOM property TextBoxString.
			MessageBox.Show(string.Format("Text In Custom WinForms Control: {0} !",MMyUserControl.TextBoxString));
		}
//------------------------------------------------------------------------
		private void Button_Click10(object Sender, RoutedEventArgs E)
		{
			MnemonicTest			Win=new MnemonicTest();
			
			Win.Show();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------