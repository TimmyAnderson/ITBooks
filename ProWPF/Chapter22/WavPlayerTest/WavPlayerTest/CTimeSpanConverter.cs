using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Globalization;
//------------------------------------------------------------------------
namespace WavPlayerTest
{
//------------------------------------------------------------------------
	public class CTimeSpanConverter : IValueConverter
	{
//------------------------------------------------------------------------
		public object Convert(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
            try
            {
                TimeSpan	Time=(TimeSpan) Value;

                return(Time.TotalSeconds);
            }
            catch
            {
                return(0);
            }
		}
//------------------------------------------------------------------------
		public object ConvertBack(object Value, Type TargetType, object Parameter, CultureInfo Culture)
		{
            double			Seconds=(double) Value;

            return(TimeSpan.FromSeconds(Seconds));
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------