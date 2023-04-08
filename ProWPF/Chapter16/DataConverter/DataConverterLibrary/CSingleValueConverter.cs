using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Globalization;
using System.Windows.Data;
//------------------------------------------------------------------------
namespace DataConverterLibrary
{
//------------------------------------------------------------------------
	[ValueConversion(typeof(string),typeof(string))]
	public class CSingleValueConverter : IValueConverter
	{
//------------------------------------------------------------------------
		public object Convert(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
			Debug.WriteLine("CSingleValueConverter.Convert() !");

			string			In=Value.ToString();
			string			Ret=In.ToUpper();

			return(Ret);
		}
//------------------------------------------------------------------------
		public object ConvertBack(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
			Debug.WriteLine("CSingleValueConverter.ConvertBack() !");

			string			In=Value.ToString();
			string			Up=In.ToUpper();
			string			Down=In.ToLower();
			string			Ret=string.Format("{0}{1}",Up[0],Down.Substring(1));

			return(Ret);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------