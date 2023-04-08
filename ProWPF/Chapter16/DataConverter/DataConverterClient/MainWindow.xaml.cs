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
// 1. Program demonstruje pouzitie DataBinding Converter.
// 2. DataBinding ma property Converter, ktorou mozem naplnit objektom implementujucim IValueConverter a realizovat tak konverziu datovych hodnot na tie, ktore sa budu zobrazovat a vice-versa.
// !!! 3. Rozhranie IValueConverter ma metodou Convert() realizuje konverziu datovej hodnoty na zobrazovanu hodnotu a metoda ConvertBack() zas spetnu konverziu zobrazovanej hodnoty na datovu hodnotu. Ci sa pouziju obe metody zavisi na type DB. Pri TwoWay sa pouziju obe.
// !!! 4. Existuje aj rozhranie IMultiValueConverter, ktore v spojitosti s MultiBinding umoznuje konvertovat viacero hodnot na jednu a naopak.
//------------------------------------------------------------------------
namespace DataConverterClient
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
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------