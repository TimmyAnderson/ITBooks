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
// 1. Program demonstruje pouzitie Transformations.
// 2. Transformaciami je mozne vykonavat rozlicne transformacne efekty nad Elements a Shapes.
// !!! 3. XAML interne transformuje vsetky transformation na MatrixTransformation, ktora sa potom aplikuje.
// !!! 4. Vsetky transformations su zdedene z Freezable co znaci, ze ich zmena SA AUTOMATICKY PREMIETNE DO GUI.
// 5. Niektore rotacie ako napriklad RotateTransformation umoznuju definovat stred rotacie (CenterX, CenterY) na ktorym bude rotacia vykonana.
// !!! 6. NEVYHODOU (CenterX, CenterY) je, ze su zadavane v ABSOLUTNYCH CISLACH. Ovela lepsia je property RenderTransformOrigin podporovana vsetkymi Shapes, ktora je zadavane v rozpeti <0-1> klientskej oblasti daneho Elementu.
// 7. Transformacie mozem zadavat v property LayoutTransformation, kde sa aplikuju este pred realizovanim Layout a MAJU VPLYV NA LAYOUT, alebo RenderTransfromation, kde sa aplikuju az v Render faze a ich rotacia nema vplyv na Layout ostatnych Elements.
//------------------------------------------------------------------------
namespace TransformationsTests
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
			DynamicTransformation		Win=new DynamicTransformation();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			TransformingShapes			Win=new TransformingShapes();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
		private void OnClick3(object Sender, RoutedEventArgs E)
		{
			TransformingElements		Win=new TransformingElements();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------