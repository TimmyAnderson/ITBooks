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
	public class CVisual : Visual
	{
//------------------------------------------------------------------------
		private List<Visual>						MVisuals;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CVisual()
		{
			MVisuals=new List<Visual>();

			MVisuals.Add(CreateEllipseVisual(new Point(100,100)));
			MVisuals.Add(CreateEllipseVisual(new Point(150,100)));
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Tato property MUSI BYT PRETAZENA, ak ma Visual nieco renderovat.
		protected override int						VisualChildrenCount
		{
			get
			{
				//Console.WriteLine(string.Format("[{0}] CVisual - VisualChildrenCount: [{1}] !",DateTime.Now.ToLongTimeString(),MVisuals.Count));

				return(MVisuals.Count);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private Visual CreateEllipseVisual(Point PT)
		{
			// DrawingVisual ma renderovacie metody na 2D rendering.
			DrawingVisual		DW=new DrawingVisual();
			DrawingContext		DC=DW.RenderOpen();

			DC.DrawEllipse(new SolidColorBrush(Color.FromRgb(255,0,0)),new Pen(new SolidColorBrush(Color.FromRgb(255,0,0)),3),PT,20,20);

			DC.Close();

			return(DW);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Tato metoda MUSI BYT PRETAZENA, ak ma Visual nieco renderovat.
		protected override Visual GetVisualChild(int Index)
		{
			return(MVisuals[Index]);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------