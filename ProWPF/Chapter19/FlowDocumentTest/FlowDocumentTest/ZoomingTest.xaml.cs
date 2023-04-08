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
	public partial class ZoomingTest:Window
	{
//------------------------------------------------------------------------
		public ZoomingTest()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void OnIncreaseZoom(object Sender, RoutedEventArgs E)
		{
			MViewer.IncreaseZoom();
		}
//------------------------------------------------------------------------
		private void OnDecreaseZoom(object Sender, RoutedEventArgs E)
		{
			MViewer.DecreaseZoom();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------