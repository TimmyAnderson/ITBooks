using System;
using System.Collections.Generic;
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
namespace VisualsTest
{
//------------------------------------------------------------------------
	public partial class SimpleVisuals:System.Windows.Window
	{
//------------------------------------------------------------------------
		public SimpleVisuals()
		{
			InitializeComponent();
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public void OnAddNewVisualClick(object Sender, RoutedEventArgs E)
		{
			DrawingVisual		DW=new DrawingVisual();
			Random				RND=new Random();

			MDrawingSurface.DrawSquare(DW,new Point(RND.Next(290),RND.Next(190)),false);
			MDrawingSurface.AddVisual(DW);
		}
//------------------------------------------------------------------------
		public void OnRemoveVisualClick(object Sender, RoutedEventArgs E)
		{
			DrawingVisual		DW=new DrawingVisual();
			Random				RND=new Random();

			if (MDrawingSurface.ItemsCount==0)
				return;

			DrawingVisual		DV=MDrawingSurface[RND.Next(MDrawingSurface.ItemsCount)];

			MDrawingSurface.DeleteVisual(DV);
		}
//------------------------------------------------------------------------
		private void OnMouseLeftButtonDown(object Sender, MouseButtonEventArgs E)
		{
			DrawingVisual		DV=MDrawingSurface.GetVisualByHitTest(E.GetPosition(MDrawingSurface));

			if (DV==null)
				return;
			// 2 - sirka Pen pouzita CMyCustomVisualsRenderer.DrawSquare().
			Point				TopLeftCorner=new Point(DV.ContentBounds.TopLeft.X + 2, DV.ContentBounds.TopLeft.Y + 2);

			MDrawingSurface.DrawSquare(DV,TopLeftCorner,true);
		}
//------------------------------------------------------------------------
		private void OnMouseLeftButtonUp(object Sender, MouseButtonEventArgs E)
		{
			DrawingVisual		DV=MDrawingSurface.GetVisualByHitTest(E.GetPosition(MDrawingSurface));

			if (DV==null)
				return;

			// 2 - sirka Pen pouzita CMyCustomVisualsRenderer.DrawSquare().
			Point				TopLeftCorner=new Point(DV.ContentBounds.TopLeft.X + 2, DV.ContentBounds.TopLeft.Y + 2);

			MDrawingSurface.DrawSquare(DV,TopLeftCorner,false);
		}
//------------------------------------------------------------------------
		private void OnMouseMove(object Sender, MouseEventArgs E)
		{

		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------