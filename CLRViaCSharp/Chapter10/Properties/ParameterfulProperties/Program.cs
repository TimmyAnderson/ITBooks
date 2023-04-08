using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ParameterfulProperties
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CName												Name1=new CName("Timmy","Anderson",12);
			CName												Name2=new CName("Atreyu","",12);
			CName												Name3=new CName("Jenny","Thompson",13);

			CNames												Names=new CNames();

			Names.Add(Name1);
			Names.Add(Name2);
			Names.Add(Name3);

			// Parameter je INTEGER.
			CName												GetName2=Names[1];

			// Parametrami su hodnoty NAMES.
			CName												GetName1=Names["Timmy","Anderson",12];
			CName												GetName3=Names["Jenny","Thompson",13];

			Console.WriteLine(string.Format("Name1: [{0}] !",Name1));
			Console.WriteLine(string.Format("Name2: [{0}] !",Name2));
			Console.WriteLine(string.Format("Name3: [{0}] !",Name3));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CName												Name1=new CName("Timmy","Anderson",12);
			CName												Name2=new CName("Atreyu","",12);
			CName												Name3=new CName("Jenny","Thompson",13);

			CNamesBase											Names=new CNamesDerived();

			Names[1]=Name1;
			Names[2]=Name2;
			Names[3]=Name3;

			// Parameter je INTEGER.
			CName												GetName2=Names[1];

			// Parametrami su hodnoty NAMES.
			CName												GetName1=Names["Timmy","Anderson",12];
			CName												GetName3=Names["Jenny","Thompson",13];

			Console.WriteLine(string.Format("Name1: [{0}] !",Name1));
			Console.WriteLine(string.Format("Name2: [{0}] !",Name2));
			Console.WriteLine(string.Format("Name3: [{0}] !",Name3));
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