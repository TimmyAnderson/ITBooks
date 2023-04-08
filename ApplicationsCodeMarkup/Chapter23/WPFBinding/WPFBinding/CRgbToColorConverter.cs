using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace WPFBinding
{
//-------------------------------------------------------------------------------------------------------
	public class CRgbToColorConverter : IMultiValueConverter
	{
//-------------------------------------------------------------------------------------------------------
        public object Convert(object[] Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
            Color			Clr=Color.FromRgb((byte)(double)Value[0], (byte)(double)Value[1], (byte)(double)Value[2]);

            if (TypeTarget==typeof(Color))
                return(Clr);

            if (TypeTarget==typeof(Brush))
                return(new SolidColorBrush(Clr));

            return(null);
        }
//-------------------------------------------------------------------------------------------------------
        public object[] ConvertBack(object Value, Type[] TypeTarget, object Param, CultureInfo Culture)
        {
            Color			Clr;
            object[]		Primaries=new object[3];

            if ((Value is Color)==true)
                Clr=(Color) Value;
            else if ((Value is SolidColorBrush)==true)
                Clr = (Value as SolidColorBrush).Color;
            else
                return(null);

            Primaries[0]=Clr.R;
            Primaries[1]=Clr.G;
            Primaries[2]=Clr.B;

            return(Primaries);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------