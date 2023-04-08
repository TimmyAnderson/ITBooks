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
// 1. Program demonstruje pouzitie Visuals.
// !!! 2. Objekt Visual tvori BASE pre vsetky Elements a umoznuje renderovat ich obsah.
// !!! 3. Vsetky Shapes ci Elements pouzivaju prave Visuals na rendering.
// !!! 4. Visual ma viacero potomkov. Na kreslenie sa pouziva DrawingVisual. Jeho metoda RenderOpen() vracia DrawingContent do ktoreho mozem pomocou mnozstva metod kreslit. Ked skoncim tak zavolam metodu DrawingContext.Close(). Takyto DC je potom pouziti na rendering Elementu.
// !!!!! 5. Nato aby som mohol renderovat Visual je potrebne vykonat niekolko nasledujucich krokov.
//     A. Pre kazdy Visual volat AddVisualChild() a AddLogicalChild() na pridanie do vizualneho a logickeho stromu.
//     B. Pretazit property VisualChildrenCount, ktora vrati pocet renderovanych Visuals.
//     C. Pretazit metodu GetVisualChild(), ktora vrati dany Visual podla indexu.
//     !!! D. Najlepsie je na tento ucel implementovat vlastnu triedu, ktora bude drzat informaciu o vsektych Visuals.
// !!! 6. Ak zaradim Visual do VisualTree potom pomocou jeho metody HitTest() je mozne zistit ci mam na danom bode nejaky hit - teda nejaky Visual. Ma viacero pretazenych verzii, vratanej tej, ktora pomocou Callback umoznuje vratit zoznam vsetkych Visuas, ktore boli trafene (hit) nie iba toho najvrchnejsieho.
// !!!!! 7. Po metode RenderOpen() a pouziti metod kreslenia NEDOCHADZA K VYKRESLOVANIU Visual FYZICKY NA OBRAZOVKU, ALE IBA SA UKLADAJU RENDEROVACIE PRIKAZY, KTORE SA V PRIPADE POTREBY, KED WPF ZISTI, ZE JE TREBA RENDEROVAT SCENU ODTIAL VYKRESLIA A RENDERUJU. TEDA WPF SI MANAGEUJE KEDY SA BUDE RENDEROVAT.
// !!!!! 8. KLUCOVE TEDA JE, ZE Invalidacia OBRAZOVKY NEMA ZMYSEL, KEDZE O TO SA STARA WPF. JA KRESLIM IBA VIRTUALNE NIE FYZICKY, ked pouzivam metody DrawingContext.
//------------------------------------------------------------------------
namespace VisualsTest
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
			SimpleVisuals				Win=new SimpleVisuals();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------