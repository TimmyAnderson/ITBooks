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
using System.Windows.Navigation;
using System.Windows.Threading;
using System.Diagnostics;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Page ked je hostovana v NavigationWindow.
// !!! 2. Na Page by som nemal nastavovat velkost, kedze tu mu prideli host (tu NavigationWindow).
// 3. Ak spustim z App.xaml priamo Page tak sa vytvori IMPLICITNY NavigationWindow.
// !!! 4. NavigationWindow je zdedeny z Window a obsahuje navigacne tlacitka ako aj podporu prechodu medzi Pages.
// !!! 5. V NavigationWindow je klucova property Source kde definujem Page, ktoru ma NavigationWindow wrapprovat.
// !!!!! 6. NavigationWindow NEMOZE OBSAHOVAT CONTENT - iba cez Source definovat Page, ktoru zorbazuje.
// 7. Medzi Pages sa je mozne prepipnat pomocou Hyperlink.
// !!! 8. Hyperlink NIE JE KLASICKY ELEMENT. Je pouzitelny iba v niektorych Elements ako jeho Child. Napriklad v TextBlock.
// 9. Pomocou Hyperlink je mozne sa odkazovat aj na WEB PAGES.
// !!! 10. Pri dokaze na WEB PAGES je dobre ZACHYTAVAT CHYBY a to napriklad tym, ze spracujem events DispatcherUnhandledException a NavigationFailed.
// !!! 11. Ak mam Page, ktore je scrolovatelna (napriklad cez ScrollViewer) potom sa mozet ODKAZAT PRIAMO NA NEJAKY JEHO POMENOVANY ELEMENT KONVECIOU 'Page.xaml#ElementName'.
// !!!!! 12. KOD MyNavigationWindow SA VOBEC NEPUSTA. Vyzera to, ze pri NavigationPage v TOMTO PRIKLADE sa mi nepodarilo dosiahnut zviazanie KODU A XAML suboru. Preto ani sa nepusti konstor, ktory ma zachytavat chyby navigacie.
// !!!!!!! 13. CHYBA V BODE 12 BOLA OPRAVENA. STACILO KOREKTNE NASTAVIT KOMPILACIU TOHTO SUBORU.
//------------------------------------------------------------------------
namespace PageInNavigationWindowTest
{
//------------------------------------------------------------------------
	public partial class MyNavigationWindow : NavigationWindow
	{
//------------------------------------------------------------------------
		public MyNavigationWindow()
		{
			// !!!!! TENTO KOD SA VOBEC NESPUSTI. CELY KONSTRUKTOR SA NESPUSTI.
			Application.Current.DispatcherUnhandledException+=new System.Windows.Threading.DispatcherUnhandledExceptionEventHandler(Current_DispatcherUnhandledException);
			Application.Current.NavigationFailed+=new NavigationFailedEventHandler(Current_NavigationFailed);

			InitializeComponent();
		}
//------------------------------------------------------------------------
		private void Current_DispatcherUnhandledException(object Sender, DispatcherUnhandledExceptionEventArgs E)
		{
			Debug.WriteLine(string.Format("!!! EXCEPTION: {0} !",E.Exception.Message));

			MessageBox.Show(string.Format("!!! EXCEPTION: {0} !",E.Exception.Message));

			// Musim ju spracovat, aby sa Exception nesirila dalej.
			E.Handled=true;
		}
//------------------------------------------------------------------------
		private void Current_NavigationFailed(object Sender, NavigationFailedEventArgs E)
		{
			Debug.WriteLine(string.Format("!!! EXCEPTION: {0} !",E.Exception.Message));

			MessageBox.Show(string.Format("!!! EXCEPTION: {0} !",E.Exception.Message));

			// Musim ju spracovat, aby sa Exception nesirila dalej.
			E.Handled=true;
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------