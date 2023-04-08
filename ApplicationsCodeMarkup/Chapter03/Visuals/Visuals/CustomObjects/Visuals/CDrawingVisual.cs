using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------
	// !!!!! Visual dokaze robit IBA REDNERING (zaradzovanie PRIMITIV a OPERACII nad nimi) do KOLEKCIE, ale NEMA LAYOUT fazu a preto NEMOZE BYT PRIAMO REDNEROVANY. Potrebuje HOST, ktory ho bude renderovat.
	public class CDrawingVisual : DrawingVisual
	{
//------------------------------------------------------------------------
		public CDrawingVisual()
		{
			Visual		DW1=CreateEllipseVisual(new Point(100,200));
			Visual		DW2=CreateEllipseVisual(new Point(150,200));

			base.Children.Add(DW1);
			base.Children.Add(DW2);

			DrawingContext		DC1=base.RenderOpen();

			DC1.DrawEllipse(new SolidColorBrush(Color.FromRgb(255,0,127)),new Pen(new SolidColorBrush(Color.FromRgb(255,0,0)),3),new Point(100,300),20,20);

			DC1.Close();

			// !!! Zrusi rendering DC1 a bude renderovat IBA DC2.
			/*
			DrawingContext		DC2=base.RenderOpen();

			DC2.DrawEllipse(new SolidColorBrush(Color.FromRgb(0,0,255)),new Pen(new SolidColorBrush(Color.FromRgb(255,0,0)),3),new Point(100,350),20,20);

			DC2.Close();
			*/
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private Visual CreateEllipseVisual(Point PT)
		{
			// DrawingVisual ma renderovacie metody na 2D rendering.
			DrawingVisual		DW=new DrawingVisual();
			DrawingContext		DC=DW.RenderOpen();

			DC.DrawEllipse(new SolidColorBrush(Color.FromRgb(255,0,255)),new Pen(new SolidColorBrush(Color.FromRgb(255,0,0)),3),PT,20,20);

			DC.Close();

			return(DW);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------