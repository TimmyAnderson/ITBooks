using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	public static class CConversionSamples
	{
//-------------------------------------------------------------------------------------------------------
		public static void Sample1<TTypeBase,TTypeDerived>(TTypeDerived Object) where TTypeDerived : TTypeBase
		{
			// !!! C# povoli CONVERSION.
			TTypeBase											Base=Object;

			Console.WriteLine(string.Format("Base [{0}] !",Base));
		}
//-------------------------------------------------------------------------------------------------------
		public static void Sample2<TType,TInnerType>(TType Object) where TType : IEnumerable<TInnerType>
		{
			// !!! C# povoli CONVERSION, pretoze IEnumerable<TType> implementuje IEnumerable.
			IEnumerable											Other=Object;

			Console.WriteLine(string.Format("Other [{0}] !",Other));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------