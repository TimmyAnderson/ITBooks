using System;
using System.Collections.Generic;
using System.Linq;
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
// 1. Program demonstruje 3D animaciu.
// !!! 2. Zaklanym elementom v 3D animacii je MeshGeometry3D.
// 3. MeshGeometry3D je MESH. Teda obsahuje koleckiu Positions (vertices),  TriangleIndices, Normals a TextureCoordinates. Je to teda suhrn triangles, tvoriacich jedno teleso.
// !!! 4. Objekt GeometryModel3D obsahuje model objektu. Je to vlastne Mesh (ulozeny v property Geometry), ktory ma predny a zadny material (properties Material a BackMaterial).
// !!! 5. Za material mozem pouziti niekolko typov materialov lisiacich sa sposobom osvetelnia.
//    A. DiffuseMaterial - vyuzitie difuzneho svetla.
//    B. SpecularMaterial - vyuziva sa aj Specular zlozka svetla.
//    C. EmissiveMaterial - material je ma aj vlastnu emisnu zlozku svetla - teda vyzarovanie.
//    D. MaterialGroup - umoznuje skladat jednotlive zlozky svetla.
// 6. Pokial BackMaterial nenastavim tak pri pohlade zozadu objekt zmizne.
// !!! 7. Svetlo je tiez zdedny z Model3D a preto ho mozno pripavat tak ako MeshGeometry3D do ModelVisual3D. Mozem pouzit naraz aj viac svetiel a mam k dispozicii 4 typi svetiel.
//    A. DirectionalLight - smerove svetlo - emulacia Slnka.
//    B. PointLight - bodove svetlo - ziarovka.
//    C. SpotLight - konicke svetlo - baterka.
//    D. AmbientLight - klasicke ambientne svetlo, teda svetlo pozadia. Minimalne svetlo objektu.
// 8. Kamera sa nastavuje pomocou property Viewport3D.Camera. Kameru urcuje ako sa bude premietat 3D scena na 2D obraz. Vo WPF existuju 3 druhy kamier.
//    A. PerspectiveCamera - klasicka perspektiva.
//    B. OrthographicCamera - na rozdiel od perspektivy vzdialenejsie objekty nie su mensie.
//    C. MatrixCamera - pouziva sa zvycajne pri migracii scen z DirectX.
// 9. Popis objektov pouzivanych v 3D.
//    A. MeshGeometry3D - ZAKLADNY OBEKT. Reprezentuje Mesh. Teda postupnost Vertices, Indices, Normals a Texture Coordinates.
//    B. GeometryModel3D - !!! ZDEDENY Z Model3D. OBALUJE MESH (MeshGeometry3D) a pridava k nemu Front a Back Material.
//    C. Light - !!! ZDEDENY Z Model3D. Reprezentuje svetlo.
//    D. Model3DGroup - !!! ZDEDENY Z Model3D. Umoznuje ukladat KOLECKIU objektov Model3D, teda GeometryModel3D, Light, alebo Model3DGroup a vytvarat tak jednu skupinu. MOZEM NAD NOU ROBIT ANIMACIE A TRANSFORMACIE.
//    E. ModelVisual3D - kolekcia Visual3D objektov. JE NAD NOU MOZNE REALIZOVAT HitTest, Transformacie a podobne. Kedze moze obsahovat viacero Meshes tak moze reprezentovat celu komplexnu scenu.
//    F. Viewport3D - kolekcia Visual3D objektov. Sluzi na zobrazovanie sceny.
// 10. Pre optimalnu funkcionalitu 3D grafiky je nutne minimalizovat pocet Meshov ako aj pocet ModelVisual3D.
// 11. SpecularMaterial a EmissiveMaterial sa pouziva zvycajne spolu s DiffuseMaterial, aby zmenili posobenie DiffuseMaterial, ktory je podkladom pre zmeny tymito dvoma materialmi.
// !!! 12. Na pouzitie textury je potrebne realzovat tieto kroky.
//    A. V materiali pouzit iny Brush, ako SolidColorBrush (napriklad ImageBrush).
//    B. V Mesh definovat TextureCoordinates.
// !!!!! 13. Ak chcem mat objekt, ktory ma viacero materialov (textur) MUSIM VYTVORIT VIACERO MESHES.
// !!! 14. Takisto je mozne aplikovat podobne aj VIDEO ako texturu a to taktiez definovanym Texture Coordinates a pouzitim VisualBrush a MediaElement.
// 15. Transformacie je mozne robit klasicky pomocou matic. Transformacie je mozne aplikovat na tieto typy objektov.
//    A. Model3D - transformujem jeden mesh, alebo skupinou meshov ak sa jedna o Model3DGroup.
//    B. ModelVisual3D - transformujem celu scenu.
//    C. Light - transformujem svetlo.
//    D. Camera - transformujem kameru.
// 16. Hit Testing sa v 3D scene sa robit troma sposobmi.
//    A. Zachytavat udalosti Mouse na Elemente Viewport3D a potom volat metodu VisualTreeHelper.HitTest() na zistenie, ktory Element mal Hit.
//    B. Vytvorit CUSTOM 3D Element, zdedeny z UIElement3D.
//    C. Vlozit do sceny namiesto ModelVisual3D objekt ModelUIElement3D, ktory poskytuje Mouse handling metody.
// !!!!! 17. Ak chcem do 3D sceny zaradi 2D Element potom POUZIJEM Viewport2DVisual3D, ktora WRAPRUJE 2D Element a moze byt hodena do 3D sceny. Takto wraprovany Element JE PLNE FUNKCNY.
// !!!!! 18. V pripade pouzitia Viewport2DVisual3D sa tymto Elemntom nahradza ModelVisual3D. Obsahuje okrem Geometry, kde definujem Mesh, Material ci Transformation aj KLUCOVY prvok Visual. PRAVE SEM SA UKLADA 2D ELEMENT.
// !!!!! 19. Kedze Element wraprovany Viewport2DVisual3D sa nanasa ako TEXTURA JE POTREBNE DEFINOVAT TextureCoordinates.
//------------------------------------------------------------------------
namespace Graphics3DTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:Window
	{
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			OneTriangleMesh				Win=new OneTriangleMesh();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			CubeMesh					Win=new CubeMesh();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click3(object Sender, RoutedEventArgs E)
		{
			PersonIn3D					Win=new PersonIn3D();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click4(object Sender, RoutedEventArgs E)
		{
			Materials					Win=new Materials();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click5(object Sender, RoutedEventArgs E)
		{
			TextureMapping				Win=new TextureMapping();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click6(object Sender, RoutedEventArgs E)
		{
			VideoIn3D					Win=new VideoIn3D();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click7(object Sender, RoutedEventArgs E)
		{
			C2DElementsIn3D				Win=new C2DElementsIn3D();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click8(object Sender, RoutedEventArgs E)
		{
			AnimatedRing				Win=new AnimatedRing();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click9(object Sender, RoutedEventArgs E)
		{
			TrackballRing				Win=new TrackballRing();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void Button_Click10(object Sender, RoutedEventArgs E)
		{
			HitTesting					Win=new HitTesting();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------