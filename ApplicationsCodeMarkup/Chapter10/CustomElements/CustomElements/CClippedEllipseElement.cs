﻿using System;
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
	public class CClippedEllipseElement : FrameworkElement
	{
//------------------------------------------------------------------------------
        public static readonly DependencyProperty	FillProperty;
        public static readonly DependencyProperty	StrokeProperty;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CClippedEllipseElement()
        {
			FillProperty=DependencyProperty.Register("Fill", typeof(Brush), typeof(CCompexEllipseElement), new FrameworkPropertyMetadata(null,FrameworkPropertyMetadataOptions.AffectsRender));
            StrokeProperty=DependencyProperty.Register("Stroke", typeof(Pen),typeof(CCompexEllipseElement), new FrameworkPropertyMetadata(null,FrameworkPropertyMetadataOptions.AffectsMeasure));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public Brush								Fill
        {
            set
			{
				SetValue(FillProperty, value);
			}
            get
			{
				return (Brush)GetValue(FillProperty);
			}
        }
//------------------------------------------------------------------------------
        public Pen									Stroke
        {
            set
			{
				SetValue(StrokeProperty, value);
			}
            get
			{
				return (Pen)GetValue(StrokeProperty);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
            Size			SizeDesired=new Size();

			// !!! Tym, ze SizeDesired je VACSI ako SizeAvailable dojde ku CLIPPING.
			SizeDesired.Width=SizeAvailable.Width*2;
			SizeDesired.Height=SizeAvailable.Height*2;

			Console.WriteLine(string.Format("SizeDesired: [{0},{1}] !",SizeDesired.Width,SizeDesired.Height));

            return(SizeDesired);
        }
//------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            Size			Size=RenderSize;

            if (Stroke!=null)
            {
                Size.Width=Math.Max(0, Size.Width-Stroke.Thickness);
                Size.Height=Math.Max(0, Size.Height-Stroke.Thickness);
            }

            DC.DrawEllipse(Fill, Stroke, new Point(RenderSize.Width/2, RenderSize.Height/2), Size.Width/2, Size.Height/2);

			Console.WriteLine(string.Format("RenderSize: [{0},{1}] !",RenderSize.Width,RenderSize.Height));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------