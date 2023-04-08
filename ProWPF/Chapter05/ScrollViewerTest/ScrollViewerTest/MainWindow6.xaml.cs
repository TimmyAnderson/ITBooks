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
namespace ScrollViewerTest
{
//------------------------------------------------------------------------
	public partial class MainWindow6:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow6()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void LineUp(object Sender, RoutedEventArgs E)
        {
            MScroller.LineUp();
        }
//------------------------------------------------------------------------
        private void LineDown(object Sender, RoutedEventArgs E)
        {
            MScroller.LineDown();
        }
//------------------------------------------------------------------------
        private void PageUp(object Sender, RoutedEventArgs E)
        {
            MScroller.PageUp();
        }
//------------------------------------------------------------------------
        private void PageDown(object Eender, RoutedEventArgs E)
        {
            MScroller.PageDown();
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------