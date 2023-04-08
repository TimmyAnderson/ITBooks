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
// 1. Program demonstruje DockPanel.
// 2. DockPanel dockuje jednotlive Elements podla nastavenia Dock AP.
// 3. Ak viacero Elements dockujem do tej iste strany tak sa ukladaju ako pri StackPanel.
// 4. Nastavenim property LastChildFill na TRUE dosiahnem, ze podledny Element sa roztiahne na zbytok plochy.
// !!! 5. To ako cast parent Elementu budu Child Elements zaberat ZAVISI OD ICH PORADIA.
//------------------------------------------------------------------------
namespace DockPanelTest
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