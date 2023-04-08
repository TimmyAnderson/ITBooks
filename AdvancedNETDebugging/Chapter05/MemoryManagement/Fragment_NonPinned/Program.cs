using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace Fragment_NonPinned
{
//-------------------------------------------------------------------------------------------------------
	class Fragment
	{
//-------------------------------------------------------------------------------------------------------
        public void Run(string[] Args)
        {
            if (Args.Length<2)
            {
                Console.WriteLine("Fragment.exe <alloc. size> <max mem in MB>");
                return;
            }

            int				Size=int.Parse(Args[0]);
            int				MaxMem=int.Parse(Args[1]);
            byte[][]		NonPinned1=null;
            byte[][]		NonPinned2=null;
            int				NumAllocs=(MaxMem*1000000)/Size;

            NonPinned1=new byte[NumAllocs/2][];
            NonPinned2=new byte[NumAllocs/2][];

            for (int i=0;i<NumAllocs/2;i++)
            {
                NonPinned1[i]=new byte[Size];
                NonPinned2[i]=new byte[Size];
            }

            Console.WriteLine("Press any key to GC & promo to GEN 1 !");
            Console.ReadKey();

            GC.Collect();

            Console.WriteLine("Press any key to GC & promo to GEN 2 !");
            Console.ReadKey();

            GC.Collect();

            Console.WriteLine("Press any key to GC (free non pinned) !");
            Console.ReadKey();

            for (int i=0;i<NumAllocs/2;i++)
                NonPinned1[i]=null;

            GC.Collect();

            Console.WriteLine("Press any key to exit !");
            Console.ReadKey();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            Fragment		F=new Fragment();

            F.Run(args);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------