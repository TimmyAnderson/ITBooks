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
// 1. Program demonstruje pouzitie Drawings.
// 2. Drawings objekty sluzia na vykrelsovanie Geometry objektov PODOBNE AKO Path.
// !!! 3. Ich hlavnou vyhodou je ze GeometryDrawing NIE SU ELEMENTY a teda BERU MENEJ PAMETE ako Path objekty.
// !!! 4. Istou nevyhodou vsak je, ze nemozne na kazdy GeometryDrawing zavesit napriklad zachytavanie udalosti mysky, kedze to NIE JE Element.
// !!!!! 5. Vyuziva sa najme NA STATICKE OBRAZKY, kde sa nedoporucuje pouzivat bitmapy, ale prave renderovanu VEKTOROVU GRAFIKU.
//------------------------------------------------------------------------
namespace DrawingsTest
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
		private void OnClick(object Sender, RoutedEventArgs E)
		{
			SimpleDrawingTest			Win=new SimpleDrawingTest();

			Win.ShowDialog();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------