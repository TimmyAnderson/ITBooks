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
// 1. Program demonstruje Grid alignment.
// !!! 2. V ramci jednej cell MOZE BYT VIAC Elements.
// !!!!! 3. V CELL mozem pouzivat Alignment ci Margin tak ako na inych Panels.
// !!!!! 4. Ked vsak zmensim okno tak, ze sa jednotlive Elements do CELL nezmestia tak sa zacnu prekryvat. To co sa bude prekryvat zavisi ZIndex a ten zas od poradia Elements v XAML.
//------------------------------------------------------------------------
namespace GridAlignmentTest
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