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
using System.Windows.Navigation;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Program demonstruje pouzitie Page Functions.
// !!! 2. PF maju v Navigation TEN ISTY VYZNAM ako DIALOGOVE OKNA V KLASICKEJ APLIKACII. Dokazu vratit navratovu hodnotu Parent Page - tej, ktora ich volala.
// 3. PF mozu vracat hodnotu lubovolneho typu. Typ definujem pomocou XAML KEYWORD 'x:TypeArguments' v deklaracii Page.
// 4. Pri pouziti PF je nutne dodrzat nasledujuci postup.
//    A. Vytvorim instanciu PF a zaregistrujem hander na jej event Return. Prave tento handler sa zavola, ked PF skonci.
//    B. PF vyvolam klasicky cez NavigationService.Navigate().
//    C. Ak chcem vratit z PF navratovu hodnotu tak zavolam metodu OnReturn() PF a predat je pozadovanu hodnotu, alebo NULL ak sa akcia nevykonala - napriklad ako reakcia na tlacitko Cancel.
// 5. Program zaroven aj demonstruje volanie jednej PF z inej PF.
// !!! 6. Pomocou PF property RemoveFromJournal mozem nasatvit aby sa po ukonceni PF vymazal Back Journal, aby sa na uz vykonanu PF nedalo znova vratit. Ako DEFAULT hondota je TRUE.
//------------------------------------------------------------------------
namespace PageFunctionsTest
{
//------------------------------------------------------------------------
	public partial class MainPage:System.Windows.Controls.Page
	{
		public MainPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnPF1Click(object Sender, RoutedEventArgs E)
		{
			PageFunction1		PF=new PageFunction1();

			// Zaregistrujem Return Handler.
			PF.Return+=new ReturnEventHandler<int>(PF_Return1);
			// Navigujem sa na Page predanim vytvoreneho objektu.
			this.NavigationService.Navigate(PF);
		}
//------------------------------------------------------------------------
		private void OnPF2Click(object Sender, RoutedEventArgs E)
		{
			PageFunction2		PF=new PageFunction2();

			// Zaregistrujem Return Handler.
			PF.Return+=new ReturnEventHandler<string>(PF_Return2);
			// Navigujem sa na Page predanim vytvoreneho objektu.
			this.NavigationService.Navigate(PF);
		}
//------------------------------------------------------------------------
		// Return Handler z PF1.
		private void PF_Return1(object Sender, ReturnEventArgs<int> E)
		{
			if (E!=null)
				MResult.Content=string.Format("Int Result: {0} !",E.Result);
			else
				MResult.Content=string.Format("Int Result: {0} !","CANCEL PRESSED");
		}
//------------------------------------------------------------------------
		// Return Handler z PF2.
		private void PF_Return2(object Sender, ReturnEventArgs<string> E)
		{
			if (E!=null)
				MResult.Content=string.Format("String Result: {0} !",E.Result);
			else
				MResult.Content=string.Format("String Result: {0} !","CANCEL PRESSED");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------