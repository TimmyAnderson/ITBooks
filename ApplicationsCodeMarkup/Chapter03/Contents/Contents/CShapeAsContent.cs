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
namespace Contents
{
//------------------------------------------------------------------------------
	public class CShapeAsContent : Window
	{
//------------------------------------------------------------------------------
		public CShapeAsContent()
		{
			Ellipse			E=new Ellipse();

			E.Fill=Brushes.AliceBlue;
			E.StrokeThickness=5;
			E.Stroke=new SolidColorBrush(Colors.Red);
			
			// Roztiahne Ellipse do celej velkosti obrazovky pretoze HorizontalAlignment a VerticalAlignment je na Stretch.
			Console.WriteLine(string.Format("HorizontalAlignment: [{0}], VerticalAlignment: [{1}] !",E.HorizontalAlignment,E.VerticalAlignment));
			
			Content=E;
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------