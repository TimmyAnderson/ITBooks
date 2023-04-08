using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using LocalizationTestLibrary;
//------------------------------------------------------------------------
// 1. Program demonstruje lokalizaciu aplikacie.
// 2. Lokalizacia vo WPF sa realizuje velmi jednoducho. KAZDA Culture MUSI MAT VLASNY BAML pre KAZDY Window. Tento je ulozeny v satelitnych assemblies, v subadresaroch aplikacie pomenovanych podla kultury (sk-SK). Cielom je vytvorit takto satelitne assemblies, ktore sa potom prekompiluju a WPF ich v tychto satelitnych assemblies najde.
// 3. Na lokalizaciu je nutne vykonat nasledujuce kroky.
//    A. Do projektu (subor .csproj) doplnit '<UICulture>en-US</UICulture>'. Projekt sa zmeni tak, ze bude vytvarat pre kazdu DLL vlastna satelitna assembly.
//    B. Tie Elements, ktore obsahuje lokalizovatelny text musim oznait pomocou 'x:Uid', aby som odtial vedel automaticky extraktovat tieto texty.
//    !!! C. Na automaticke oznacenie VSETKYCH ELEMENTS vo Windows sluzi prikaz: 'msbuild /t:updateuid LocalizationTest.csproj'. A na zistenie ci vsetky Elements su oznacene zas prikaz: 'msbuild /t:checkuid LocalizationTest.csproj'.
//    !!! D. Pouzijem LocBaml.exe na EXTRAKTOVANIE LOKALIZOVATELNEHO CONTENTU. LocBaml.exe je dstribuovany ako SAMPLE k HELPU. Je ho mozne STIAHNUT cez MSDN HELP, ked vyhladam 'locbaml' a stiahnem tento example. Samozrejme JE HO NUTNE SKOMPILOVAT.
//    !!! E. Pri spusteni LocBaml.exe je ho NUTNE MAT V ADRESARI, KDE JE SKOMPILOVANA DLL.
//    F. Vysledkom extrahovania su subory CSV. Tie da daju citat pomocou Excel - POZOR na jazykovu veziu. Cesky Excel to zobrazi zle, kedze on ma ako odelovac ';' a nie ','.
//    G. Po editacia CSV suborov moze spusti pomocou LocBaml.exe spetnu regeneraciu a vytvorenie DLL z editovanych CSV suborov.
//    H. LocBaml.exe na regeneraciu kniznicu potrebuje aj originalne satelitne DLL v ktorych zmeni hodnoty z CSV suborov. Takisto musim specifikovat Culutre novovytvtorenej DLL.
//    I. LocBaml.exe MUSI BYT SPUSTANY z Bin\Debug a este predtym je treba vytvorit lokalizovany adresar (sk-SK). Potom je uz potrebne spusit LocBaml.exe, napriklad takto: 'locbaml /generate en-US\LocalizationTest.resources.dll /trans:Edited_LocalizationTest.resources.CSV /cul:sk-SK /out:sk-SK'.
//    J. Vysledkom su SATELITNE ASSEMBLIES S LOKALIZOVANYM OBSAHOM.
//    !!! K. Ak chcem takyto preklad pouzit musim nastavit pre Thread Culture. Najlepsie je to robit na zaciatku. Napriklad v Apllication contructor.
// !!!!! 4. Ak zmenim Culture v konstruktore Window TAK TOTO WINDOW NEBUDE LOKALIZOVANE. Je to logicke, kedze v kostruktore je uz nahranna satelitne DLL s povodnym jazykom. Culture je treba menit este v Application, aby vsetko bolo lokalizovane.
// !!!!! 5. Lokalizovat sa da VSETKO V XAML. Presnejsie KAZDA PROPERTY, KTORA MA NASTAVENY [LocalizabilityAttribute] alebo typ property ma tento atribut. Teda aj OBRAZKY v Image Element. (Image.Source sice nema atribut, ale typ ImageSource ano.) Avsak zmeneny obrazok MUSI BYT V ASSEMBLY. Tu napriklad mam 'HappyFace.jpg' pre 'us-US' a 'SadFace.jpg' pre 'sk-SK'.
// !!!!! 6. Content, ktory potrebujem loaklizovat a NIE JE PRAIMO V XAML, ale V KODE mozem lokalizovat nasledovne.
//    A. Content ulozim do <Window.Resource> ci <Application.Resource>.
//    B. V kode vytihanem tento Resource a pouzijem.
//------------------------------------------------------------------------
namespace LocalizationTest
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
		private void OnStartDialog(object Sender, RoutedEventArgs E)
		{
			SubWindow					Win=new SubWindow();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnStartDialogFromOtherAssembly(object Sender, RoutedEventArgs E)
		{
			SubWindowFromOtherLibrary	Win=new SubWindowFromOtherLibrary();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------