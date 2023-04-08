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
namespace DataTemplateTestLibrary
{
//------------------------------------------------------------------------
	[ValueConversion(typeof(CName),typeof(Brush))]
	public class CTeenagerShowerConverter : IValueConverter
	{
//------------------------------------------------------------------------
		public object Convert(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
			CName			Name=(CName) Value;

			if (Name.Age>=13 && Name.Age<=19)
				return(new SolidColorBrush(Colors.Red));
			else
				return(new SolidColorBrush(Colors.Green));
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