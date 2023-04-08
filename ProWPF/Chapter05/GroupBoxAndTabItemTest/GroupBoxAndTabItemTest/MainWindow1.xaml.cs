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
// 1. Program demonstruje GroupBox a TabItem.
// 2. GroupBox a TabItem su tzv. Header Elements, ktore maju ako Content jeden Element, ale MAJU NAVYSE aj Header, do ktoreho znova mozem dat jeden Element.
// 3. GroupBox je trivialny Element, ktory dokonca ani neponuka explicitne grouping RadionButtons napriklad (nie je treba, lebo KAZDY Panel robi Grouping svojich Child Elements). Obsahuje iba jeden Child Element a preto sa don vnara zvycajne nejaky Panel. Kresli okolo svojich hranic Round Rectangle.
// 4. TabItem je Item do TabControl. Je teda Child Element do TabControl.
// !!! 5. V TabControl JE JEDINY ZMYSLUPLNY Child E do TabControl. Inak to vyzera dost bizarne ako je vidiet v MainWindow2.xaml.
// !!! 6. Property TabControl.TabStripPlacement urcuje ku ktoremu okraju bude Header docknuty.
//------------------------------------------------------------------------
namespace GroupBoxAndTabItemTest
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