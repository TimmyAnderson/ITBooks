using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace ManagedLockingDuringShutdown
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static object					MSLock=new object();
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			// Vytvorim 10 finalizovatelnych objektov.
			Program[]			P=new Program[10];

			for (int i=0;i<P.Length;i++)
				P[i]=new Program();

			// Ziskam LOCK a prinutim proces aby spustil SHUTDOWN.
			lock (MSLock)
			{
				Environment.Exit(-1);
			}

			// Zabezpecim, aby objekt nezanikol v GC.
			GC.KeepAlive(P);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
    ~Program()
    {
        Console.WriteLine("acquiring MSLOCK...");

        // Pokusim sa ziskat LOCK pocas SHUTDOWN co sposobi HANG threadu.
        lock (MSLock)
        {
            Console.WriteLine("Got it!?  Nope.");
        }

		Console.WriteLine("This code is UNREACHABLE !!!");
    }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------