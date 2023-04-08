using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ReferenceTypes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CNameClass											Name1=new CNameClass("Timmy","Anderson",12);
			CNameClass											Name2=new CNameClass("Timmy","Anderson",12);
			CNameClass											Name3=new CNameClass("Timmy","Anderson",13);

			Console.WriteLine(string.Format("Name1.Equals(Name1): [{0}] !",Name1.Equals(Name1)));
			Console.WriteLine(string.Format("Name1.Equals(Name2): [{0}] !",Name1.Equals(Name2)));
			Console.WriteLine(string.Format("Name1.Equals(Name3): [{0}] !",Name1.Equals(Name3)));
			Console.WriteLine(string.Format("Name1.Equals(new object()): [{0}] !",Name1.Equals(new object())));

			Console.WriteLine(string.Format("Name1==Name2: [{0}] !",Name1==Name2));
			Console.WriteLine(string.Format("Name1==Name3: [{0}] !",Name1==Name3));

			Console.WriteLine(string.Format("Name1!=Name2: [{0}] !",Name1!=Name2));
			Console.WriteLine(string.Format("Name1!=Name3: [{0}] !",Name1!=Name3));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CNameClass											Name1=new CNameClass("Timmy","Anderson",12);
			CNameClass											Name2=new CNameClass("Timmy","Anderson",12);
			CNameClass											Name3=new CNameClass("Timmy","Anderson",13);

			Console.WriteLine(string.Format("HASH Name1: [{0}] !",Name1.GetHashCode()));
			Console.WriteLine(string.Format("HASH Name2: [{0}] !",Name2.GetHashCode()));
			Console.WriteLine(string.Format("HASH Name3: [{0}] !",Name3.GetHashCode()));
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