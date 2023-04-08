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
// 1. Program demonstruje pouzite StatusBar.
// 2. StatusBar sice nema take moznosti ako ToolBar co sa tyka zmeny pozcie ci umiesntenia do ToolBarTray, ale na rozdiel od ToolBar su jeho Child Elements umiestnene do StatusBarItem a TAKISTO AKO V TOOLBAR aj tu StatusBar MENI Default Style svojich Child Elements.
//------------------------------------------------------------------------
namespace StatusBarTest
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