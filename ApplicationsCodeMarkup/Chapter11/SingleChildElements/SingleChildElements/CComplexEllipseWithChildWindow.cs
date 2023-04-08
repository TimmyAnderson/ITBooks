using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------------
namespace SingleChildElements
{
//------------------------------------------------------------------------------
	public class CComplexEllipseWithChildWindow : Window
	{
//------------------------------------------------------------------------------
		private CComplexEllipseWithChild				MEllipse;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CComplexEllipseWithChildWindow()
		{
            Title="Enclose Element in Ellipse";

            MEllipse=new CComplexEllipseWithChild();

            MEllipse.Fill=Brushes.ForestGreen;
            MEllipse.Stroke=new Pen(Brushes.Magenta, 48);
            Content=MEllipse;

            TextBlock			Text=new TextBlock();

            Text.FontFamily=new FontFamily("Times New Roman");
            Text.FontSize=48;
            Text.Text="Text inside ellipse";

			// Nastavim CHILD property.
            MEllipse.Child=Text;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------