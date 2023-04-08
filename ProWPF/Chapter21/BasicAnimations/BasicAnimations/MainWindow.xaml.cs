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
// 1. Program demonstruje pouzitie animacii vyvolavanych z C# kodu.
// 2. Na rozdiel od benych animacii zalozenych v prekreslovani jednotlivych Frames je WPF Animation zalozeny na ZMENE DP.
// 3. Teda WPF Animation je vlastne zmena nejakej DP v danom case. Toto ma samozrejme viacero ombedzeni. Nad danou DP je mozne realizovat iba jednu animaciu, nie je komplexnejsie veci ako pridavat Elements a tak podobne.
// !!! 4. Animovat je mozne KAZDY ELEMENT, pretoze KAZDY Element implementuje rozhranie IAnimatable. Teda KAZDY OBJEKT, KTORY IMPLEMENTUJE IAnimatable je ANIMOVATELNY. Samozrejme animovatelna je JEHO NIEKTORA JEHO DP.
// !!! 5. Nato aby som mohol animovat DP musim specifikovat priebeh animacie. Ten zavisi od toho AKEHO TYPU JE DP. Pre kazdy TYP DP musi byt SPECIALNA TRIEDA, ktora IMPLEMENTUJE ANIMACIU DP.
// 6. Existuju 3 typy PRIEBEHOV ANIMACIE DP, ktore su definovane meno triedy, ktora ju implementuje (XXX - je meno typu DP).
//    A. XXXAnimation - implementuje interpolacnu zmenu DP. Teda zmenu z hodnoty From az do To.
//    B. XXXAnimationUsingKeyFrames - implementuje zmenu DP na danu hdonotu. Teda definujem hodnotu na ktoru sa DP ma zmenit.
//    C. XXXAnimationUsingPath - implementuje zmenu DP podla priebeho definovanom v Path.
// !!! 7. Plati, ze KAZDY Typ, ktory je podporovany pre animaciu ma implementovany XXXAnimationUsingKeyFrames. Ciselne typy okrem nej este maju aj XXXAnimation a 3 maju aj XXXAnimationUsingPath.
// 8. Postup pri realizovani animacii je nasledujuci.
//    A. Definujem priebeh animacie, teda triedu (XXXAnimation, XXXAnimationUsingKeyFrames, XXXAnimationUsingPath).
//    B. Pre Element, ktoreho DP chcem animovat volam metodu BeginAnimation(), kde jej pradam instanciu triedy definovanu v bode A.
// 9. Pri interpolacnej animacii definujem property From, To a By na definovanie animacie. Niekedy From nie je vhodne definovat, ak napriklad chcem pri kazdom stalceni tlacitka ho o torchu viac roztiahnut. Potom From definovat nemusim a vychadza sa z aktualnej hodnoty DP (tu Width). Ak nedefinujem To potom sa ako hodnota To nastavavi hodnota DP, ktora zsa vypocita z hodnoty DP bez alikovania animacie. Samozrejme toto ma zmysle iba ked uz nejaka animacia bezi, inak sa nestane nic a animacia nespusi, kedze From a To su rovnake.
// !!! 10. Snimkovanie Animation je vypocitavana WPF AUTOMATICKY. Vypoctava sa z From a To hodnot a snimkovacej frekvencie, ktora je default na 60 frames per second.
// 11. Nad roznymi DP daneho Elementu je moze SUCASTNE robit VIAC ANIMACII.
// !!!!! 12. Ked animacia skonci VYSLEDNA HODNOTA ANIMACIE SA NADALEJ UPLATNUJE. Teda DP OSTANE NA HODNOTE To. DOKONCA AJ KED POTOM ZMENIM V KODE HODNOTU DANEJ DP TAK SA TAK REALNE NEZMENI, LEBO ANIMACIA MA PREDNOST. Existuje viacero rieseni ako to zmenit. Cez property AutoReverse sa moze animacia vratit do povodnej hodnoty. Alebo nastavim animaciu, kde nenastavim To a tym padom sa bude From==To a potom uz je mozne zmenit hodnotu DP. Dalsim riesenim je FillBehavior animacie na Stop, cim sa vysledna hodnota po skonceni Animacie nezapise do DP. Poslednym riesenim je zachytit event Animation.Completed, ktory je volany ked animacia skonci a tu poslanim NULL do metody BeginAnimation() zrusim efekt animacie na DP.
// 13. Pomocou properties AccelerationRatio a DecelerationRatio mozem urcit v ktorej pozicii <0,1> budu zrychlovany a spomalovany beh animacie.
// 14 Pomocou property RepeatBehavior mozem urcit pocet opakovani, alebo cas ako dlho bude clekovo trvat animacia, pricom ak presiahne cas jednej iteracie tak sa opakuje.
//------------------------------------------------------------------------
namespace BasicAnimations
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
			SimpleAnimation				Win=new SimpleAnimation();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			SimultaneousAnimations		Win=new SimultaneousAnimations();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			AnimationLifetime			Win=new AnimationLifetime();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			AccelerationDeceleration	Win=new AccelerationDeceleration();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			RepeatBehavior				Win=new RepeatBehavior();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------