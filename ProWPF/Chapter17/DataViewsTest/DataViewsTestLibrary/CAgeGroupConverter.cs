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
using System.ComponentModel;
using System.Globalization;
using DataViewsTestLibrary;
//------------------------------------------------------------------------
namespace DataViewsTestLibrary
{
//------------------------------------------------------------------------
	// !!! CUSTOM Converter, ktory vytvori 3 Groups pre Pre-teen, Teenegerov a Adults.
	public class CAgeGroupConverter : IValueConverter
	{
//------------------------------------------------------------------------
		public object Convert(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
			int				Age=(int) Value;

			if (Age<=12)
				return("Preteen");
			else if (Age<=19)
				return("Teeneger");
			else
				return("Adult");
		}
//------------------------------------------------------------------------
		public object ConvertBack(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
			throw(new Exception("The method or operation is not implemented."));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------