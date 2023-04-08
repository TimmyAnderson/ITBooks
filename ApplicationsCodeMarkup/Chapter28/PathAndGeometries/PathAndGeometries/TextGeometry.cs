using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace PathAndGeometries
{
//-------------------------------------------------------------------------------------------------------
	public class TextGeometry
	{
//-------------------------------------------------------------------------------------------------------
        private string											MTxt="";
        private FontFamily										MFntfam=new FontFamily();
        private FontStyle										MFntstyle=FontStyles.Normal;
        private FontWeight										MFntwt=FontWeights.Normal;
        private FontStretch										MFntstr=FontStretches.Normal;
        private double											MEmsize=24;
        private Point											MPtOrigin=new Point(0, 0);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public string											Text
        {
            get
			{
				return(MTxt);
			}
            set
			{
				MTxt=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public FontFamily										FontFamily
        {
            get
			{
				return(MFntfam);
			}
            set
			{
				MFntfam=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public FontStyle										FontStyle
        {
            get
			{
				return(MFntstyle);
			}
            set
			{
				MFntstyle=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public FontWeight										FontWeight
        {
            get
			{
				return(MFntwt);
			}
            set
			{
				MFntwt=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public FontStretch										FontStretch
        {
            get
			{
				return(MFntstr);
			}
            set
			{
				MFntstr=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public double											FontSize
        {
            get
			{
				return(MEmsize);
			}
            set
			{
				MEmsize=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public Point											Origin
        {
            get
			{
				return(MPtOrigin);
			}
            set
			{
				MPtOrigin=value;
			}
        }
//-------------------------------------------------------------------------------------------------------
        public Geometry											Geometry
        {
            get
            {
                FormattedText		Formtxt=new FormattedText(Text, CultureInfo.CurrentCulture, FlowDirection.LeftToRight, new Typeface(FontFamily, FontStyle, FontWeight, FontStretch), FontSize, Brushes.Black);

                return(Formtxt.BuildGeometry(Origin));
            }
        }
//-------------------------------------------------------------------------------------------------------
        public PathGeometry										PathGeometry
        {
            get
            {
                return(PathGeometry.CreateFromGeometry(Geometry));
            }
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------