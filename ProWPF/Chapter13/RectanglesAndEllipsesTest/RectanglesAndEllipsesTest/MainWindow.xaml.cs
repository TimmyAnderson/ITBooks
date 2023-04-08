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
// 1. Program demonstruje pouzitie Rectangles a Ellipses.
// !!! 2. Rectangle a Ellipse su zdedene zo Shape a ten FrameworkElement a teda maju VSETKY VLASTNOSTI Elements. Su to Elements a teda sa na nich da aplikovat napriklad dedicnost Elements.
// !!!!! 3. Ak nezadefinujem Stroke a Fill tak Ellipse a Rectangle NEBUDU VIDITELNE.
// 4. Rectangle definuje 2 properties: RadiusX, RadiusY, ktore urcuje vykrojenie Rectangle v rohoch.
// 5. Pokial nezadefinujem Height a Width potom je velkost Rectangle a Ellipse definovany jej Containerom. V pripade StackPanel je to 0, pretoze StackPanel sa prisposobuje velkosti svojho obsahu. V pripade Grid sa zas roztiahne do sirky celeho cell.
// 6. Velmi vhodne je Shapes umiestnovat do Canvas Element, kde moze definovat explicitnu poziciu umiestnania Shape.
// !!! 7. Kedze pri kresleni do Canvas musim zadefinovat velkosti Shapes tak pri zoomovani to sposobuje problemy, kedze tieto Shapes sa nezoomuju.
// !!!!! 8. Riesenim vlozenie Canvas do Viewport Element, ktory zabezpecuje AUTOMATICKY ZOOMING na zaklade pociatocnej velkosti Shapes a proporcne ich roztahuje.
// !!!!! 9. Pri tomto pouziti vsak JE TREBA NA Viewport zadefinovat VELKOST (Width, Height). Je to preto, lebo Viewport ma IBA JEDEN Child Element A OD JEHO POCIATOCNEJ VELKOSTI ODVAZDA ZVECSENIE CI ZMENSENIE. Cize ked dam ako Child Canvas (najbeznejsia moznost) tak MUSIM DEFINOVAT JEHO VELKOST.
//------------------------------------------------------------------------
namespace RectanglesAndEllipsesTest
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
			SimpleRectanglesAndEllipses		Win=new SimpleRectanglesAndEllipses();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			RoundedRectangles				Win=new RoundedRectangles();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			Sizing							Win=new Sizing();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			ViewportCanvas					Win=new ViewportCanvas();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------