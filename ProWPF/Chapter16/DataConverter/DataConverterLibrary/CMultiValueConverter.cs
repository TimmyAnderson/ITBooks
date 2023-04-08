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
	public class CMultiValueConverter : IMultiValueConverter
	{
//------------------------------------------------------------------------
		public object Convert(object[] Values, Type TargetType, object Parameter, CultureInfo Culture)
		{
			Debug.WriteLine("CMultiValueConverter.Convert() !");

			StringBuilder			SB=new StringBuilder();

			for (int i=0;i<Values.Length;i++)
			{
				if (i!=0)
					SB.Append(" ");

				SB.Append(Values[i].ToString());
			}

			return(SB.ToString());
		}
//------------------------------------------------------------------------
		public object[] ConvertBack(object Value, Type[] TargetTypes, object Parameter, CultureInfo Culture)
		{
			Debug.WriteLine("CMultiValueConverter.ConvertBack() !");

			string			In=Value.ToString();
			string[]		Values;
			int				Age=0;

			Values=In.Split(new string[]{" "},StringSplitOptions.RemoveEmptyEntries);

			if (Values.Length!=3)
				return(null);

			if (Int32.TryParse(Values[2],out Age)==false)
				return(null);

			// !!! Aj Age posielam ako string, kedze konverujem na TextBox.Text.
			// Ak by som ukladal data do CName, potom by bol 'int' ako Age OK.
			return(new object[]{Values[0],Values[1],Age.ToString()});
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------