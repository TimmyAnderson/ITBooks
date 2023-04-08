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
using DependencyPropertiesTestLibrary;
//------------------------------------------------------------------------
// 1. Program demostruje rozlicne moznosti pouzitia DP a AP.
// 2. DP aj AP mozem pouzit na LUBOVOLNY DO.
// 3. Pouzitie dedicnosti.
//    A. Dedicnost sa uplantuje iba na VIZUALNE Elements - take co su zdedene aspon z FrameworkElement.
//    B. Na objekty NEZDEDENE z FrameworkElement sa DEDICNOST NEUPLATNUJE.
//    C. Dedicnost funguje medzi Elements, kde ak Element NEMA nastavenu hodnotu AP, ale niektory jeho predok v strome ju ma nastavenu tak ju tento Element zdedi.
//    !!! D. Co bolo zaujimave, ze ked som sa pokusal sam implementovat Content property (CFEParent dedil z FrameworkElement) tak TO NEFUNGOVALO. Ked som pouzil ako [ContentProperty] OBYCAJNU property tak DECINOST NESLA - co je logicke, kedze to nie je DP. No a ked som sa pokusial spravit z [ContentProperty] DP tak ZNOVA DEDICNOST NEBEZALA. DOVOD SOM NEZISTIL. Riesenim bolo zdedit CFEParent z ContentControl, kedy prave ContentControl implementuje [ContentProperty] a tak ju vyuzijem. NEVIEM kde bol zadrhel, bolo by treba viac informacii.
// 4. Pouzitie AP.
//    A. AP su v podstate TO ISTE AKO DP. Jediny rozdiel je, ze AP mozem V XAML aplikovat AJ NA INE ELEMENTS, AKO TEN, KDE SOM AP DEFINOVAL. Programovo je vsak mozne KAZDU DP nastavit NA HOCIJAKOM DependencyObject OBJEKTE A TEDA VLASTNE ROBIA TO ISTE CO AP.
//    B. Klucovym rodziel pri definicii je, ze pri DP definujem DP a property wrapper. Pri AP definuje AP a 2 metody s menom GetXXX() a SetXXX(), kde XXX je meno property.
//    !!!!! C. Vyzera to vsak, ze ked definujem DP a k nej STATICKE metody GetXXX() a SetXXX() TAK SA CHOVA DP UPLNE PRESNE AKO AP. Dokonca ju IDE VOLAT AJ ZO XAML a FUNGUJE DEDICNOST.
//    !!!!! D. Ale ak k DP nepouzije dvojicu STATICKYCH metod, ale PROPERTY WRAPPER potom DP sa SKUTOCNE CHOVA AKO DP a TEDA JU NIE JE MOZNE POUZIT NA INOM ELEMENT, AKO TOM CO JU DEFINOVAL.
//    !!!!! E. Vyzera to teda, ze AP A DP su UPLNE TO ISTE, akurat pre XAML parser je dolezite CI K NIM PRISTUPUJEM cez property wrapper (vtedy sa chova ako DP - nemozem ju nastavit na inom Element), alebo ak pouzivam dvojicu STATICKYCH metod a vtedy sa chova ako AP - je ju mozne definovat aj na inom Element ako ten, ktory tuto AP DEFINOVAL.
//    !!!!!!! F. JE TO JASNE !!! Klucove SU WRAPRE - NA TOM CI POUZIJE DependencyProperty.Register(), alebo DependencyProperty.RegisterAttached !!! NEZALEZI !!!. Logika je takato.
//       1. Ked mam DP (pristup cez propery wrapper) XAML parser vie praimo na tomto Element volat tuto property, kedze mam objekt Elementu a mozem ho pouzit a volat property.
//       2. DP na DO, ktory ho nedefinuje pouzit nemozem, kedze mam iba property DO, ktory DEFINOVAL DP, ale IN DO, na ktory DP chcem aplikovat !!! NEMA TUTO PROPERTY, TAKZE NEMA !!! CO !!! ZAVOLAT.
//       3. Pri AP (pristup cez STATICKE GetXXX() a SetXXX()) je iny, kedze MAM STATICKE METODY.
//       4. Ak mam aj iny DO na ktorm som AP nedefinoval TAK PRISTUP K STATICKYM METODAM AP-DEFINUJUCEHO DO MAM VZDY - HOLD STATICKE METODY. Teda ich MOZEM ZAVOLAT.
//       5. Cela finta AP je v IMPLEMENTACII GetXXX() a SetXXX(). Tie v tele zavolaju GetValue() a SetValue() nad predanym parametrom a to je OBJEKT DO, KTORY SAM NEDEFNOVAL AP, ALE NAD KTORYM CHCEM AP POUZIT.
//       6. No a kedze v kode GetXXX() a SetXXX() JE SPRAVENE VOLANIE GetValue() a SetValue() nad DO, KTORY NEDEFINUJE, ALE IBA POUZIVA AP TAK SA TAKTO !!!!! SPETNE !!!!! NASTAVI HODNOTA AP NA DO, ktory POUZIVA AP, ALE NEDEFINUJE JU A TYM !!! MAM NASIMULOVANU CINNSOT AP - ZADEFINJEM HODNOTU DP nad INYM DO, AKO TYM, KTORY JU DEFINOVAL.
// 5. Validacia.
//    A. Validacia nema pristup k samotnemu DO iba k novej hodnote, ktoru moze prijat, alebo zamiernut.
//    B. Je volana pri KAZDEJ ZMENEJ hodnoty DP - AJ PRI STARTE PROGRAMU.
//    C. Ak validacia ZLYHA pri XAML parsingu tak hodi Exception a PROGRAM SA ANI NESPUSTI.
//    D. Aj v kode ked nastavim ZLU hodnotu, alebo taku, ktora vo Validacii sposobi exception tak SA VSETKO VRACIA AKO EXCEPTION. Custom exception vratenu vo Validatore mozem zachytit.
//    E. Validacia je proces kedy sa HONDOTA NEMENI iba VALIDUJE.
//    !!! F. Je volena AJ KED NASTAVIM TU ISTU HODNOTU.
// 6. Notifikacia.
//    A. Je volana ked je hodnota DP ZMENENA. Ak nastavim EXISTUJUCU honototu potom sa notifikacia NEVOLA.
//    B. Obsahuje DO OBJEKT a teda ma pristup k VSETKYM ICH PROPERTY a moze s nim LUBOVOLNE PRACOVAT.
//    C. Objekt DependencyPropertyChangedEventArgs nesie info ako o starej tak aj novej hodnote.
// 7. Coerce.
//    A. Umoznuje zmenit hodnotu DP.
//    B. V Coerce mam pristup k celemu DO.
//    C. Vykonava sa PO VALIDACII HODNOTY, avsak ak ju Coerce ZMENI POTOM SA VALIDACIA VYKONA ZNOVA.
//    !!! D. Nemeni sa BASE HODNOTA, Coerce IBA !!! KONVERTUJE TUTO HODNOTU NA NOVU, ALE BASE HODNOTA SA NEZMENI.
//    !!!!! E. Ak dojde k zmene hodoty, ktora ovplyvni Coerce proces nejakej DP POTOM MUSI VOLAT metodu CoerceValue(), ktora VYVOLA Coerce METODU DANEJ DP.
// 8. Shared Properties.
//    A. SP je vlastne to, ze mam VIAC IDENTIFIKATOROV DP, ktora sa odkazuju NA TU ISTU DP.
//    B. Ak teda zmenim na DANOM DO hodnotu DP, alebo HOCKTOREJ na nu sa odkazujucej SP tak SA VLASTNE ZMENA PREMIETNE NA VSTKY DP, kedze MAJU TEN ISTY IDENTITIKATOR.
//    C. Cize naozaj je to iba novy identifikator odkazujuci sa na inu DP.
//    !!! D. Samozrejme, ze pri volani AddOwner() na zaregistrovanie SP musim dat inu triedu ako tu, ktoru som dal pri registrovani povodnej DP.
// !!!!! 9. Pri citani hodnoty DP sa NEROBI CELY PROCES citania a prechodu DP. To by bolo katastrofalne pomale. ????? Vyzera to, ze DP si uklada LOCAL VALUE DP a tu pouziva POKYM SA NEZMENI NASTAVENIM ci uz priamo cez SET, alebo PREDOK PRI DEDICNOSTI. Tuto LOCAL VALUE JE MOZNE ZMAZAT CEZ ClearValue().
//------------------------------------------------------------------------
namespace DependencyPropertiesTestClient
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
		private void OnWriteInheritanceStatus(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			// Tu sa hodnota '-999' zdedi z MFEParent1.
			Debug.WriteLine(string.Format("\tMFEParent1: {0} !",MFEParent1.ToString()));
			Debug.WriteLine(string.Format("\tMFEParent2: {0} !",MFEParent2.ToString()));
			Debug.WriteLine(string.Format("\tMFEParent3: {0} !",MFEParent3.ToString()));
			Debug.WriteLine(string.Format("\tMFEParent4: {0} !",MFEParent4.ToString()));
			Debug.WriteLine(string.Format("\tMFEParent5: {0} !",MFEParent5.ToString()));
			Debug.WriteLine(string.Format("\tMFEParent6: {0} !",MFEParent6.ToString()));
			Debug.WriteLine(string.Format("\tMFEChild1: {0} !",MFEChild1.ToString()));
			Debug.WriteLine(string.Format("\tMFEChild2: {0} !",MFEChild2.ToString()));
			// Tu sa hodnota '-999' zdedi z MLabel2.
			Debug.WriteLine(string.Format("\tMFEChild3: {0} !",MFEChild3.ToString()));
			Debug.WriteLine(string.Format("\tMFEChild4: {0} !",MFEChild4.ToString()));
			Debug.WriteLine(string.Format("\tMFEChild5: {0} !",MFEChild5.ToString()));
			Debug.WriteLine(string.Format("\tMFEChild6: {0} !",MFEChild6.ToString()));
		}
