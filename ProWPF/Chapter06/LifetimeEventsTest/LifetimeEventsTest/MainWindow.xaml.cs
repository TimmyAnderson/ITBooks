using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje udalosti, ktore vznikaju pri vzniku a inicializacii okna.
// 2. Tri Lifetime events ma KAZDY ELEMENT.
//    A. Initialized - vytvorena instanica Elementu a nakonfigurovana z XAML. Cely Window VSAK ESTE NIE JE INICIALIZOVANY.
//    B. Loaded - Element vytvoreny a nakonfigurovany. Cely Window UZ JE INICIALIZOVANY. NAJLEPSIE MIESTO NA DOPLNENIE CUSTOM INICIALIZACIE.
//    C. Unloaded - Element, alebo cely Window odstraneny.
// 3. Tieto Events su SPEPCIFICKE PRE Window.
//    A. SourceInitialized - ked sa vytvori HWND okna.
//    B. ContentRendered - je volany ked sa Window ??? PRVY KRAT RENDERUJE.
//    C. Activated - ked Window dostane Focus.
//    D. Deactivated - ked Window strati Focus.
//    E. Closing - ked sa okno uzatvara. Tu mozes ZRUSIT ZATVARANIE OKNA.
//    F. Closed - posledny event predtym nez sa Window definitivne uzvrie.
// !!! 3. Ten isty objekt Window NEMOZEM OTVORIT VIAC AKO RAZ. Vyzera to, ze Window MOZE BYT OTVORENE IBA RAZ a ak chcem ho otvorit znova MUSIM VYTVORIT NOVU INSTANCIU WINDOW.
// !!!!! 4. Ak mam vytvorenu instanciu Window a to nema nastaneho predka (MSubWindow) tak POKIAL HO NEZATVORIM TAK SA NEDA SKONCIT APLIKACIA. DOKONCA AJ KED TO OKNO ANI LEN NEOTVORIL, TAK AK ZAVRIEM hlavne okno a toto NIKDY NEOTVORENE okno nebolo NIKDY OTVORENE A TEDA NIKDY ZAVRETE tak !!!!! sa program NESKONCI.
// !!!!! 5. Inak povedane ked sa aplikacia konci tak WPF SKONTORLUJE CI SU VSETKY Window v Closed STATE. AK NIE POTOM SA !!! NESKONCI. Situaciu je mozne riesit aj tym, ze sa Window nastavi ako Child Window a potom zavretie Main Window sposobi zavretie celej aplikacie.
// !!!!! 6. Body 4 a 5 sa vztahuju aj na NEMODALNE OKNA.
//------------------------------------------------------------------------
namespace LifetimeEventsTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		// Toto okno musim VZDY OTROCIT A ZATVORIT, ABY SA PROGRAM SKONCIL.
		private Window					MSubWindow1;
		private Window					MSubWindow2;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();

			MSubWindow1=new Window();
			MSubWindow2=new Window();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnShowNewDialog(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			Window		SubWindow=new SubWindow();

			SubWindow.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnShowSharedModalDialog(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MSubWindow1.ShowDialog();
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("!!! EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnShowSharedNonModalDialog(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MSubWindow2.Show();
			}
			catch(Exception Ex)
			{
				MessageBox.Show(string.Format("!!! EXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------