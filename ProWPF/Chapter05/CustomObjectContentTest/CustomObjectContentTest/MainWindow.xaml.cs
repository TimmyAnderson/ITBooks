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
// 1. Program demonstruje ako je mozne zobrazovat Custom Object.
// !!! 2. Ak je objekt zdedeny z FrameworkElement potom sa pouzjie pri renderingu metoda OnRender().
// !!! 3. Ak objekt nie je zdedeny z FrameworkElement potom sa pouzije metoda ToString() a jej text za zobrazi ako Content.
// !!!!! 4. Objekty, ktore nie su zdenene z FrameworkElement SA NEDAJU PRIAMO DAT DO WINDOW, ALE TREBA ICH WRAPPROVAT NAPRIKLAD POMOCOU LABEL.
//------------------------------------------------------------------------
namespace CustomObjectContentTest
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