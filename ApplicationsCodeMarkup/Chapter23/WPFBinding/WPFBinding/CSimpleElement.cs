using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace WPFBinding
{
//-------------------------------------------------------------------------------------------------------
	public class CSimpleElement : FrameworkElement
	{
//-------------------------------------------------------------------------------------------------------
        public static DependencyProperty						NumberProperty;
//-------------------------------------------------------------------------------------------------------
        static CSimpleElement()
        {
            NumberProperty=DependencyProperty.Register("Number", typeof(double), typeof(CSimpleElement), new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.AffectsRender));
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public double											Number
        {
            get
			{
				return((double)GetValue(NumberProperty));
			}
            set
			{
				SetValue(NumberProperty, value);
			}
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
            return(new Size(200, 50));
        }
//-------------------------------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            DC.DrawText(new FormattedText(Number.ToString(), CultureInfo.CurrentCulture, FlowDirection.LeftToRight,new Typeface("Times New Roman"), 12, SystemColors.WindowTextBrush), new Point(0, 0)); 
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------