using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	public struct SGenericStruct<TType> : IGenericInterface<TType>
	{
//-------------------------------------------------------------------------------------------------------
		public void InterfaceMethod(TType Parameter)
		{
			Console.WriteLine(string.Format("Generics INTERFACE METHOD (in STRUCT) CALLED with GENERICS parameter: [{0}], Type: [{1}] !",Parameter,typeof(TType).Name));
		}
//-------------------------------------------------------------------------------------------------------
		public void StructMethod(TType Parameter)
		{
			Console.WriteLine(string.Format("Generics STRUCT METHOD CALLED with GENERICS parameter: [{0}], Type: [{1}] !",Parameter,typeof(TType).Name));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------