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
namespace CustomElements
{
//------------------------------------------------------------------------------
	public class CEllipseElement : FrameworkElement
	{
//------------------------------------------------------------------------------
		public CEllipseElement()
		{

		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		protected override void OnRender(DrawingContext DC)
		{
			base.OnRender(DC);

			DC.DrawEllipse(Brushes.Blue,new Pen(Brushes.Red, 24), new Point(RenderSize.Width/2,RenderSize.Height/2),RenderSize.Width/2,RenderSize.Height/2);

			Console.WriteLine(string.Format("Size: [{0},{1}] !",RenderSize.Width,RenderSize.Height));
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------