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
// 1. Program demonstruje pouzitie Custom Panel.
// 2. Implementacia Custom Panel spociva v zdedeni Control z obektu Panel a pretazenia dvoch metod MeasureOverride() a ArrangeOverride().
// 3. Obe tieto medoty volaju vsetky Child Elements a vypoctivavaju velkost (volanie Measure() na Child) a prideluju miesto (volanie Arrange() na Child) Child Elements.
// !!! 4. VZDY MUSIM VOLAT Measure() AJ KED MA NEZAUJIMA VELKOST ELEMENTU. INAK SA NEBUDE SPRAVNE RENDEROVAT.
//------------------------------------------------------------------------
namespace CustomPanelClient
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
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------