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
namespace CustomPanels
{
//------------------------------------------------------------------------------
	public class CCustomCanvas : Panel
	{
//------------------------------------------------------------------------------
		// AP pre CHILDREN ELEMENTS.
        public static readonly DependencyProperty	LeftProperty;
        public static readonly DependencyProperty	TopProperty;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CCustomCanvas()
        {
			// !!! Ako metadata parameter je nastaveny FrameworkPropertyMetadataOptions.AffectsParentArrange, aby pri zmene hodnoty AP doslo k renderingu Panel.
            LeftProperty=DependencyProperty.RegisterAttached("Left",typeof(double), typeof(CCustomCanvas), new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.AffectsParentArrange));
            TopProperty=DependencyProperty.RegisterAttached("Top",typeof(double), typeof(CCustomCanvas), new FrameworkPropertyMetadata(0.0, FrameworkPropertyMetadataOptions.AffectsParentArrange));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Staticka metoda pre AP.
        public static void SetLeft(DependencyObject Obj, double Value)
        {
            Obj.SetValue(LeftProperty, Value);
        }
//------------------------------------------------------------------------------
		// Staticka metoda pre AP.
        public static double GetLeft(DependencyObject Obj)
        {
            return (double)Obj.GetValue(LeftProperty);
        }
//------------------------------------------------------------------------------
		// Staticka metoda pre AP.
        public static void SetTop(DependencyObject Obj, double Value)
        {
            Obj.SetValue(TopProperty, Value);
        }
//------------------------------------------------------------------------------
		// Staticka metoda pre AP.
        public static double GetTop(DependencyObject Obj)
        {
            return (double)Obj.GetValue(TopProperty);
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
			Console.WriteLine("SizeAvailable: [{0},{1}] !",SizeAvailable.Width,SizeAvailable.Height);

			// !!! Measure() pre CHILDREN ELEMENTS MUSI BYT VOLANA, aby si tieto ELEMENTS vypocitali DesiredSize.
            foreach (UIElement Child in InternalChildren)
                Child.Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));

            return(base.MeasureOverride(SizeAvailable));
        }
//------------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size SizeFinal)
        {
			Console.WriteLine("SizeFinal: [{0},{1}] !",SizeFinal.Width,SizeFinal.Height);

            foreach (UIElement Child in InternalChildren)
                Child.Arrange(new Rect(new Point(GetLeft(Child), GetTop(Child)), Child.DesiredSize));

            return(SizeFinal);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------