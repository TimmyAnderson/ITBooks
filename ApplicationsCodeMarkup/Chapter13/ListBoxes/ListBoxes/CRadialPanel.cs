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
namespace ListBoxes
{
//------------------------------------------------------------------------------
	public class CRadialPanel : Panel
	{
//------------------------------------------------------------------------------
        public static readonly DependencyProperty	OrientationProperty;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        private bool								MShowPieLines;
        private double								MAngleEach;
        private Size								MSizeLargest;
        private double								MRadius;
        private double								MOuterEdgeFromCenter;
        private double								MInnerEdgeFromCenter;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CRadialPanel()
        {
            OrientationProperty=DependencyProperty.Register("Orientation", typeof(ERadialPanel), typeof(CRadialPanel),new FrameworkPropertyMetadata(ERadialPanel.ByWidth,FrameworkPropertyMetadataOptions.AffectsMeasure));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public ERadialPanel							Orientation
        {
            get
			{
				return((ERadialPanel)GetValue(OrientationProperty));
			}
            set
			{
				SetValue(OrientationProperty, value);
			}
        }
//------------------------------------------------------------------------------
        public bool									ShowPieLines
        {
            get
            {
                return(MShowPieLines);
            }
            set
            {
                if (MShowPieLines==value)
                    InvalidateVisual();

                MShowPieLines=value;
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
            if (InternalChildren.Count==0)
                return(new Size(0, 0));

            MAngleEach=360.0/InternalChildren.Count;
            MSizeLargest=new Size(0, 0);

            foreach (UIElement Child in InternalChildren)
            {
                Child.Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));

                MSizeLargest.Width=Math.Max(MSizeLargest.Width, Child.DesiredSize.Width);

                MSizeLargest.Height=Math.Max(MSizeLargest.Height, Child.DesiredSize.Height);
            }

            if (Orientation==ERadialPanel.ByWidth)
            {
                MInnerEdgeFromCenter=MSizeLargest.Width/2/Math.Tan(Math.PI*MAngleEach/360);
                MOuterEdgeFromCenter=MInnerEdgeFromCenter+MSizeLargest.Height; 

                MRadius=Math.Sqrt(Math.Pow(MSizeLargest.Width/2, 2) + Math.Pow(MOuterEdgeFromCenter, 2));
            }
            else
            {
                MInnerEdgeFromCenter = MSizeLargest.Height/2/Math.Tan(Math.PI*MAngleEach/360);
                MOuterEdgeFromCenter = MInnerEdgeFromCenter+MSizeLargest.Width;

                MRadius=Math.Sqrt(Math.Pow(MSizeLargest.Height/2, 2) + Math.Pow(MOuterEdgeFromCenter, 2));
            }

            return(new Size(2*MRadius, 2*MRadius));
        }
//------------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size SizeFinal)
        {
            double			AngleChild=0;
            Point			PTCenter=new Point(SizeFinal.Width/2, SizeFinal.Height/2);
            double			Multiplier=Math.Min(SizeFinal.Width/(2*MRadius), SizeFinal.Height/(2*MRadius));

            foreach (UIElement Child in InternalChildren)
            {
                Child.RenderTransform=Transform.Identity;

                if (Orientation==ERadialPanel.ByWidth)
                    Child.Arrange(new Rect(PTCenter.X-(Multiplier*MSizeLargest.Width/2), PTCenter.Y-(Multiplier*MOuterEdgeFromCenter), Multiplier*MSizeLargest.Width, Multiplier*MSizeLargest.Height));
                else
                    Child.Arrange(new Rect(PTCenter.X+Multiplier*MInnerEdgeFromCenter,PTCenter.Y-Multiplier*MSizeLargest.Height/2,Multiplier*MSizeLargest.Width,Multiplier*MSizeLargest.Height));

                Point		PT=TranslatePoint(PTCenter, Child);

                Child.RenderTransform=new RotateTransform(AngleChild, PT.X, PT.Y);

                AngleChild+=MAngleEach;
            }

            return(SizeFinal);
        }
//------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            base.OnRender(DC);

            if (ShowPieLines==true)
            {
                Point		PTCenter=new Point(RenderSize.Width/2, RenderSize.Height/2);
                double		Multiplier=Math.Min(RenderSize.Width/(2*MRadius),RenderSize.Height/(2*MRadius));
                Pen			LPen=new Pen(SystemColors.WindowTextBrush, 1);

                LPen.DashStyle=DashStyles.Dash;

                DC.DrawEllipse(null, LPen, PTCenter, Multiplier*MRadius, Multiplier*MRadius);

                double		AngleChild=-MAngleEach/2;

                if (Orientation==ERadialPanel.ByWidth)
                    AngleChild+=90;

                foreach (UIElement Child in InternalChildren)
                {
                    DC.DrawLine(LPen, PTCenter, new Point(PTCenter.X+Multiplier*MRadius*Math.Cos(2*Math.PI*AngleChild / 360),PTCenter.Y+Multiplier*MRadius*Math.Sin(2*Math.PI*AngleChild/360)));
                    AngleChild+=MAngleEach;
                }
            }
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------