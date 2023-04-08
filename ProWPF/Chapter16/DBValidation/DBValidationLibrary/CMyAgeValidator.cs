using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Globalization;
//------------------------------------------------------------------------
namespace DBValidationLibrary
{
//------------------------------------------------------------------------
	public class CMyAgeValidator : ValidationRule
	{
//------------------------------------------------------------------------
		public override ValidationResult Validate(object Value, CultureInfo CultureInfo)
		{
			string			In=Value.ToString();
			int				Age;

			if (Int32.TryParse(In, out Age)==false)
				return(new ValidationResult(false,"Value is not NUMBER !"));

			if (Age<5 || Age>120)
				return(new ValidationResult(false,"You sholud be DEAD !"));

			return(new ValidationResult(true,null));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------