using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Strings
{
//-------------------------------------------------------------------------------------------------------
	// !!! CUSTOM implementacia INTERFACE IFormatProvider, ktora zaroven implementuje aj INTERFACE ICustomFormatter.
	public sealed class CCustomFormatterAddBrackets : IFormatProvider, ICustomFormatter
	{
//-------------------------------------------------------------------------------------------------------
		public object GetFormat(Type FormatType)
		{
			if (FormatType==typeof(ICustomFormatter))
			{
				return(this);
			}
			else
			{
				// CLASS CultureInfo implementuje INTERFACE IFormatProvider.
				return(Thread.CurrentThread.CurrentCulture);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string Format(string Format, object Argument, IFormatProvider FormatProvider)
		{
			Console.WriteLine(string.Format("METHOD ICustomFormatter.Format() CALLED with Format [{0}] and Argument [{1}] !",Format,Argument));

			if (Format=="()" || Format=="[]")
			{
				string											FormattedString=string.Format("{0}{1}{2}",Format[0],Argument,Format[1]);

				return(FormattedString);
			}
			else
			{
				return(Argument.ToString());
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------