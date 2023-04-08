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
namespace SingleChildElements
{
//------------------------------------------------------------------------------
	public class CComplexEllipseWithChild : CComplexEllipse
	{
//------------------------------------------------------------------------------
		// Tu sa uklada CHILD ELEMENT.
        private UIElement							MChild;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Kedze ELEMENT moze mat iba jeden CHILD, tak moze vracat iba 1, alebo 0.
        protected override int						VisualChildrenCount
        {
            get
            {
                return((Child!=null) ? 1 : 0);
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        public UIElement							Child
        {
            get
            {
                return(MChild);
            }
            set
            {
                if (MChild!=null)
                {
					// Ak uz CHILD bol definovany, tak ho odstranim z VISUAL i LOGICAL TREE.
                    RemoveVisualChild(MChild);
                    RemoveLogicalChild(MChild);
                }

                if ((MChild=value)!=null)
                {
					// Pridam CHILD do VISUAL i LOGICAL TREE.
                    AddVisualChild(MChild);
                    AddLogicalChild(MChild);
                }
            }
        }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
        protected override Visual GetVisualChild(int Index)
        {
            if (Index>0 || Child==null)
                throw(new ArgumentOutOfRangeException("Invalid Index !","Index"));

            return(Child);
        }
//------------------------------------------------------------------------------
		// Urci velkost potrebnu pre rendering CUSTOM ELEMENT.
        protected override Size MeasureOverride(Size SizeAvailable)
        {
            Size			SizeDesired=new Size(0,0);

            if (Stroke!=null)
            {
				// Ak je definovany Stoke, tak pozadovana vekost bude 2* STROKE THICKNESS.
                SizeDesired.Width+=2*Stroke.Thickness;
                SizeDesired.Height+=2*Stroke.Thickness;

				// !!! Vypocitam SizeAvailable pre CHILD ELEMENT.
                SizeAvailable.Width=Math.Max(0,SizeAvailable.Width-(2*Stroke.Thickness));
                SizeAvailable.Height=Math.Max(0,SizeAvailable.Height-(2*Stroke.Thickness));
            }

            if (Child!=null)
            {
				// Ak je definovany Child, tak mu priradim SizeAvailable (ta je bud z PARENT ELEMENT CUSTOM ELEMENTU, alebo ak je definovane Stroke, tak SizeAvailable je vypocitany podla velkosti Stoke CUSTOM ELEMENT.
                Child.Measure(SizeAvailable);

				// !!! Metoda Child.Measure() NASTAVILA pre CHILD hodnotu DesiredSize.
                SizeDesired.Width+=Child.DesiredSize.Width;
                SizeDesired.Height+=Child.DesiredSize.Height;
            }

            return(SizeDesired);
        }
//------------------------------------------------------------------------------
        protected override Size ArrangeOverride(Size SizeFinal)
        {
            if (Child!=null)
            {
				// Vypocitam RECTANGLE do ktoreho sa bude renderovat CHILD ELEMENT.
                Rect		Rectangle=new Rect(new Point((SizeFinal.Width-Child.DesiredSize.Width)/2,(SizeFinal.Height-Child.DesiredSize.Height)/2),Child.DesiredSize);

				// Pridelim RECTANGLE vypocitany RECTANGLE, ale AK NAHODOU MA CHILDREN mohol i on vypocitat POZICIE svojich CHILDREN ELEMENTS.
                Child.Arrange(Rectangle);
            }

            return(SizeFinal);
        }
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------