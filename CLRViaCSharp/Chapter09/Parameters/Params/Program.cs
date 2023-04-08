using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Params
{
//-------------------------------------------------------------------------------------------------------
	public class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CTestClass											TC=new CTestClass();

			int													Result1=TC.Add();

			Console.WriteLine(string.Format("Result1: [{0}] !",Result1));

			int													Result2=TC.Add(1);

			Console.WriteLine(string.Format("Result2: [{0}] !",Result2));

			// Je volana NON-PARAMS metoda.
			int													Result3=TC.Add(1,2);

			Console.WriteLine(string.Format("Result3: [{0}] !",Result3));

			int													Result4=TC.Add(1,2,3);

			Console.WriteLine(string.Format("Result4: [{0}] !",Result4));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CTestClass											TC=new CTestClass();

			TC.AddAndPrint("BIG SUM 1",1,2,3);

			TC.AddAndPrint("BIG SUM 2",new int[]{1,2,3});

			TC.AddAndPrint("BIG SUM 3",new int[0]);

			TC.AddAndPrint("BIG SUM 4",null);
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