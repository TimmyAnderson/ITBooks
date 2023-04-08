using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Controls;
using System.Windows;
//------------------------------------------------------------------------
namespace CustomPanelLibrary
{
//------------------------------------------------------------------------
	// Specialny WrapPanel, ktroy umoznuje definovat jeden Element na ktorom sa zalomi riadok a bude sa pokracovat s umiestnovanim Element na nasledujucom.
    public class WrapBreakPanel : Panel
    {
//------------------------------------------------------------------------
		// Definuje Element po ktorom sa zalomi riadok.
        public static DependencyProperty	LineBreakBeforeProperty;
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        static WrapBreakPanel()
        {
            FrameworkPropertyMetadata	Metadata=new FrameworkPropertyMetadata();

            Metadata.AffectsArrange=true;
            Metadata.AffectsMeasure=true;
            LineBreakBeforeProperty=DependencyProperty.RegisterAttached("LineBreakBefore", typeof(bool), typeof(WrapBreakPanel), Metadata);
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        public static void SetLineBreakBefore(UIElement Element, bool Value)
        {
            Element.SetValue(LineBreakBeforeProperty, Value);
        }
//------------------------------------------------------------------------
        public static Boolean GetLineBreakBefore(UIElement Element)
        {
            return((bool) Element.GetValue(LineBreakBeforeProperty));
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        private void ArrangeLine(double Y, double LineHeight, int Start, int End)
        {
            double					X=0;
            UIElementCollection		Xhildren=InternalChildren;

            for (int i=Start;i<End;i++)
            {
                UIElement			Child=Children[i];

                Child.Arrange(new Rect(X, Y, Child.DesiredSize.Width, LineHeight));
                X+=Child.DesiredSize.Width;
            }
        }
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
        protected override Size MeasureOverride(Size Constraint)
        {
            Size				CurrentLineSize=new Size();
            Size				PanelSize=new Size();

            foreach (UIElement Element in base.InternalChildren)
            {
                Element.Measure(Constraint);

                Size			DesiredSize=Element.DesiredSize;
                                
                if (GetLineBreakBefore(Element)==true || CurrentLineSize.Width+DesiredSize.Width>Constraint.Width)
                {
                    // Switch to a new line (either because the element has requested it or space has run out).
                    PanelSize.Width=Math.Max(CurrentLineSize.Width, PanelSize.Width);
                    PanelSize.Height+=CurrentLineSize.Height;
                    CurrentLineSize=DesiredSize;

                    // If the element is too wide to fit using the maximum width of the line, just give it a separate line.
                    if (DesiredSize.Width>Constraint.Width) 
                    {
                        PanelSize.Width=Math.Max(DesiredSize.Width, PanelSize.Width);
                        PanelSize.Height+=DesiredSize.Height;
                        CurrentLineSize=new Size();
                    }
                }
                else 
                {
                    // Keep adding to the current line.
                    CurrentLineSize.Width+=DesiredSize.Width;

                    // Make sure the line is as tall as its tallest element.
                    CurrentLineSize.Height=Math.Max(DesiredSize.Height, CurrentLineSize.Height);
                }
            }

            // Return the size required to fit all elements.
            // Ordinarily, this is the width of the constraint, and the height is based on the size of the elements.
            // However, if an element is wider than the width given to the panel, the desired width will be the width of that line.
            PanelSize.Width=Math.Max(CurrentLineSize.Width, PanelSize.Width);
            PanelSize.Height+=CurrentLineSize.Height;

            return(PanelSize);
        }
//------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size ArrangeBounds)
        {
            int					FirstInLine = 0;
            Size				CurrentLineSize=new Size();
            double				AccumulatedHeight = 0;
            UIElementCollection Elements=base.InternalChildren;

            for (int i=0;i<Elements.Count;i++)
            {
                Size			DesiredSize=Elements[i].DesiredSize;

				// Need to switch to another line.
                if (GetLineBreakBefore(Elements[i])==true || CurrentLineSize.Width+DesiredSize.Width>ArrangeBounds.Width)
                {
                    ArrangeLine(AccumulatedHeight, CurrentLineSize.Height, FirstInLine, i);
                    AccumulatedHeight+=CurrentLineSize.Height;
                    CurrentLineSize=DesiredSize;

					// The element is wider then the constraint - give it a separate line.
					if (DesiredSize.Width>ArrangeBounds.Width) 
                    {
                        ArrangeLine(AccumulatedHeight, DesiredSize.Height, i, ++i);
                        AccumulatedHeight+=DesiredSize.Height;
                        CurrentLineSize=new Size();
                    }

                    FirstInLine=i;
                }
				// Continue to accumulate a line.
                else 
                {
                    CurrentLineSize.Width+=DesiredSize.Width;
                    CurrentLineSize.Height=Math.Max(DesiredSize.Height, CurrentLineSize.Height);
                }
            }

            if (FirstInLine<Elements.Count)
                ArrangeLine(AccumulatedHeight, CurrentLineSize.Height, FirstInLine, Elements.Count);

            return(ArrangeBounds);
        }
//------------------------------------------------------------------------
    }
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------