#define SHOWCHANNEL
//-------------------------------------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;
using System.Diagnostics;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CPrintHelper
	{
//-------------------------------------------------------------------------------------------------------
		private static object									MSyncLock=new object();
		private static int										MCounter=0;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static CPrintHelper()
		{
			FileStream			FS=new FileStream("DelegatorChannelOutput.txt", FileMode.Create);
			TraceListener		Listener=new TextWriterTraceListener(FS);

			Trace.Listeners.Add(Listener);
			Trace.AutoFlush=true;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static void Print(string TypeName, string MemberName)
		{
			// Print the text as an atomic unit.
			lock(MSyncLock)
			{
				MCounter++;

				string			Output=String.Format("{3}. {0}.{1}, Thread: {2} !", TypeName, MemberName, Thread.CurrentThread.ManagedThreadId, MCounter);

				PrintInternal(Output);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void Print(string Message)
		{
			// Print the text as an atomic unit
			lock(MSyncLock)
			{
				MCounter++;

				string			Output=string.Format("{0}. {1}, Thread: {2} !", MCounter, Message, Thread.CurrentThread.ManagedThreadId, MCounter);

				PrintInternal(Output);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void PrintNewLine()
		{
			lock(MSyncLock)
			{
				PrintInternal(Environment.NewLine);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static void PrintNoThread(string Message)
		{
			lock(MSyncLock)
			{
				MCounter++;
				PrintInternal(Message);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void PrintInternal(string Output)
		{
			// The lock is taken by one of the public Print methods so no lock is necessary.
			Console.WriteLine(Output);
			Trace.WriteLine(Output);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------