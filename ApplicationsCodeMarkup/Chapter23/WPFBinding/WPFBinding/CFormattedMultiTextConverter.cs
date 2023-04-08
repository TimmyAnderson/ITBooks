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
	public class CFormattedMultiTextConverter : IMultiValueConverter
	{
//-------------------------------------------------------------------------------------------------------
        public object Convert(object[] Value, Type TypeTarget, object Param, CultureInfo Culture)
        {
			// Vsetky objekty z MultiBidning su zaslane ako parametre Format() a ConverterParameter obsahuje formatovaci parameter.
            return(string.Format((string) Param, Value));
        }
//-------------------------------------------------------------------------------------------------------
        public object[] ConvertBack(object Value, Type[] TypeTarget, object Param, CultureInfo Culture)
        {
            return(null);
        }
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------