//------------------------------------------------------------------------
		private void OnDelegates1SetOKValue1(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MFEParent11.FEDelegates1=45;
		}
//------------------------------------------------------------------------
		private void OnDelegates1SetOKValue2(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MFEParent11.FEDelegates1=60;
		}
//------------------------------------------------------------------------
		private void OnDelegates1SetWrongValue(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MFEParent11.FEDelegates1=135;
			}
			catch(Exception Ex)
			{
				Debug.WriteLine(string.Format("\tEXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnDelegates1SetExceptionValue(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MFEParent11.FEDelegates1=777;
			}
			catch(Exception Ex)
			{
				Debug.WriteLine(string.Format("\tEXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnWriteDelegates1Status(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			Debug.WriteLine(string.Format("\tMFEParent11: {0} !",MFEParent11.GetFEDelegates1String()));
			//Debug.WriteLine(string.Format("\tMFEParent12: {0} !",MFEParent12.GetFEDelegates1String()));
			//Debug.WriteLine(string.Format("\tMFEParent13: {0} !",MFEParent13.GetFEDelegates1String()));
		}
//------------------------------------------------------------------------
		private void OnDelegates2SetOKValue1(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			MFEParent21.FEDelegates2=45;
		}
//------------------------------------------------------------------------
		private void OnDelegates2SetOKValue2(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			MFEParent21.FEDelegates2=60;
		}
//------------------------------------------------------------------------
		private void OnDelegates2SetWrongValue(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MFEParent21.FEDelegates2=135;
			}
			catch(Exception Ex)
			{
				Debug.WriteLine(string.Format("\tEXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnDelegates2SetExceptionValue(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MFEParent21.FEDelegates2=777;
			}
			catch(Exception Ex)
			{
				Debug.WriteLine(string.Format("\tEXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnWriteDelegates2Status(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("\tMFEParent21: {0} !",MFEParent21.GetFEDelegates2String()));
		}
//------------------------------------------------------------------------
		private void OnDelegates3SetOKValue1(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MFEParent31.FEDelegates3=45;
		}
//------------------------------------------------------------------------
		private void OnDelegates3SetOKValue2(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			MFEParent31.FEDelegates3=60;
		}
//------------------------------------------------------------------------
		private void OnDelegates3SetCoerceWrongValue(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MFEParent31.FEDelegates3=95;
			}
			catch(Exception Ex)
			{
				Debug.WriteLine(string.Format("\tEXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnDelegates3SetWrongValue(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MFEParent31.FEDelegates3=135;
			}
			catch(Exception Ex)
			{
				Debug.WriteLine(string.Format("\tEXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnDelegates3SetExceptionValue(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");

			try
			{
				MFEParent31.FEDelegates3=777;
			}
			catch(Exception Ex)
			{
				Debug.WriteLine(string.Format("\tEXCEPTION: {0} !",Ex.Message));
			}
		}
//------------------------------------------------------------------------
		private void OnDelegates3SetLimitValueTo50(object Sender, RoutedEventArgs E)
		{
			MFEParent31.SetLimit(50);
		}
//------------------------------------------------------------------------
		private void OnDelegates3SetLimitValueTo75(object Sender, RoutedEventArgs E)
		{
			MFEParent31.SetLimit(75);
		}
//------------------------------------------------------------------------
		private void OnWriteDelegates3Status(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("\tMFEParent31: {0} !",MFEParent31.GetFEDelegates3String()));
		}
//------------------------------------------------------------------------
		private void OnSharedSetBaseDPValue1(object Sender, RoutedEventArgs E)
		{
			MFEParent41.FESharedBase=10;
		}
//------------------------------------------------------------------------
		private void OnSharedSetBaseDPValue2(object Sender, RoutedEventArgs E)
		{
			MFEParent41.FESharedBase=20;
		}
//------------------------------------------------------------------------
		private void OnSharedSetBaseReferendedDPValue1(object Sender, RoutedEventArgs E)
		{
			MFEParent41.FESharedReference=30;
		}
//------------------------------------------------------------------------
		private void OnSharedSetBaseReferendedDPValue2(object Sender, RoutedEventArgs E)
		{
			MFEParent41.FESharedReference=40;
		}
//------------------------------------------------------------------------
		private void OnWriteSharedStatus(object Sender, RoutedEventArgs E)
		{
			Debug.WriteLine("");
			Debug.WriteLine(string.Format("\tMFEParent41: {0} !",MFEParent41.GetFESharedString()));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------