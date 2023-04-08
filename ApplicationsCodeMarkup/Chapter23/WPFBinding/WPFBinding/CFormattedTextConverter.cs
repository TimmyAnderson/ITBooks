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
	public class CFormattedTextConverter : IValueConverter
	{
//-------------------------------------------------------------------------------------------------------
        public object Convert(object Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
			// Ak parameter je typu string tak obsahuje formatovanie DateTime.
            if ((Param is string)==true)
                return(string.Format(Param as string, Value));

            return(Value.ToString());
		}
//-------------------------------------------------------------------------------------------------------
        public object ConvertBack(object Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
            return(null);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------