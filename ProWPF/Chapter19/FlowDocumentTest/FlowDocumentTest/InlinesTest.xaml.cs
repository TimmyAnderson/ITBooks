using System;
using System.Collections.Generic;
using System.Linq;
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
namespace FlowDocumentTest
{
//------------------------------------------------------------------------
	public partial class InlinesTest:Window
	{
//------------------------------------------------------------------------
		public InlinesTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Hyperlink_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("Hyperlink clicked !");
		}
//------------------------------------------------------------------------
		private void Button_Click(object Sender, RoutedEventArgs E)
		{
			MessageBox.Show("Button clicked !");
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------