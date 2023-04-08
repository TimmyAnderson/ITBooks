using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Simple2
{
//-------------------------------------------------------------------------------------------------------
	class Simple2
	{
//-------------------------------------------------------------------------------------------------------
        public void Run1()
        {
            Console.WriteLine("Press any key to acquire lock !");
            Console.ReadLine();

            Monitor.Enter(this);

            Console.WriteLine("Press any key to release lock !");
            Console.ReadLine();

            Monitor.Exit(this);

            Console.WriteLine("Press any key to call GetHashCode() !");
            Console.ReadLine();

			// !!! Volanie GetHashCode() ZAPLNA OBJECT HEADER, avsak pretoze v OBJECT HEADER uz NIE JE informacia o THIN LOCK (thread, ktory drzi THIN LOCK), a teda je PRAZDNY, teraz sa naplni hodnotou HASH CODE, BEZ toho, aby sa vytvoril SYNC BLOCK.
			this.GetHashCode();

            Console.WriteLine("Press any key to exit !");
            Console.ReadLine();
        }
//-------------------------------------------------------------------------------------------------------
        public void Run2()
        {
            Console.WriteLine("Press any key to acquire lock !");
            Console.ReadLine();

            Monitor.Enter(this);

            Console.WriteLine("Press any key to call GetHashCode() !");
            Console.ReadLine();

			// Volanie GetHashCode() ZAPLNA OBJECT HEADER a kedze OBJECT HEADER UZ OBSAHUJE informaciu o THIN LOCKU (thread, ktory drzi THIN LOCK), tak 4 BYTES pre OBJECT HEADER je NEPOSTACUJUCICH a MUSI sa VYTVORIT SYNC BLOCK.
			this.GetHashCode();

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
            Simple2			S=new Simple2();

            //S.Run1();
            S.Run2();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------