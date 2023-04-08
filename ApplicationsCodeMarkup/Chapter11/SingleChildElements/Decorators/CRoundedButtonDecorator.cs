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
namespace Decorators
{
//------------------------------------------------------------------------------
	// !!! Dedi z DECORATOR, ktora ma property Child.
	public class CRoundedButtonDecorator : Decorator
	{
//------------------------------------------------------------------------------
        public static readonly DependencyProperty	IsPressedProperty;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CRoundedButtonDecorator()
        {
            IsPressedProperty=DependencyProperty.Register("IsPressed", typeof(bool), typeof(CRoundedButtonDecorator), new FrameworkPropertyMetadata(false, FrameworkPropertyMetadataOptions.AffectsRender));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public bool									IsPressed
        {
            get
			{
				return((bool)GetValue(IsPressedProperty));
			}
            set
			{
				SetValue(IsPressedProperty, value);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
            Size		SzDesired=new Size(2, 2);

            SizeAvailable.Width-=2;
            SizeAvailable.Height-=2;

            if (Child!=null)
            {
                Child.Measure(SizeAvailable);
                SzDesired.Width+=Child.DesiredSize.Width;
                SzDesired.Height+=Child.DesiredSize.Height;
            }

            return(SzDesired);
        }
//------------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size SizeArrange)
        {
            if (Child!=null)
            {
                Point				PTChild=new Point(Math.Max(1, (SizeArrange.Width-Child.DesiredSize.Width)/2),Math.Max(1,(SizeArrange.Height-Child.DesiredSize.Height)/2));

                Child.Arrange(new Rect(PTChild, Child.DesiredSize));
            }

            return(SizeArrange);
        }
//------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            RadialGradientBrush		Brush=new RadialGradientBrush((IsPressed==true) ? SystemColors.ControlDarkColor : SystemColors.ControlLightLightColor, SystemColors.ControlColor);

            Brush.GradientOrigin=(IsPressed==true) ? new Point(0.75, 0.75) : new Point(0.25, 0.25);
            DC.DrawRoundedRectangle(Brush, new Pen(SystemColors.ControlDarkDarkBrush,1), new Rect(new Point(0,0), RenderSize), RenderSize.Height/2, RenderSize.Height/2);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------