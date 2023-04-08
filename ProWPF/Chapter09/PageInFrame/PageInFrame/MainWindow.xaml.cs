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
// 1. Program demonstruje pouzitie Page vo Frame.
// 2. Frame sluzi na zobraznie Page. Je to Element a mozem ho umiestnit lubovolne do Window ci ineho Page.
// !!! 3. Default ma nastaveny NavigationUIVisibility na Automatic co znamena, ze sa navigacne tlacitka zobrazia AZ PO TOM CO ODSKOCIM NA INU PAGE A JE SA KDE NAVIGOVAT.
// !!! 4. Na jednom Window\Page moze byt aj viacero Frames.
//------------------------------------------------------------------------
namespace PageInFrame
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