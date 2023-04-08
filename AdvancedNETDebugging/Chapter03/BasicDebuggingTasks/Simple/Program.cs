using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Simple
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			StringBuilder			SB1=new StringBuilder("MSG 1 - Welcome to Advanced .NET Debugging !");
			StringBuilder			SB2=new StringBuilder("MSG 2 - Welcome to Advanced .NET Debugging !");

			// 1. output - line 15.
            Console.WriteLine(SB1.ToString());

			// 2. output - line 18.
            Console.WriteLine(SB2.ToString());

			// 3. output - line 21.
            Console.WriteLine("Press any key to exit");
            Console.ReadKey();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------