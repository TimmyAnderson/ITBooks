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
// 1. Program demonstruje rozlicne aspekty Application class pri JEJ ZDEDENI.
// 2. Program demonstruje zachytavanie evento Application cez pretazenie virtualnej metody, ako aj moznost zdielania dat medzi Windows pomocou Application class.
//------------------------------------------------------------------------
namespace DerivedApplicationClassTest
{
//------------------------------------------------------------------------
	public partial class MainWindow:System.Windows.Window
	{
//------------------------------------------------------------------------
		private int							MCounter=0;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public MainWindow()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnCreateSubWindow(object Sender, RoutedEventArgs E)
		{
			SubWindow			SW=new SubWindow(++MCounter);

			SW.Show();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------