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
namespace LayoutExamples
{
//------------------------------------------------------------------------
	public partial class MainWindow2:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow2()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void chkLongText_Checked(object Sender, RoutedEventArgs E)
        {            
            MCmdPrev.Content = " <- Go to the Previous Window ";
            MCmdNext.Content = " Go to the Next Window -> ";
        }
//------------------------------------------------------------------------
        private void chkLongText_Unchecked(object Sender, RoutedEventArgs E)
        {
            MCmdPrev.Content = "Prev";
            MCmdNext.Content = "Next";
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------