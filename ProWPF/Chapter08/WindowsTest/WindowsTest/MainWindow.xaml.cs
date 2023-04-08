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
using System.Diagnostics;
//------------------------------------------------------------------------
// 1. Program demonstruje niektore vlastnosti triedy Window.
// 2. Pomocou property ResizeMode mozem nastavit Minimize a Maximize tlacitka.
// 3. RestoreBounds vrazcia velkost okna - aj ked je v Minimized, alebo Maximized state.
// 4. Property WindowStyle dava styl okna. Ci bude mat titulkovy pruh a tak podobne.
// !!! 5. Pomocou property AllowsTransparency mozem vyrobit PRIEHLADNE OKNO. Ale ZAROVEN MUSI BYT NASTAVENY WindowStyle na 'None'. A takisto Bacground NA TRANSPARENTNU FARBU.
// !!! 6. Trieda SystemParameters obsahuj OBROVSKE MNOZSTVO PROPERTIES tykajucich sa OBRAZOVKY.
// 7. Pomocou property Visibility (alebo metdy Hide()) je mozne skryt okno, alebo ho znova zobrazit.
// 8. Propety Owner sluzi na zadefinovane Ownera okna. Ak ma Window Ownera potom minimalizacia Ownera sposobi minimalizaciu okna, ktore vlastni, podobne maximalizacia, ci zatvorenie okna.
// !!! 9. Realny zmysel Owner je iba vtedy ak spusta MODALNE OKNO.
// 10. Pomocou property DialogResult, ktore je Nullable<bool> moze dialove okno informovat Parent okno o vysledku akcie. Tuto property musim nastavovat bud rucne, alebo pomocou nastavenia IsDefault a IsCancel na danom tlacitku. Hdnotu tejto priperty ozem ziskat ako navratovu hodnou motody ShowDialog().
// 11. Ak chcem vytvorit Window s neobldnikovym tvarom musi urobit toto.
//     A. Nastavit AllowsTransparency na TRUE.
//     B. Nastavit WindowStyle na None.
//     C. Nastavit Background na Transparent Color.
//     D. Pridat nestvorcovy Content, bud pomocou napriklad PNG su\boru ako Background, alebo vykreslenim grafiky pomocou WPF Elements.
// !!!!! 12. Extremne jednoducho sa da zabezpecit PRESUVANIE NonRectangularWindow pri klepnuti na jeho Content. Staci zavolat moetdu DragMove() napriklad pri stlaceni laveho tlacika mysky a je to.
// !!!!! 13. Rozhrahovanie NonRectangular Window je zlozitejsie a vyzaduje niekolko krokov a JEDNU FINTU.
//     A. Finta spociva v tom, ze okolo celeho Window spravim NEVIDITELNY Rectangle, ktory vsak bude reagovat na mysku.
//     B. Na tomto Rectangle budem zachytavat stlacenie tlacitka pohyb a uvolnenie tlacika a pocas nich BUDE OKNO ZVECSOVAT, ALEBO ZMENSOVAT.
//     !!! C. Nato aby bol NEVIDTELNY Rectangle v popredi MUSI BYT V GRIDE AKO POSLEDNY A MUSI MAT NSTAVENY Aligment na Stretch a frabu samozrejme transparentnu. Ak ma grid viacero Column a Rows tak sa musi roztahovat na vsetky, aby zabral cel plochu.
//------------------------------------------------------------------------
namespace WindowsTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private Visibility					MWin;
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
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			NoResize				Win=new NoResize();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			CanMinimize				Win=new CanMinimize();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			CanResize				Win=new CanResize();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			CanResizeWithGrip		Win=new CanResizeWithGrip();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			RestoreBounds			Win=new RestoreBounds();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			WSNone					Win=new WSNone();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			WSSingleBorderWindow	Win=new WSSingleBorderWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick8(object Sender, RoutedEventArgs E)
		{
			WSThreeDBorderWindow	Win=new WSThreeDBorderWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick9(object Sender, RoutedEventArgs E)
		{
			WSToolWindow			Win=new WSToolWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick10(object Sender, RoutedEventArgs E)
		{
			AllowsTransparency		Win=new AllowsTransparency();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick11(object Sender, RoutedEventArgs E)
		{
			if (MWin!=null)
				return;

			MWin=new Visibility();
			MWin.Show();
		}
//------------------------------------------------------------------------
		private void OnClick12(object Sender, RoutedEventArgs E)
		{
			if (MWin==null)
				return;

			MWin.Visibility=System.Windows.Visibility.Visible;
		}
//------------------------------------------------------------------------
		private void OnClick13(object Sender, RoutedEventArgs E)
		{
			OwnedWindow				Win=new OwnedWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick14(object Sender, RoutedEventArgs E)
		{
			OwnedWindow				Win=new OwnedWindow();

			Win.Show();
		}
//------------------------------------------------------------------------
		private void OnClick15(object Sender, RoutedEventArgs E)
		{
			DialogResult			Win=new DialogResult();
			bool?					Ret=Win.ShowDialog();

			if (Ret==null)
				Debug.WriteLine(string.Format("Ret: NULL !"));
			else if (((bool) Ret)==false)
				Debug.WriteLine(string.Format("Ret: FALSE !"));
			else
				Debug.WriteLine(string.Format("Ret: TRUE !"));
		}
//------------------------------------------------------------------------
		private void OnClick16(object Sender, RoutedEventArgs E)
		{
			SimpleNonRectangularWindow	Win=new SimpleNonRectangularWindow();

			Win.Show();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------