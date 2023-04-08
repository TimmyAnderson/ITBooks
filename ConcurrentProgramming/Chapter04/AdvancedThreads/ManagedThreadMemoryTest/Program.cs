using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;
//-----------------------------------------------------------------------------
namespace ManagedThreadMemoryTest
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static long					MStartVirtualMemSize=Process.GetCurrentProcess().VirtualMemorySize64;
		private static long					MStartWorkingMemSize=Process.GetCurrentProcess().WorkingSet64;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		private static void DummyThread()
		{
			Thread.Sleep(5000);
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		private static string FriendlyLong(long Number)
		{
			string			Text=Number.ToString();
			StringBuilder	SB=new StringBuilder();

			for (int i=0,j=Text.Length;i<Text.Length;i++,j--)
			{
				if ((j % 3)==0 && i>0)
					SB.Append(",");

				SB.Append(Text[i]);
			}

			return(SB.ToString());
		}
//-----------------------------------------------------------------------------
		private static void ShowMemory(string Prefix)
		{
			Process				P=Process.GetCurrentProcess();
			long				VirtualMem=P.VirtualMemorySize64;
			long				VirtualDif=VirtualMem-MStartVirtualMemSize;
			long				WorkingMem=P.WorkingSet64;
			long				WorkingDif=WorkingMem-MStartWorkingMemSize;

			Console.WriteLine(string.Format("{0} - VM: {1}, V-DIF: {2}, WM: {3}, W-DIF: {4} !",Prefix,FriendlyLong(VirtualMem),FriendlyLong(VirtualDif),FriendlyLong(WorkingMem),FriendlyLong(WorkingDif)));
		}
//-----------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.BufferHeight=1000;
			Console.WindowWidth=100;

			ShowMemory("BEGINING");

			const int				COUNT=15;
			Thread[]				Threads=new Thread[COUNT];

			for(int i=0;i<COUNT;i++)
			{
				Threads[i]=new Thread(DummyThread,1*1024*1024);
				Threads[i].Start();
				Thread.Sleep(10);
				ShowMemory(string.Format("{0}. THREAD CREATED",i+1));
			}

			for(int i=0;i<COUNT;i++)
				Threads[i].Join();

			Thread.Sleep(100);

			ShowMemory("\n\n\nALL THREADS FINISHED");

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------