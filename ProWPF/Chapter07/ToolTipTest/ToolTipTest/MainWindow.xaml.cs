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
// 1. Program demonstruje ToolTips.
// 2. Pomocou propety ToolTip implementovanej vo FrameworkElement mozem aplikovat ToolTip na LUBOVOLNY Element.
// 3. V ToolTip mozem umiestnovat rozlicne Elements ako aj obrazky. Interaktivne Elements ako Buttons ci TextBox VSAK NEBUDU REAGOVAT.
// !!! 4. ToolTip ma mnozstvo properties, ktorym mozem menit poziciu ToolTip, alebo timeouts.
// !!! 5. Pomocou triedy ToolTipService je mozne nastavit dalsie properties, najme timeouts.
//------------------------------------------------------------------------
namespace ToolTipTest
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
		private void OnToolTipOpening(object Sender, ToolTipEventArgs E)
		{
			Debug.WriteLine("ToolTip OPENING !");

			// !!! Ked nastavim Handled na TRUE tak sa ToolTip NEZOBRAZI.
			// E.Handled=true;
		}
//------------------------------------------------------------------------
		private void OnToolTipClosing(object Sender, ToolTipEventArgs E)
		{
			Debug.WriteLine("ToolTip CLOSING !");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------