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
// 1. Program demonstruje pouzitie Paths a Geometries.
// !!! 2. Path obsahuje klucovu property Data, ktora je typu Geometry. Do nej je mozne ulozit JEDNU GEOMETRY - teda objekt typu Geometry. Tym, ze Geometries je mozne kombinovat tak je mozne do jednej Path vlozit niekolko Geometries.
// !!! 3. Path obsahuje properties Stroke a Fill urcujuce AKO SA BUDE VYPLNAT Geometry. Geometry tieto properties NEMA.
// !!! 4. Kedze Geometry NEMA Stroke a Fill ak chcem kombiovat Geometries rozlicnej farby MUSIM POUZIT VIAC PATHS.
// !!! 5. Teda Geometry DEFINUJE SHAPE a Path VYKRESLUJE A VYPLNA TENTO SHAPE.
// 6. Triedy Path a Geometry su zdedene z Freezable a teda zmena ich properties sa automaticky premietne do GUI.
// 7. Geometry ma property Transform pomocou, ktorej je mozne aplikovat transformacie na danu Geometry.
// 8. Vypocet velkosti Geometry sa robi este v Layout faze, takze MA VPLYV NA UMIESTNENIE Elements.
// 9. Zakladne Geometries su: LineGeometry, RectangleGeometry a EllipseGeometry.
// !!! 10. GeometryGroup umoznuje kombinovat naraz viacero Geometries do jednej Geometry. Ma property FillRule, ktorou sa urcuje pri prieniku viacerych Geometries ktora cast bude vyplnena a ktora nie.
// !!! 11. GeometryGroup umoznuje teda obsahovat viacero Geometries (ciar, kriviek, obdlznikov, ci elips) a kombinovat ich navzajom.
// !!! 12. Pomocou GeometryGroup.FillRule je mozne vyrezat casti jednej Geometry z inej, ale sirsie moznosti kombinacie Geometries NEMA. Nato treba pouzit CombinedGeometry.
// !!! 13. CombinedGeometry poskytuje skrze svoju property GeometryCombineMode kombinovat PRAVE 2 Geometries.
// !!! 14. CombinedGeometry.GeometryCombineMode ma nasledujuce 4 mody umoznujuce kombinaciu DVOCH Geometries.
//     A. Union - zjednotenie ploch 2 Geometries.
//     B. Intersect - prinik dvoch 2 Geometries.
//     C. Xor - operacia XOR nad 2 Geometries. Teda zjednotenie - prienik.
//     D. Exclude - odcitanie Geometry_1-Geometry_2.
// 15. PathGeometry je najkomplexnejsia Geometry umoznujuca definovat krivky. Klucova property je Figures do ktorej ukladam kolekciu objektov PathFigure. Kazdy objekt PathFigure ma okre StartinPoint aj klucovu property Segments do ktorej ukladam segmenty ciary, alebo krivky a ta vytvara priebeh samotnej krivky. Vtip je v tom, ze do Segments ukladam kolekciu objektov zdedenych z PathSegment. No a sem patria triedy ako LineSegment, ArcSegment, BezierSegment ci QuadraticBezierSegment (a ich PolyXXX verzie), ktore umoznuju kreslit krivky vratane Bezierovych kriviek.
// !!! 16. PathGeometry obsahuje 1, ALEBO VIACERO obejkto PathFigure, kde KAZDY definuje otvoreny, alebo uzatvoreny polynom (ciaru, krivku, bezierovu krivku).
// !!! 17. PathFigure obsahuje KLUCOVU PROPERTY Segments, kde definujem SEGMENTY POLYNOMU. Okrem toho ma property IsClosed, IsFilled a StartPoint udavajuci pociatocny bod polynomu.
// !!! 18. Property PathFigure.Segments oabhuje KOLEKCIU obejtov zdedenych z PathSegment, medzi ktorymi su: LineSegment, ArcSegment, BezierSegment, QuadraticBezierSegment a ich PolyXXX verzie.
// !!!!! 19. SKLADANIM SEGEMNTOV VYTVARAM POLYNOM.
// 20. Kedze PathGeometry je znacne rozsiahla na zapis je mozne pouzit aj skratenu syntax nazyvanu Geometry Mini-Language, ktora pomocou jednoznakovych prikazov v property Data triedy Path.
// 21. Geometry objekty je mozne pouzit aj v property Clip Elementu. Jej nastavenim mozem velkost a tvar Elementu orezat na bizarny tvar.
//------------------------------------------------------------------------
namespace PathAndGeometriesTest
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
			SimpleGeometries			Win=new SimpleGeometries();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			DynamicGeometry				Win=new DynamicGeometry();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			GeometryGroup				Win=new GeometryGroup();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			CombiningShapes				Win=new CombiningShapes();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			SimpleArc					Win=new SimpleArc();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			BezierCurve					Win=new BezierCurve();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			MiniLanguage				Win=new MiniLanguage();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick8(object Sender, RoutedEventArgs E)
		{
			Clipping					Win=new Clipping();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick9(object Sender, RoutedEventArgs E)
		{
			ClippingWithViewbox			Win=new ClippingWithViewbox();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick10(object Sender, RoutedEventArgs E)
		{
			PathGeometry				Win=new PathGeometry();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------