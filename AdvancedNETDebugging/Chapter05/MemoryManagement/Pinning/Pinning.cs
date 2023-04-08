using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace Pinning
{
//-------------------------------------------------------------------------------------------------------
	class Pinning
	{
//-------------------------------------------------------------------------------------------------------
        public void Run()
        {
            sbyte[]				B1=null;
            sbyte[]				B2=null;
            sbyte[]				B3=null; 

            Console.WriteLine("Press any key to alloc !");
            Console.ReadKey();

            B1=new SByte[100]; 
            B2=new SByte[200];
            B3=new SByte[300]; 

            GCHandle			H1=GCHandle.Alloc(B1, GCHandleType.Pinned);
            GCHandle			H2=GCHandle.Alloc(B2, GCHandleType.Pinned);
            GCHandle			H3=GCHandle.Alloc(B3, GCHandleType.Pinned);

            Console.WriteLine("Press any key to GC !");
            Console.ReadKey();

            GC.Collect();

            Console.WriteLine("Press any key to exit !");
            Console.ReadKey();

            H1.Free();
			H2.Free();
			H3.Free();
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
            Pinning				P=new Pinning();

            P.Run();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------