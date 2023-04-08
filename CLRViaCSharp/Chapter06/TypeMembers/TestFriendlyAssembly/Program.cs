using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using InternalAssembly;
//-------------------------------------------------------------------------------------------------------
namespace DynamicTypes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test()
		{
			// !!! Aj ked CName je INTERNAL, tak kedze bola TestFriendlyAssembly oznacena ako FRIEND, tak typ CName je VIDITELNA z TestFriendlyAssembly.
			CName												Name=new CName("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name: [{0}] !",Name.ToString()));

			// FRIEND ASSEMBLY moze volat aj INTERNAL MEMBERS.
			Name.InternalMethod();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------