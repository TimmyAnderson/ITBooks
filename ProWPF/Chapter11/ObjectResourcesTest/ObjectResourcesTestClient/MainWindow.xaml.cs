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
// 1. Program demonstruje pouzitie Object Resources.
// 2. OR mozem definovat NA KAZDOM ELEMENTE a plati medzi nimi dedicnost, kde v danom Elemente mozem pouzit svoje OR ako aj vsetko OR definovane v parent Elements.
// !!! 3. OR vsak MUSI BYT DEFINOVANA PRED POUZITIM. A to dokonca aj v ramci Elementu, kedy naprrv musim defionovat OR a az potom Content, ak v Content tento OR vyuziva.
// 4. Ak sa na urovni Window nenajde OR tak sa hlada v Application class, alebo System Resources.
// 5. Z kodu mozem pristupovat k lubovlnej OR cez property Resources, ktory ma KAZDY ELEMENT.
// !!! 6. Samozrejme ked pouzivam Resources priamo tak mam prstup iba k danej LOKALNEJ KOLEKCII a dedicnost sa neuplatnuje. Ak chcem ziskat OR s vyuzitim APLIKACIE DEDICNOSTI OR musim pouzit metodu FindResource(), ktore je schopna najst OR aj v parent Elements ako v pripade XAML.
// !!! 7. OR mozu byt staticke, alebo dynamicke. Dynamicke su take, ze ked ich v kode zmenim TAK SA ZMENA PREMIETNE DO GUI.
// !!!!! 8. AJ STATICKY RESOURCE moze SPOSOBIT ZMENU GUI. A to vtedy ked je dana trieda ZDEDENA Z Freezable, alebo FreezableCollection. Tento predok zabezpecuje AUTOMATICKY UPADTE GUI pri zmene OR.
// 9. Nastavenim 'x:Shared' danej OR sposobim, ze sa nebude pouzivat tak ista instancia obejktu, ale v kazdom pouzitii sa vytvori jej nova kopia. V niektorych pouzitiach je to vyhodne. Napriklad ked do Resources dam Element. Vtedy sa musi vytvorit klon, aby 2 Elements mohli mat ineho predka.
// !!!!! 10. Aj ked som implementoval vlastny Freezable objekt, tak mi automaticky neupadetoval GUI. ????? Dovod podla je v tom, ze nato by muselo byt GUI pripavene. V pripade Brush napriklad jeho DP maju zaregisrovanu metodu pri zmene DP a tam pravdepodobne zabezpeci zmenu GUI.
// !!! 11. Systemove Resources su ulozene v triedach: SystemColors, SystemFonts a SystemParameters. Tieto triedy maju STATICKE PROPERTIES typu ResourceKey (napriklad SystemColors.WindowTextBrushKey), ktore mozuem pouzit ako Resource. Tieto systemove Resources BY MALI BYT MAPOVANE DYNAMICKY (DynamicResource), aby zmeny systemovych settings pocas behu aplikacia sa hned aj prejaili bez nutnosti restartovat aplikaciu.
// !!! 12. Resources mozem ulozit do ResourceDictionary co je specialny XAML, ktory obsahuje iba ResourceDictionary. Tento potom mozem do existujuceho Resources integrovat pomocou property MergedDictionaries.
// 13. V pripade, ze chcem pouzit OR z jednej DLL v inej DLL exisuju dve sposoby ako to spravit.
// !!! 14. Sposob cislo 1 je nasledujuci.
//     A. V separatnej DLL definujem jednu, alebo viacero ResourceDictionaries, kde definujem svoje OR.
//     !!! B. Vytvorim adresar s menom 'Themes'. MENO JE !!! POVINNE.
//     !!! C. V adresari vytvorim ResourceDictionary s menom 'generic.xaml'. AJ TOTO MENO JE POVINNE.
//     D. Do assembly prihodim DUMMY TRIEDU, ktore identifikator sluzi na identifikaciu OR.
//     E. Ako KEY pre KAZDY RESOURCE MUSIM pouzit ComponentResourceKey, kde v property TypeInTargetAssembly definujem DUMMY TRIEDU zadefinovanu v bode D.
//     F. Pri definovani ciest (k obrazkom, alebo ResourceDictionaries) je NIEKEDY nutne pouzivat FULL PATH (s definovanim assembly) A NIEKEDY SHORT PATH aby pri pristup z inej assembly som sa k danemu obrazku (resource) vedel dostat. Viac info v MyTestDictionary.xaml a Generic.xaml.
//     G. Teraz mozem pouzit OR v inej assembly, ale MUSIM POUZIT DYNAMIC RESOURCE NIE STATIC RESOURCE.
// !!! 14. Sposob cislo 2 je nasledujuci.
//     A. Rozdiel orpoti sposobu 1 je, ze v tej DUMMY TRIEE zadefinujem pre KAZDY RESOURCE STATIC PROPERTY, ktora vytiahne Resource.
//     B. V inej assemlly potom uz staci iba k tejto property pristupit a cez Dynamic Resource ju namapovat.
//------------------------------------------------------------------------
namespace ObjectResourcesTestClient
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
			CustomResources				Win=new CustomResources();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			InheritanceResources		Win=new InheritanceResources();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{	
			StaticDynamicResources		Win=new StaticDynamicResources();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			ResourceDictionaryWindow	Win=new ResourceDictionaryWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			SharedResourcesWindow		Win=new SharedResourcesWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------