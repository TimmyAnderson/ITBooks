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
// 1. Program demonstruje ukladanie CUSTOM objektov do Journal, ktore sluzia na refresh stranky pri Back a Forward akcii.
// 2. Do Journal je mozne ukladat CUSTOM DATA pomocou NavigationService a meotdy AddBackEntry(). Na odstranenie entry z Journal sluzi metoda RemoveBackEntry().
// 3. Do Journal mozem uklada IBA objekty zdedene z CustomContentState.
// !!! 4. Trieda CustomContentState ma abstraktu netodu Reply(), ktora je volana ked dany CUSTOM OBJEKT ma OBNOVIT Page. TU musim pridat LOGIKU REFRESHU Page PODLA DAT, ktore mam ulozene v tomto objekte.
// !!! 5. Page MUSI implementovat rozhranie IProvideCustomContentState a jej metodu GetContentState(), ktorym si Page vypyta objekt CUSTOM OBJEKT (zdedeny z CustomContentState).
// !!!!! 6. Cela logika fungovania CUSTOM OBJEKTOV v Journale je nasledujuca.
//    A. Ked sa zmni obsah Page tak, ze povodny chcem ulozit (tu - premiestnim Item medzi dvoma ListBoxes) tak si ulozim obsah stranky do CUSTOM OBJEKTU (CListSelectionJournalEntry - dedi z CustomContentState). Tento objekt sa ulozi do Journalu.
//    B. Ak opustam stranku (klepnutim na hyperlinku, alebo stlacenim tlacitok Back\Forward) tak sa zavola metoda IProvideCustomContentState.GetContentState(), ktora vrati aktualny stav Page a NavigatorService ho ulozi do Journal.
//    C. Naopak ked sa vraciam na stranku (cez tlacitka Back\Forward) tak NavigatorService vytiahne z Journal CUSTOM OBJEKT (zdedeny z CustomContentState) a zavola sa jeho metoda Reply(). PRAVE TU MUSIM OBNOVIT STAV Page.
//    D. Ked sa prepinam medzi dvoma instanciami OBRAZU TEJ ISTEJ Page tak sa najprv zavola IProvideCustomContentState.GetContentState() na AKTUALNOM STATE a potom Reply() na STATE, KTORY JE ULOZENY V Journal.
// !!!!! 7. V povodnom programe bola chyba, ked bol objekt Page asociovany s CustomContentState co zblblo ked sa vytvorila nova instancia Page. Viac info v CustomContentState.
//------------------------------------------------------------------------
namespace AddCustomJournalItems
{
//------------------------------------------------------------------------
	public partial class MainPage:System.Windows.Controls.Page
	{
//------------------------------------------------------------------------
		public MainPage()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------