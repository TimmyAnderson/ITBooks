using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	// !!! Kedze BASE CLASS vyzaduje ako CONSTRAINT implementaciu INTERFACE IComparable, TYPE PARAMETER MUSI v DERIVED CLASS ho tiez implementovat.
	public sealed class CConstrainsDerivedClass<TClassParameter> : CConstrainsBaseClass<TClassParameter>  where TClassParameter : IComparable
	{
//-------------------------------------------------------------------------------------------------------
		// !!! KEYWORD [where] sa NESMIE v OVERRIDEN METHODS NESMIE pouzit.
		public override void VirtualMethod<TMethodParameter>() //where TMethodParameter : ICloneable
		{
			Console.WriteLine("VirtualMethod<TMethodParameter>() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Overloaded()
		{
			Console.WriteLine("Overloaded() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Overloaded<TParam>()
		{
			Console.WriteLine("Overloaded<TParam>() CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		/*
		// !!! METHODS NEMOZU byt OVERLOADED iba na zaklade ineho CONSTRAINT.
		public void Overloaded<TParam>() where TParam : ICloneable
		{
			Console.WriteLine("Overloaded<TParam>() with CONSTRAINTS CALLED !");
		}
		*/
//-------------------------------------------------------------------------------------------------------
		// !!! METHODS MOZU byt OVERLOADED na zaklade ARITY.
		public void Overloaded<TParam1,TParam2>()
		{
			Console.WriteLine("Overloaded<TParam1,TParam2>() with CONSTRAINTS CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------