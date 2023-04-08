using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
//------------------------------------------------------------------------
namespace CustomDrawnElementsLibrary
{
//------------------------------------------------------------------------
    public class CustomDrawnDecorator : Decorator
    {
//------------------------------------------------------------------------
        static CustomDrawnDecorator()
        {
            CustomDrawnElement.BackgroundColorProperty.AddOwner(typeof(CustomDrawnDecorator));
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public Color BackgroundColor
        {
            get
            {
                return (Color)GetValue(CustomDrawnElement.BackgroundColorProperty);
            }
            set
            {
                SetValue(CustomDrawnElement.BackgroundColorProperty, value);
            }
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Vypocitava sa RadialGradientBrush podla pozicie mysky.
        private Brush GetForegroundBrush()
        {
            if (IsMouseOver==false)
            {
                return(new SolidColorBrush(BackgroundColor));
            }
            else
            {
                RadialGradientBrush		Brush=new RadialGradientBrush(Colors.White, BackgroundColor);
                Point					AbsoluteGradientOrigin=Mouse.GetPosition(this);
                Point					RelativeGradientOrigin=new Point(AbsoluteGradientOrigin.X / base.ActualWidth, AbsoluteGradientOrigin.Y/base.ActualHeight);

                Brush.GradientOrigin=RelativeGradientOrigin;
                Brush.RadiusX=0.2;
                Brush.Center=RelativeGradientOrigin;
                Brush.Freeze();

                return(Brush);
            }
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		// Tu dochadza k samotnemu renderingu.
        protected override void OnRender(DrawingContext DC)
        {
            base.OnRender(DC);

            Rect			Bounds=new Rect(0, 0, base.ActualWidth, base.ActualHeight);

            DC.DrawRectangle(GetForegroundBrush(), null, Bounds);
        }
//------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs E)
        {
            base.OnMouseMove(E);
			// Vyvolam repaint okna.
            this.InvalidateVisual();
        }
//------------------------------------------------------------------------
        protected override void OnMouseLeave(MouseEventArgs E)
        {
            base.OnMouseLeave(E);
			// Vyvolam repaint okna.
            this.InvalidateVisual();
        }
//------------------------------------------------------------------------
		// Pretazujem aj MeasureOverride(), kedze sa jedna o Decorator, ktory ma Child objekt.
        protected override Size MeasureOverride(Size Constraint)
        {
            UIElement			Child=this.Child;

            if (Child!=null)
            {
                Child.Measure(Constraint);

                return(Child.DesiredSize);
            }
            else
            {
                return(new Size());
            }
        }
//------------------------------------------------------------------------
    }
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------