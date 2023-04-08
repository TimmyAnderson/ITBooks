using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Generations
{
//-------------------------------------------------------------------------------------------------------
	class Generations
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] Args)
		{
            CName				Name1=new CName("Timmy", "Anderson");
            CName				Name2=new CName("Jenny", "Thompson");

            Console.WriteLine("Allocated objects !"); 

            Console.WriteLine("Press any key to invoke GC for 1st time !");
            Console.ReadKey();

            Name1=null;

            GC.Collect();

            Console.WriteLine("Press any key to invoke GC for 2nd time !");
            Console.ReadKey();

            GC.Collect();
            
            Console.WriteLine("Press any key to exit !");
            Console.ReadKey();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------