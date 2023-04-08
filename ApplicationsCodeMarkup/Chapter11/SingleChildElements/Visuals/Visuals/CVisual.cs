using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------
	// Trieda dedi z Visual.
	// !!! Visual poskytuje iba ZAKLADNU FUNKCIONALITU pre WPF.
	// !!!!! Bazicka trieda Visual NEPOSKYTUJE METODU na vratenie DrawingContext, avsak jej CHILD triedy ako DrawingVisual uz ANO.
	// !!!!! Trieda Visual je vlastne NODE vo VISUAL TREE a moze OBSAHUJE KOLEKCIU CHILD ELEMENTS.
	public class CVisual : Visual
	{
//------------------------------------------------------------------------
		// !!!!! Kedze VISUAL je TREE NODE vo VISUAL TREE, tak moze obsahovat kolekciu CHILD VISUALS.
		private List<Visual>						MVisuals;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CVisual()
		{
			MVisuals=new List<Visual>();

			Visual			Ellipse1=CreateEllipseVisual(new Point(100,100),Colors.LightGreen,Colors.DarkGreen);
			Visual			Ellipse2=CreateEllipseVisual(new Point(150,100),Colors.LightGreen,Colors.DarkGreen);

			// Pridam elipsy ako CHILD VISUALS.
			MVisuals.Add(Ellipse1);
			MVisuals.Add(Ellipse2);

			// Evidujem ELIPSY vo VISUAL TREE, aby mohli byt posielane RE.
			AddVisualChild(Ellipse1);
			AddVisualChild(Ellipse2);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Tato property vracia POCET CHILD VISUALS.
		protected override int						VisualChildrenCount
		{
			get
			{
				return(MVisuals.Count);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		internal static Visual CreateEllipseVisual(Point PT, Color C1, Color C2)
		{
			// !!! Vytvorim instanciu DrawingVisual, ktora poskytuje metodu RenderOpen() vracajucu DrawinContext.
			DrawingVisual		DW=new DrawingVisual();
			DrawingContext		DC=DW.RenderOpen();

			// Vykreslim ELIPSU.
			DC.DrawEllipse(new SolidColorBrush(C1),new Pen(new SolidColorBrush(C2),3),PT,20,20);

			// Uzavriem DRAWING CONTEXT.
			DC.Close();

			return(DW);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Tato OVERRIDED METHOD vracia pre dany Index CHILD VISUAL.
		protected override Visual GetVisualChild(int Index)
		{
			return(MVisuals[Index]);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------