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
// 1. Program demonstruje pouzitie Lines, Polylines a Polygon.
// 2. Line ma properties X1, Y1, X2 a Y2, ktorym definujem velkost line.
// !!! 3. MUSIM DEFINOVAT Stroke, aby bolo Line VIDIET.
// !!! 4. V Canvase mozem definat aj Left ci Bottom a tieto predstavuju bod 0,0 voci ktoremu je pociatocna pozicia Line.
// !!! 5. V inych Panels ako napriklad StackPanel je bod 0,0 urceny podla Elements Flow, teda za posledny Elementom.
// 6. Polyline je spojenie niekolkych ciar za sebou. Jednotlive Points sa ukladaju do property Points.
// 7. Polygon je obdoba Polyline az nato, ze posledny a prvy bod je automaticky spojeny.
// !!! 8. Polygon a Polyline maju zaujimavu property FillRule, ktro mozem pri prekyvajucom sa Polygone, ci Polyline urcit, ktore casti sa budu vykreslovat.
// 9. Pomocou properties StartLineCap a EndLineCap mozem urcit ukoncenie Line a Polyline.
// 10. Pomocou StrokeLineJoin a dalsich propertie mozem pre vsetky Shapes s vynimkou Line urcit ako sa budu vykreslovat sykove body medzi dvoma line. Je tam dost vela options.
// 11. Pomocou properties StrokeDashArray mozem nastavit vzorku pri prerusovanych ciarach. Vzroka mozem mat viacero double hodnotu, pricom vzorkovanie sa udava od hodnoty s indexom urcenym v property StrokeDashOffset. Jednotlive prerusovane fragmenty, mozu mat nastavene konce ciar na ine zakoncenie pomocou property StrokeDashCap.
// 12. Pomocou SnapsToDevicePixels nasatveny na TRUE vypnem efekt anti-aliasing, co moze byt niekedy pri renderovani uzitocne, aby okraje ciar neboli rozmazane.
//------------------------------------------------------------------------
namespace LinesTest
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
			Lines					Win=new Lines();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			Polylines				Win=new Polylines();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			Polygons				Win=new Polygons();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			LineCaps				Win=new LineCaps();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			LineJoins				Win=new LineJoins();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			DashedLines				Win=new DashedLines();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			PixelSnapping			Win=new PixelSnapping();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------