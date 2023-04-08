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
// 1. Program demonstruje pouzitie animacii na niektore properties Elements.
// 2. Velmi casto sa animacia pouziva v spolupraci s transformaciami, kde je mozne vytvorit efekty rotacie, posunov a podobne prave pomocou animacii.
// !!! 3. Ak pouzivam kombinovanu animaciu cez TransformGroup tam mozem pomocou operatora [] v XAML pristupovat k VSETKYM subtransfromaciam.
// 4. Podobne zaujimave efekty je mozne docielit aj animaciou Brushes.
// !!! 5. PointAnimation je animacia umoznujuca animovat box X a bod Y sucastne, akoby bezali 2 animacie.
// 6. UsingKeyFrame animation je animacia, kedy definujem pozicie animacie. Zatial co pri linearnej animacii kontinualne rastla hodnota z jednej pozicie do dalsej a mohol som urcite iba zaciatok a koniec, tu mozem specifikovat viacero bodov animacie. UsingKeyFrame animacia obsahuje koleckiu KeyFrames objektov, ktore defiunuju hodnotu animacie a cas za aky sa animacia ma zrealizovat.
// !!! 7. Pozname tri typy KeyFrames, ktore sa pouzivaju ako body animacie v UsingKeyFrame animaciach.
//    A. LinearXXXKeyFrame - vtedy medzi jednotlivymi body je hodnota LINEARNE INTERPOLOVANA.
//    B. SplineXXXKeyFrame - vtedy medzi jednotlivymi body je hodnota SPLINE INTERPOLOVANA - bezierove krivky. Ako parametre sa tu udavaju 2 riadiace body.
//    C. DiscreteXXXKeyFrame - rovno sa skoci z jednej hodnoty na druhu bez interpolacie.
// !!! 8. Pre kazdu UsingKeyFrame animaciu existuju horeuvedene 3 TYPY OBJEKTOV typu KeyFrame. LinearXXXKeyFrame a DiscreteXXXKeyFrame je mozne vzajomne kombinovat.
// 9. Takisto je mozne pouzit Path-Based Animation, kde Path urcuje priebeh hodnot animacie.
//------------------------------------------------------------------------
namespace ElementTransformations
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
			RotateAnimation				Win=new RotateAnimation();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			MultipleTransform			Win=new MultipleTransform();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			AnimatingBrushes			Win=new AnimatingBrushes();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick4(object Sender, RoutedEventArgs E)
		{
			LinearKeyFrame				Win=new LinearKeyFrame();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick5(object Sender, RoutedEventArgs E)
		{
			DiscreteKeyFrame			Win=new DiscreteKeyFrame();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick6(object Sender, RoutedEventArgs E)
		{
			SplineKeyFrame				Win=new SplineKeyFrame();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick7(object Sender, RoutedEventArgs E)
		{
			PathBasedAnimation			Win=new PathBasedAnimation();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------