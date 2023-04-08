using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
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
	public partial class ParagraphTest:Window
	{
//------------------------------------------------------------------------
		public ParagraphTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnClick1(object Sender, RoutedEventArgs E)
		{
			foreach(Run R in MParagraph1.Inlines)
				Debug.WriteLine(string.Format("{0}",R.Text));
		}
//------------------------------------------------------------------------
		private void OnClick2(object Sender, RoutedEventArgs E)
		{
			foreach(Run R in MParagraph2.Inlines)
				Debug.WriteLine(string.Format("{0}",R.Text));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------