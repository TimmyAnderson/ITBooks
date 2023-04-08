using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------
namespace Visuals
{
//------------------------------------------------------------------------
	// !!!!! Sluzi ako HOST - pretoze UIElement uz MA LAYOUT FAZU.
	public class CVisualHost : UIElement
	{
//------------------------------------------------------------------------
		private List<Visual>						MHostVisuals;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		public CVisualHost()
		{
			MHostVisuals=new List<Visual>();

			// Pridam CUSTOM VISUAL renderujuci 2 elipsy.
			MHostVisuals.Add(new CVisual());

			// Pridam CUSTOM DRAWING VISUAL renderujuci 2 elipsy.
			MHostVisuals.Add(new CDrawingVisual());

			// Pridam i DALSI VISUAL renderujuci obdlznik.
			DrawingVisual		MyRect1=new DrawingVisual();
			DrawingContext		DC1=MyRect1.RenderOpen();

			DC1.DrawRectangle(new SolidColorBrush(Color.FromRgb(0,255,0)),new Pen(new SolidColorBrush(Color.FromRgb(255,0,0)),3),new Rect(){X=200,Y=200,Height=100,Width=200});

			DC1.Close();

			MHostVisuals.Add(MyRect1);

			// A pridam este jeden Visual.
			DrawingVisual		MyRect2=new DrawingVisual();
			DrawingContext		DC2=MyRect2.RenderOpen();

			DC2.DrawRectangle(new SolidColorBrush(Color.FromRgb(0,255,0)),new Pen(new SolidColorBrush(Color.FromRgb(0,0,255)),3),new Rect(){X=10,Y=10,Height=10,Width=20});

			DC2.Close();

			MHostVisuals.Add(MyRect2);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Tato property MUSI BYT PRETAZENA, ak ma Visual nieco renderovat.
		protected override int						VisualChildrenCount
		{
			get
			{
				//Console.WriteLine(string.Format("[{0}] CVisualHost - VisualChildrenCount: [{1}] !",DateTime.Now.ToLongTimeString(),MHostVisuals.Count));

				return(MHostVisuals.Count);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// !!! Tato metoda MUSI BYT PRETAZENA, ak ma Visual nieco renderovat.
		protected override Visual GetVisualChild(int Index)
		{
			return(MHostVisuals[Index]);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------