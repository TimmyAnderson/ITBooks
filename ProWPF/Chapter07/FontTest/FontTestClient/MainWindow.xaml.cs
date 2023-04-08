using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
// 1. Progrem demonstruje fonty.
// 2. Trieda Fonts definuje niekolko properties umoznujuci nastavit velkost fontu a jeho vlastnosti ako Bold, Stretch ci Weight.
// 3. Okrem toho dalsie vlastnosti a prkotinky fontu je mozne nasatvit TextDecorations a Typography.
// !!! 4. Meno Fontu MUSI BYT UPLNE PRESNE, INAK HO WPF IGNORUJE.
// !!! 5. Ak Font NIE JE NA CIELOVOM PC, mozem dat viacero alternativnych Fontov, tak ze do FontFamily dam viacero fontov oddelenych ciarkou.
// !!! 6. Trieda SystemFontFamilies obsahuje mnozstvo static properties, vratane zoznamu vsetkych Fonts.
//------------------------------------------------------------------------
namespace FontTestClient
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
		private void OnShowAllFonts(object Sender, RoutedEventArgs E)
		{
			foreach (FontFamily FF in Fonts.SystemFontFamilies)
				Debug.WriteLine(string.Format("\t{0} !",FF.Source));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------