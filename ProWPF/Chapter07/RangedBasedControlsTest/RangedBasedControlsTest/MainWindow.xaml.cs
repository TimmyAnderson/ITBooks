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
// 1. Program demonstruje Sliders, ProgressBars a ScrollBar.
// 2. Sliders ma property Ticks umoznujucu definovat znacky aj nepravidelne. Naopak pomocou TickFrequency ich umiestnim pravidelne. Takisto viem nastavit aj timeouts a selection area cez property IsSelectionRangeEnabled na TRUE, SelectionStart a SelectionEnd.
// 3. ScrollBar nie je nijako zaujimavy, kedze ScrollBarViewer je daleko lepsi a komplexnejsi Element.
// 4. ProgressBar ma dve modes.
//    A. Ak definuje Minimum a Maximum tak sa zobrazuje pomocou Value proporcna cast Progress vytmavi.
//    B. Ak definujem propery IsIndeterminate vtedy Minimum, Maximum a Value NEMAJU ZMYSEL a ProgressBar sa periodicky prekresluje ako symbolizovanie priebehu akcie.
// !!! 5. ProgressBar - jeho Value NASTAVUJEM SAM a PROGRAMOVO.
//------------------------------------------------------------------------
namespace RangedBasedControlsTest
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