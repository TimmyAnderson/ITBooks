using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------
	public class CFrameworkElement : FrameworkElement
	{
//------------------------------------------------------------------------
		protected override void OnRender(DrawingContext DC)
		{
			double			SizeX=base.ActualWidth;
			double			SizeY=base.ActualHeight;

			DC.DrawEllipse(new SolidColorBrush(Color.FromRgb(255,0,0)),new Pen(new SolidColorBrush(Color.FromRgb(255,0,0)),3),new Point(SizeX/2,SizeY/2),10,10);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------