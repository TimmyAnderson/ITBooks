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
using VisualTreeDisplayLibrary;
//------------------------------------------------------------------------
// 1. Program demosntruje kniznicu zorbazujucu vizualny strom.
// 2. WPF reprezentuje obsah okna pomocou Logical Tree, ktory obsahuje vsekty Elements co som pridal do okna. Ale nielen Elements, ale napriklad aj ich Content co moze byt napriklad aj obycajny string.
// 3. WPF ma okrem Logical Tree aj Visual Tree, ktory vizualne reprezentuje zobrazovane okno. Niektore Nodes z Logical Tree rozbije na viacero Nodes vo Visual Tree.
// !!! 4. Elements su v v ramci C# triedy definovane BEZ GRAFICKEHO VYZORU. Ten mu dodava TEMPLATE.
// 5. Template je prave to co mapuje Node z LT na Node do VT a dava Elementu graficky vyzor.
// !!! 6. Samozrejme Template je mozne zmenit a tym sa daju realizovat styly vo WPF.
// !!!!! 7. Zatial co LT sa nemeni po spusteni okna (ak ho nezmenim v kode) tak VT sa meni v zavislosti od pouziteho stylu vo Windows.
//------------------------------------------------------------------------
namespace VisualTreeDisplayClient
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
			CVisualTreeDisplay		TreeDisplay=new CVisualTreeDisplay();

			TreeDisplay.ShowVisualTree(this);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------