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
	public partial class MainWindow3:System.Windows.Window
	{
//------------------------------------------------------------------------
		public MainWindow3()
		{
			InitializeComponent();

            AddHandler(CheckBox.CheckedEvent, new RoutedEventHandler(chk_Checked));
            AddHandler(CheckBox.UncheckedEvent, new RoutedEventHandler(chk_Unchecked));            
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void chk_Checked(object Sender, RoutedEventArgs E)
        {
            CheckBox			Chk=(CheckBox) E.OriginalSource;
            DependencyObject	Obj=LogicalTreeHelper.FindLogicalNode(this, Chk.Content.ToString());

            ((FrameworkElement) Obj).Visibility=Visibility.Visible;
        }
//------------------------------------------------------------------------
        private void chk_Unchecked(object Sender, RoutedEventArgs E)
        {
            CheckBox			Chk=(CheckBox) E.OriginalSource;
            DependencyObject	Obj=LogicalTreeHelper.FindLogicalNode(this, Chk.Content.ToString());

            ((FrameworkElement) Obj).Visibility=Visibility.Collapsed;
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------