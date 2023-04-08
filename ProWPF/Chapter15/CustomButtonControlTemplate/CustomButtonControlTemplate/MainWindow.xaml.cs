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
// 1. Program demonstruje pouzitie Custom Control Template aplikovanej na Button.
// 2. CT sa uklada zvycajne do Resource a aplikuje sa priradenim na Property Template, ktoru ma kazdy Control.
// 3. Kedze idem implemetnovat Button tak musi mat nejaky Background a Border. Najlepsie je na to pouzit Border Element.
// !!! 4. Ak chcem aby Button mohol drzat aj Content tak potrebujem vlozit do CT ContentPresenter. Nastavim aj RecognizesAccessKey, aby Button mohol mat Access Key.
// !!! 5. Kedze implementuje CT mnohe veci musim implementovat sam, kedze v standardnych Buttons to robi prave CT. Jednou z nich je aj Padding. O Margin Buttonu sa stara Parent Element (napriklad StackPanel), ale o Padding (HoriontalAlligment, VerticalAlligment) sa stara ContentPresenter. Padding sa da SPRAVIT TRIVIALNE tak, ze namapujem pomocou TemplateBinding (DA SA POUZIT IBA V TEMPLATE) Padding na ContentPresenter.Margin. Teda vlastne odsadim ContentPresenter OD Border a MAM IMPLEMENTOVANU FUNCKIONALITU Padding.
// !!!!! 6. V CT sa pouziva TemplateBindding na viazanie PROPERTIES CT A PROPETIES CONTROLU, KTORY BUDE POUZIVAT TENTO CT. Je to teda SPECIALIZOVANA VERIZA BINDINGU pre pouzitie VYLUCNE v CT.
// !!! 7. Template Bindding je OneWay binding a je urcena pre pouzitie specialne v CT.
// !!! 8. Na prekreslenie Button pri kliknuti, disable, ci trebars ak doplnim aj zmenu vyrozu Button pri prechode myskou, tak na realizaciu totho vsetkeho je idealne pouzit Triggers. Pomocou nich mozem elegantne A BEZ POUZITIA KODU renderovat Button pri tychto akciach.
// !!! 9. Na symbolizovancie ziskania Focus sa pouzije skryty Rectangle, ktory je na pozadi za ContentPresenter. Obe hodim na Grid, cim dosiahnem aby lezali na sebe, ContentPresenter na Rectangle.
// !!! 10. Funkcionalitu Disabled urobim tak, ze vytvorim Trigger an property IsEnabled. AVSAK MUSI BYT AKO POSLEDNY Trigger, ABY PREBIL OSTATNE, ktore by tiez mohli zmenit vyzor Button.
// !!! 11. Najlepsie ako zistit co by mala CT robit pre dany Element je preskumat standardnu CT pomocou prezeracat CT, ktory bol ukazany v tejto kapitole.
// !!! 12. Ak chcem pouzit na CT vlastny Style potom je vyhodne definovat novy CT a za nim az Style, pricom Style nastavi AP Control.Template na CT, KTORY SOM PREDTYM VYTVORIL. Jednou nevyhodou faktu, ze Style nie je priamo sucastou CT je to, ze v Style nemozem pouzit property TargetName na nastavovanie properties hlbsie v strome CT.
// !!! 13. Skinning sa robi tak, ze vytvorim viacero variant CT, ktore ulozim najlepsie do ResourceDictionary a programovo potom zmenim hodnotu tohto ResourceDictionary v Resource Collection na novy CT, ci Skin. Nato aby zmena prebehla vsak musi byt Dany CT ci Skin mapovany na Type, alebo musim pouzit DynamicResource.
// !!!!! 14. Ak vytvaram ResourceDictionary, tento RD MOZE MAT WRAPPER TRIEDU, zededenu z ResourceDictionary, ktora tento ResourceDictionary implementuje. Aby to fungovalo musim nielen doplnit meno triedy s rovnakym nazom ako ma XAML a koncovkou .CS (VS to automaticky nerobi), ale aj doplnit x:Class s menom triedy do deklaracie ResourceDictionary.
// !!! 15. Aj pre ItemControls je mozne vytvorit CT. Situacie je tu zlozitejsia, ze CT sa uplantnuje na samotny Element, nie vsak na jeho Items. Ak chcem spravit specialnu CT aj pre Items, potom napriklad pre ListBox musim vytvorit aj CT pre ListBoxItem. Podobne mozem definovat aj CT pre ScrollBar.
// !!! 16. CT a Style mozem definovat aj pre Window. Standardny Window je rozdeleny na 3 rows. V 1. je Title, v 2. samotny content okna s Elementom AdornerDecorator a 3. obsahuje Footer, kde sa uklada zvycajne tlacitko na zvecsenie okna. AdornerDecorator sluzi na zobrazenie Drag and Drop ikony, Error indicator, focus a tak podobne.
// !!!!! 17. Pri vytvarani Custom Window CT pouzivam C# Code ako sucast ResourceDictionary, ktory obsahuje prave CT a Style Window. Je to ELEGANTNA FINTA AKO PRIHODIT DO Style, ci CT CUSTOM C# CODE. NEVYHODOU je, ze v tomto C# Behind Code NEMOZEM POUZIT 'this' keyword. Nastastie je mozne namiesto neho pouzit Element.TemplatedParent. Ten moze castovat na Window a pouzivat jeho properties.
//------------------------------------------------------------------------
namespace CustomButtonControlTemplate
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
			SimpleTemplate			Win=new SimpleTemplate();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
        private void OnClick2(object Sender, RoutedEventArgs E)
        {
			TemplateWithStyle		Win=new TemplateWithStyle();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
        private void OnClick3(object Sender, RoutedEventArgs E)
        {
			Skinning				Win=new Skinning();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
        private void OnClick4(object Sender, RoutedEventArgs E)
        {
			ItemsControlTemplate	Win=new ItemsControlTemplate();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
        private void OnClick5(object Sender, RoutedEventArgs E)
        {
			CustomWindow			Win=new CustomWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------