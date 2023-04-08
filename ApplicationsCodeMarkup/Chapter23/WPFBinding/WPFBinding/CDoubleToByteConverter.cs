using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.Windows;
using System.Windows.Data;
//-------------------------------------------------------------------------------------------------------
namespace WPFBinding
{
//-------------------------------------------------------------------------------------------------------
    [ValueConversion(typeof(double), typeof(byte))]
	public class CDoubleToByteConverter : IValueConverter
	{
//-------------------------------------------------------------------------------------------------------
        public object Convert(object Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
            return((byte)(double) Value);
        }
//-------------------------------------------------------------------------------------------------------
        public object ConvertBack(object Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
            return((double) Value);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------