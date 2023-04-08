using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace Contents
{
//------------------------------------------------------------------------------
	public class CSimpleEllipse : FrameworkElement
	{
//------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            DC.DrawEllipse(Brushes.Blue, new Pen(Brushes.Red, 24), new Point(RenderSize.Width / 2, RenderSize.Height / 2), RenderSize.Width / 2, RenderSize.Height / 2);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------