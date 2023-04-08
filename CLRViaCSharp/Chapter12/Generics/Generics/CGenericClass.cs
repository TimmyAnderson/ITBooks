using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	public class CGenericClass<TType> : IGenericInterface<TType>
	{
//-------------------------------------------------------------------------------------------------------
		public static int										MStaticValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void InterfaceMethod(TType Parameter)
		{
			Console.WriteLine(string.Format("CGenericClass<TType>.InterfaceMethod() METHOD (in CLASS) CALLED with GENERICS parameter: [{0}], Type: [{1}] !",Parameter,typeof(TType).Name));
		}
//-------------------------------------------------------------------------------------------------------
		public void ClassMethod(TType Parameter)
		{
			Console.WriteLine(string.Format("CGenericClass<TType>.ClassMethod() CALLED with GENERICS parameter: [{0}], Type: [{1}] !",Parameter,typeof(TType).Name));
		}
//-------------------------------------------------------------------------------------------------------
		public void GenericMethod<TParameter>(TParameter Parameter1, TType Parameter2)
		{
			Console.WriteLine(string.Format("CGenericClass<TType>.GenericMethod<TParameter>() CALLED with GENERICS Parameter1: [{0}], Type1: [{1}], Parameter2: [{2}], Type1: [{3}] !",Parameter1,typeof(TParameter).Name,Parameter2,typeof(TType).Name));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------