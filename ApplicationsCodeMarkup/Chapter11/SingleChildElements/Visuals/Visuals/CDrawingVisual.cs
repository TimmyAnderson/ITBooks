using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------
	// Pretazim DrawingVisual, ktory ma 2 CHILDREN.
	public class CDrawingVisual : DrawingVisual
	{
//------------------------------------------------------------------------
		public CDrawingVisual()
		{
			Visual			DW1=CVisual.CreateEllipseVisual(new Point(100,200),Colors.Red,Colors.DarkRed);
			Visual			DW2=CVisual.CreateEllipseVisual(new Point(150,200),Colors.Red,Colors.DarkRed);

			// !!!!! Kedze DrawingVisual dedi od ContainerVisual, ma v property Children KOLEKCIU typu VisualCollection.
			base.Children.Add(DW1);
			base.Children.Add(DW2);

			// !!!!! DrawingVisual okrem toho, ze moze mat Visuals sama umoznuje renderovat lubovolny obsah. To je rozdiel oproti triede Visul, ktora SAMA sa REDNEROVAT NEDOKAZE a potrebuje na to CHILDREN VISUALS zdedene z DrawingVisual, alebo UIElement.
			DrawingContext		DC=base.RenderOpen();

			DC.DrawEllipse(new SolidColorBrush(Colors.LightBlue),new Pen(new SolidColorBrush(Colors.DarkBlue),3),new Point(100,300),20,20);

			DC.Close();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------