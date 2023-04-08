using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace Generics
{
//-------------------------------------------------------------------------------------------------------
	public static class COperators
	{
//-------------------------------------------------------------------------------------------------------
		public static void Test1<TType>(TType Value)
		{
			// !!! CLR UMOZNUJE pouzit OPERATORS v GENERIC CONSTRUCTS IBA pre OPERATOR== a OPERATOR!= a aj to iba pri porovnani s NULL VALUE.
			if (Value==null)
			{
				Console.WriteLine("VALUE is NULL !");
			}
			else
			{
				Console.WriteLine("VALUE is NOT NULL !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void Test2<TType>(TType Value)
		{
			// !!! CLR UMOZNUJE pouzit OPERATORS v GENERIC CONSTRUCTS IBA pre OPERATOR== a OPERATOR!= a aj to iba pri porovnani s NULL VALUE.
			if (Value!=null)
			{
				Console.WriteLine("VALUE is NOT NULL !");
			}
			else
			{
				Console.WriteLine("VALUE is NULL !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		/*
		public static void Test3<TType>(TType Value1, TType Value2)
		{
			// !!! CLR NEUMOZNUJE pouzit OPERATORS v GENERIC CONSTRUCTS.
			if (Value1==Value2)
			{
				Console.WriteLine("Result TRUE !");
			}
			else
			{
				Console.WriteLine("Result FALSE !");
			}
		}
		*/
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------