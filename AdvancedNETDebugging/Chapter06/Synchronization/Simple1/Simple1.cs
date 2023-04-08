using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Simple1
{
//-------------------------------------------------------------------------------------------------------
	class Simple1
	{
//-------------------------------------------------------------------------------------------------------
        public void Run()
        {
			// Volanie GetHashCode() ZAPLNA OBJECT HEADER a sposobuje GENEROVANIE SYNC BLOCK.
            Console.WriteLine(string.Format("Hash Code: [{0}] !",this.GetHashCode()));

            Console.WriteLine("Press any key to acquire lock !");
            Console.ReadLine();

            Monitor.Enter(this);

            Console.WriteLine("Press any key to release lock !");
            Console.ReadLine();

            Monitor.Exit(this);

            Console.WriteLine("Press any key to exit !");
            Console.ReadLine();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            Simple1			S=new Simple1();

            S.Run();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------