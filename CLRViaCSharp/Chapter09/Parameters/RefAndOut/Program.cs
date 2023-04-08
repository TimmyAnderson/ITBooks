using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RefAndOut
{
//-------------------------------------------------------------------------------------------------------
	public class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CTestClass											TC=new CTestClass();

			int													Value1=4;

			TC.Add(Value1);

			Console.WriteLine(string.Format("Value1: [{0}] !",Value1));

			int													Value2=4;

			TC.Add(ref Value2);

			Console.WriteLine(string.Format("Value2: [{0}] !",Value2));

			/*
			string												Text1="Timmy";
			string												Text2="Anderson";

			// Toto sa NEPREKOMPILUJE, pretoze TYP pri 'ref' a 'out' parametroch MUSI BYT TOTOZNY s TYPOM UVEDENYM V DEKLARACII metody.
			TC.Swap(ref Text1,ref Text2);

			Console.WriteLine(string.Format("Text1: [{0}], Text2: [{1}] !",Text1,Text2));
			*/

			string												Text1="Timmy";
			string												Text2="Anderson";

			object												Temp1=Text1;
			object												Temp2=Text2;

			// Toto sa NEPREKOMPILUJE, pretoze TYP pri 'ref' a 'out' parametroch MUSI BYT TOTOZNY s TYPOM UVEDENYM V DEKLARACII metody.
			TC.Swap(ref Temp1, ref Temp2);

			Console.WriteLine(string.Format("Temp1: [{0}], Temp2: [{1}] !",Temp1,Temp2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CTestClass											TC=new CTestClass();
			string												Value;

			TC.GetValue(out Value);

			Console.WriteLine(string.Format("Value: [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------