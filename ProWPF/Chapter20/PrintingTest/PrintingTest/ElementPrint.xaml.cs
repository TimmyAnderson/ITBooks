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
namespace PrintingTest
{
//------------------------------------------------------------------------
	public partial class ElementPrint:Window
	{
//------------------------------------------------------------------------
		public ElementPrint()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private void Button_Click1(object Sender, RoutedEventArgs E)
		{
			PrintDialog				PD=new PrintDialog();

			if (PD.ShowDialog()==true)
				PD.PrintVisual(MToPrint,"Test Print");
		}
//------------------------------------------------------------------------
		// !!!!! Aby to spravne fungovalo tak by musel byt MToPrint typu Canvas.
		private void Button_Click2(object Sender, RoutedEventArgs E)
		{
			PrintDialog				PD=new PrintDialog();

			if (PD.ShowDialog()==true)
			{
				// Skryjem parent Element - aby zvecsenie nebolo vidiet.
				MParentPrintStackPanel.Visibility=Visibility.Hidden;

				// Zvecsim vystup 5 krat.
				MToPrint.LayoutTransform=new ScaleTransform(5, 5);

				// Definujem Margin okolo Page.
				int			PageMargin=5;

				// Ziskam velkost Page.
				Size		PageSize=new Size(PD.PrintableAreaWidth-PageMargin*2, PD.PrintableAreaHeight-20);

				// Zrealizujem prepocet, aby sa zvecsenie aplikovalo.
				MToPrint.Measure(PageSize);
				MToPrint.Arrange(new Rect(PageMargin, PageMargin, PageSize.Width, PageSize.Height));

				// Vytlacim Element.
				PD.PrintVisual(MToPrint, "Test Print");

				// Odstranim zvescenie.
				MToPrint.LayoutTransform=null;

				MParentPrintStackPanel.Visibility=Visibility.Visible;
			}
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------