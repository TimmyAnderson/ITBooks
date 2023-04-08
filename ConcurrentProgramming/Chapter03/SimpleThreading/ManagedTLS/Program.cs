using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-----------------------------------------------------------------------------
namespace ManagedTLS
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static string				SLOT_NAME="MyTLSEntry";
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		private static void DynamicTLSThread(object Param)
		{
			Console.WriteLine("{0}: Running - TLS VALUE: {1} !",Thread.CurrentThread.ManagedThreadId,Param);

			// Ziskam LocalDataStoreSlot z mena.
			LocalDataStoreSlot		LDSS=Thread.GetNamedDataSlot(SLOT_NAME);

			// Ulozim hodnotu do TLS.
			Thread.SetData(LDSS,Param);

			// Nacitam hodnotu z TLS.
			Console.WriteLine("{0}: Running - BEFORE SLEEP: {1} !",Thread.CurrentThread.ManagedThreadId,Thread.GetData(LDSS));

			Thread.Sleep(5000);

			// Nacitam hodnotu z TLS.
			Console.WriteLine("{0}: Running - AFTER SLEEP: {1} !",Thread.CurrentThread.ManagedThreadId,Thread.GetData(LDSS));
		}
//-----------------------------------------------------------------------------
		private static void StaticTLSThread(object Param)
		{
			Console.WriteLine("{0}: Running - TLS VALUE: {1}, ActualNonTLSVariable {2}, ActualTLSVariable: {3} !",Thread.CurrentThread.ManagedThreadId,Param,CStaticTLS.MNonTLSVariable,CStaticTLS.MTLSVariable);

			// Ulozim hodnotu do TLS.
			CStaticTLS.MTLSVariable=(int) Param;

			// A tuto hodnotu ulozim MIMO TLS do STATICKEJ PREMENNEJ.
			CStaticTLS.MNonTLSVariable=(int) Param;

			// Nacitam hodnotu z TLS.
			Console.WriteLine("{0}: Running - BEFORE SLEEP - NonTLS: {1} - TLS: {2} !",Thread.CurrentThread.ManagedThreadId,CStaticTLS.MNonTLSVariable,CStaticTLS.MTLSVariable);

			Thread.Sleep(5000);

			// Nacitam hodnotu z TLS.
			Console.WriteLine("{0}: Running - AFTER SLEEP - NonTLS: {1} - TLS: {2} !",Thread.CurrentThread.ManagedThreadId,CStaticTLS.MNonTLSVariable,CStaticTLS.MTLSVariable);
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		private static void Test1()
		{
			// Alokujem TLS Entry.
			Thread.AllocateNamedDataSlot(SLOT_NAME);

			const int			COUNT=5;
			Thread[]			Threads=new Thread[COUNT];

			for (int i=0;i<COUNT;i++)
			{
				Threads[i]=new Thread(new ParameterizedThreadStart(DynamicTLSThread));
				Threads[i].Start(i+1);
			}

			for (int i=0;i<COUNT;i++)
				Threads[i].Join();

			// Dealokujem TLS Entry.
			Thread.FreeNamedDataSlot(SLOT_NAME);
		}
//-----------------------------------------------------------------------------
		private static void Test2()
		{
			// Alokujem TLS Entry.
			Thread.AllocateNamedDataSlot(SLOT_NAME);

			const int			COUNT=5;
			Thread[]			Threads=new Thread[COUNT];

			for (int i=0;i<COUNT;i++)
			{
				Threads[i]=new Thread(new ParameterizedThreadStart(StaticTLSThread));
				Threads[i].Start(i+1);
			}

			for (int i=0;i<COUNT;i++)
				Threads[i].Join();

			// Dealokujem TLS Entry.
			Thread.FreeNamedDataSlot(SLOT_NAME);
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------