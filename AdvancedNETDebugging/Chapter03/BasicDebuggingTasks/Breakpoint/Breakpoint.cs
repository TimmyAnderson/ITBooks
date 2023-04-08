using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Breakpoint
{
//-------------------------------------------------------------------------------------------------------
	class Breakpoint
	{
//-------------------------------------------------------------------------------------------------------
        public void AddAndPrint(int A, int B)
        {
            int			Res=A+B;

            Console.WriteLine("Adding {0}+{1}={2} !", A, B, Res);
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public static void AddAndPrintStatic(int A, int B)
        {
            int			Res=A+B;

            Console.WriteLine("Adding {0}+{1}={2} !", A, B, Res);
        }
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            Console.WriteLine("Press any key (1st instance function) !");
            Console.ReadKey();

            Breakpoint		BP=new Breakpoint();

            BP.AddAndPrint(10, 5);

            Console.WriteLine("Press any key (2nd instance function) !");
            Console.ReadKey();

            BP=new Breakpoint();
            BP.AddAndPrint(100, 50);

            Console.WriteLine("Press any key (static function) !");
            Console.ReadKey();

            AddAndPrintStatic(20, 15);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------