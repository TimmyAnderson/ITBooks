using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace Date
{
//-------------------------------------------------------------------------------------------------------
	class MyDate
	{
//-------------------------------------------------------------------------------------------------------
        [DllImport("MyNative.dll", CharSet = CharSet.Unicode)]
        private static extern void GetDate(StringBuilder Date);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] Args)
		{
            if (Args.Length!=1)
            {
                Console.WriteLine("Please specify number of iterations !");
                return;
            }

            int					It=int.Parse(Args[0]);
            StringBuilder		Date=new StringBuilder(100);

            for (int i=0;i<It;i++)
                GetDate(Date);

            GC.Collect();

            Console.WriteLine("Press any key to exit !");
            Console.Read();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------