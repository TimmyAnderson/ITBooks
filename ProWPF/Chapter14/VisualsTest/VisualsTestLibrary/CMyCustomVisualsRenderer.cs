using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
//------------------------------------------------------------------------
namespace VisualsTestLibrary
{
//------------------------------------------------------------------------
	// Trieda reprezentuje Element, ktory bude pouzivany na vykreslenie Visuals.
	public class CMyCustomVisualsRenderer : Canvas
	{
//------------------------------------------------------------------------
		private List<DrawingVisual>			MVisuals;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CMyCustomVisualsRenderer()
		{
			MVisuals=new List<DrawingVisual>();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Vracia pocet Visuals.
		protected override int				VisualChildrenCount
		{
			get
			{
				return(MVisuals.Count);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public  int							ItemsCount
		{
			get
			{
				return(MVisuals.Count);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public DrawingVisual				this[int Index]
		{
			get
			{
				return(MVisuals[Index]);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Vrati Visual pre dany Index.
		protected override Visual GetVisualChild(int Index)
		{
			return(MVisuals[Index]);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public void AddVisual(DrawingVisual Visual)
		{
			MVisuals.Add(Visual);

			base.AddVisualChild(Visual);
			base.AddLogicalChild(Visual);
		}
//------------------------------------------------------------------------
		public void DeleteVisual(DrawingVisual Visual)
		{
			MVisuals.Remove(Visual);

			base.RemoveVisualChild(Visual);
			base.RemoveLogicalChild(Visual);
		}		
//------------------------------------------------------------------------
		public void DrawSquare(DrawingVisual Visual, Point TopLeftCorner, bool IsSelected)
		{
			using (DrawingContext DC=Visual.RenderOpen())
			{
				Brush		Brush=new SolidColorBrush(Colors.Red);

				if (IsSelected==true)
					Brush=new SolidColorBrush(Colors.Green);

				DC.DrawRectangle(Brush, new Pen(Brushes.SteelBlue, 4), new Rect(TopLeftCorner, new Size(30, 30)));
			}
		}
//------------------------------------------------------------------------
		// Robi Hit Test.
		public DrawingVisual GetVisualByHitTest(Point Point)
		{
			HitTestResult		HitResult=VisualTreeHelper.HitTest(this, Point);
			// Musi byt pouzity operator 'as', kedze mozem klepnut aj mimo DrawingVisual.
			DrawingVisual		DV=HitResult.VisualHit as DrawingVisual;

			return(DV);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------