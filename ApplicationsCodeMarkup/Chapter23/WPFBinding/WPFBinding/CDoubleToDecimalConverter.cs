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
    [ValueConversion(typeof(double), typeof(decimal))]
	public class CDoubleToDecimalConverter : IValueConverter
	{
//-------------------------------------------------------------------------------------------------------
        public object Convert(object Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
            decimal			Num=new decimal((double)Value);

            if (Param!=null)
                Num=decimal.Round(Num, int.Parse(Param as string));

            return(Num);
        }
//-------------------------------------------------------------------------------------------------------
        public object ConvertBack(object Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
            return(decimal.ToDouble((decimal) Value));
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------