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
// 1. Program demonstruje pouzitie Brushes.
// 2. Brushes sa pouzivaju na definovanie Background ci Foreground, ale aj napriklad ako Fill na vyplnannie Shapes.
// !!! 3. Brush dedi z Freezable, takze zmena Brush sa AUTOMATICKY PREMIETNE DO GUI.
// 4. LinearGradientBrush sluzi na vytvorenie gradientu - prechodu medzi farbami. Farebny prechod definujem pomocou GradientStop objektu, kde definujem Offset v intervale <0,1> urcujuci rychlost prechodu a Color definujucu farbu. LinearGradientBrush potom spravi prechod medzi dvoma farbami.
// 5. Pomocou ImageBrush mozem vytvorit Brush z rozlicnych typov images. Ma niekolko zaujimavych properties, ako napriklad Viewbox, pomocou ktoreho mozem spravit vyrez, dalej Stretch, ktory urcuje chovanie sa pri zmene velkosti okna.
// 6. Pomocou ImageBrush je mozne vytvorit aj Tiled pozadie, kde bude pozadie tvorene tapetou vedla seba naskladanych obrazkou. Je mozne vytvorit 2 typy tiled Brush. Proporcne - kde mam konstatny pocet tiles a tie sa rozrahuju podla potreby tak aby zaplnili cely prideleny region ak sa zoomuje okno. Druhou moznostou je fixed-sized tiles, kde tiles maju konstantnu velkost a pri zoomingu sa meni ich pocet.
// 7. Pomocou VisualBrush je mozne REPLIKOVAT CONTENT Elementu. Ak napriklad mam Button s nejakym Content (textom, obrazkom) a chcem ho niekde inde v okne zobrazit (napriklad ako nahlad na vyzor tlacitka) tak pouzijem VisualBrush.
// !!! 8. Dokonca VisualBrush monitoruje zmenu nanho naviazaneho Elementu, takze aj ked dokonca ziska Element Content, co znamena vykrelsenie obdlznika okolo Content tak sa VisualBrush nanho namapovany tiez takto prekresli. Potobne aj pri kliknuti na Button sa nanho namapovany VisualBrush prekresli.
// !!! 9. Pomocou OpacityMask mozem definovat Brush, ktorym definujem Opacity Brush, ktory mozem vytvorit rozlicne vizarne efekty, ako Element, ktory postupne mizne. Je to zavisle od toho aky typ Brush pouzijem. Pri pouziti Brush v property OpacityMask sa akceptuje IBA ALPHA ZLOZKA. Samotna farba nie. Pomocou Alpha zlozky sa urci uroven transparencie.
//------------------------------------------------------------------------
namespace BrushesTest
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
			DynamicBrushes			Win=new DynamicBrushes();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			RadialGradient			Win=new RadialGradient();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			Gradients				Win=new Gradients();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			GradientText			Win=new GradientText();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			ImageBrushes			Win=new ImageBrushes();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			TileTypes				Win=new TileTypes();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			TileFlip				Win=new TileFlip();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick8(object Sender, RoutedEventArgs E)
		{
			VisualBrush				Win=new VisualBrush();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick9(object Sender, RoutedEventArgs E)
		{
			OpacityMask				Win=new OpacityMask();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------