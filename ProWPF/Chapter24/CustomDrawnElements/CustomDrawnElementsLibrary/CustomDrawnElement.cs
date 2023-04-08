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
    public class CustomDrawnElement : FrameworkElement
    {
//------------------------------------------------------------------------
        public static DependencyProperty		BackgroundColorProperty;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        static CustomDrawnElement()
        {
            FrameworkPropertyMetadata	Metadata=new FrameworkPropertyMetadata(Colors.Yellow);
			
			Metadata.AffectsRender=true;
            BackgroundColorProperty=DependencyProperty.Register("BackgroundColor", typeof(Color), typeof(CustomDrawnElement), Metadata);
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public Color							BackgroundColor
        {
            get
            {
                return((Color)GetValue(BackgroundColorProperty));
            }
            set
            {
                SetValue(BackgroundColorProperty, value);
            }
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private Brush GetForegroundBrush()
        {
            if (IsMouseOver==false)
            {
                return(new SolidColorBrush(BackgroundColor));
            }
            else
            {
                RadialGradientBrush			Brush=new RadialGradientBrush(Colors.White, BackgroundColor);
                Point						AbsoluteGradientOrigin=Mouse.GetPosition(this);
                Point						RelativeGradientOrigin=new Point(AbsoluteGradientOrigin.X / base.ActualWidth, AbsoluteGradientOrigin.Y / base.ActualHeight);

                Brush.GradientOrigin=RelativeGradientOrigin;
                Brush.Center=RelativeGradientOrigin;
                Brush.Freeze();

                return(Brush);
            }
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {            
            base.OnRender(DC);

            Rect				Bounds=new Rect(0, 0, base.ActualWidth, base.ActualHeight);

            DC.DrawRectangle(GetForegroundBrush(), null, Bounds);
        }
//------------------------------------------------------------------------
        protected override void OnMouseMove(MouseEventArgs E)
        {
            base.OnMouseMove(E);
            this.InvalidateVisual();
        }
//------------------------------------------------------------------------
        protected override void OnMouseLeave(MouseEventArgs E)
        {
            base.OnMouseLeave(E);
            this.InvalidateVisual();
        }
//------------------------------------------------------------------------
    }
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------