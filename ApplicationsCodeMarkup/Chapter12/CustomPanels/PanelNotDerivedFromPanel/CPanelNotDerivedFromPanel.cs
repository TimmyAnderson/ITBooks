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
namespace PanelNotDerivedFromPanel
{
//------------------------------------------------------------------------------
	// !!! Nededim z Panel.
	public class CPanelNotDerivedFromPanel : FrameworkElement
	{
//------------------------------------------------------------------------------
        // Dependency Property.
        public static readonly DependencyProperty	BackgroundProperty;
//------------------------------------------------------------------------------
        // Kolekcia CHILD OBJECTS.
        private List<UIElement>						MChildren=new List<UIElement>();
        private Size								MSizeChildrenTotal;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        static CPanelNotDerivedFromPanel()
        {
            BackgroundProperty=DependencyProperty.Register("Background", typeof(Brush), typeof(CPanelNotDerivedFromPanel),new FrameworkPropertyMetadata(null,FrameworkPropertyMetadataOptions.AffectsRender));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public Brush								Background
        {
            get
			{
				return((Brush)GetValue(BackgroundProperty));
			}
            set
			{
				SetValue(BackgroundProperty, value);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        // Overridden properties and methods.
        protected override int						VisualChildrenCount
        {
            get
			{
				return(MChildren.Count);
			}
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Visual GetVisualChild(int Index)
        {
            if (Index>=MChildren.Count)
                throw(new ArgumentOutOfRangeException("Index"));

            return(MChildren[Index]);
        }
//------------------------------------------------------------------------------
        protected override Size MeasureOverride(Size SizeAvailable)
        {
            MSizeChildrenTotal=new Size(0, 0);

            foreach (UIElement Child in MChildren)
            {
				// Kazdy CHILD dostane ako SizeAvailable INFINITE.
                Child.Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));

				// Vypocitam celkovu velkost, ktory CHILDREN zaberaju.
                MSizeChildrenTotal.Width+=Child.DesiredSize.Width;
                MSizeChildrenTotal.Height+=Child.DesiredSize.Height;
            }

            return(MSizeChildrenTotal);
        }
//------------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size SizeFinal)
        {
            Point			PTChild=new Point(0, 0);

            foreach (UIElement Child in MChildren)
            {
                Size		SizeChild=new Size(0, 0);

                SizeChild.Width=Child.DesiredSize.Width*(SizeFinal.Width/MSizeChildrenTotal.Width);
                SizeChild.Height=Child.DesiredSize.Height*(SizeFinal.Height/MSizeChildrenTotal.Height);

                Child.Arrange(new Rect(PTChild, SizeChild));

                PTChild.X+=SizeChild.Width;
                PTChild.Y+=SizeChild.Height;
            }

            return(SizeFinal);
        }
//------------------------------------------------------------------------------
        protected override void OnRender(DrawingContext DC)
        {
            DC.DrawRectangle(Background, null, new Rect(new Point(0, 0), RenderSize));
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public void Add(UIElement El)
        {
            MChildren.Add(El);

			// Pridany element musi byt pridany i do VISUAL a LOGICAL TREE.
            AddVisualChild(El);
            AddLogicalChild(El);
            InvalidateMeasure();
        }
//------------------------------------------------------------------------------
        public void Remove(UIElement El)
        {
            MChildren.Remove(El);

			// Odobrany element musi byt odobrany i z VISUAL a LOGICAL TREE.
            RemoveVisualChild(El);
            RemoveLogicalChild(El);
            InvalidateMeasure();
        }
//------------------------------------------------------------------------------
        public int IndexOf(UIElement El)
        {
            return(MChildren.IndexOf(El));
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------