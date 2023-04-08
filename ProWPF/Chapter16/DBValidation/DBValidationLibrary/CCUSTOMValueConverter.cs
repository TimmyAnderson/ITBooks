using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Globalization;
using System.Windows.Data;
//------------------------------------------------------------------------
namespace DBValidationLibrary
{
//------------------------------------------------------------------------
	//[ValueConversion(typeof(string),typeof(string))]
	public class CCUSTOMValueConverter : IValueConverter
	{
//------------------------------------------------------------------------
		public object Convert(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
			Debug.WriteLine("CCUSTOMValueConverter.Convert() !");

			string			In=Value.ToString();
			string			Ret=In.ToUpper();

			return(Ret);
		}
//------------------------------------------------------------------------
		public object ConvertBack(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
			Debug.WriteLine("CCUSTOMValueConverter.ConvertBack() !");

			string			In=Value.ToString();
			string			Up=In.ToUpper();
			string			Down=In.ToLower();

			if (In.Length==0)
				return(In);

			string			Ret=string.Format("{0}{1}",Up[0],Down.Substring(1));

			// !!! Umelo vygenerujem chybu - aby sa prejavila vo validacii.
			if (Up=="BUG" || Up=="15")
				throw(new ArgumentException("Value has value 'BUG' what is REALLY BUG !","Value"));

			return(Ret);
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------