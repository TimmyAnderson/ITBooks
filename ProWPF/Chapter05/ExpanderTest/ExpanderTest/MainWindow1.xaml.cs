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
// 1. Program demonstruje pouzitie Expandera.
// 2. Expander sluzi na skyrvanie a odkryanie casti okna.
// 3. Property ExpandDirection urcuje do akeho smeru sa skryta oblast roztiahne.
// !!!!! 4. Problem je pri Grdi Cells, ktore NEROZSIRUJU NA ROZDIEL od StackPanel SVOJU VELKOT pri expandovani a TAK ICH CONTENT JE OREZANY.
// !!!!! 5. Riesenim problemu z bodu 4 je nastavit Grid CELL na Auto Width a Height.
// 6. Expander vystavuje eventy, tkre je mozne zachytit pre roztiahnutim a stiahnutim Expandera.
//------------------------------------------------------------------------
namespace ExpanderTest
{
//------------------------------------------------------------------------
	public partial class MainWindow1:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow1()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------