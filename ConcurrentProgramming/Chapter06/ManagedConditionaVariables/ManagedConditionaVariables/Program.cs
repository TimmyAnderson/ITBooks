using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace ManagedConditionaVariables
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static object					MSyn=new object();
		private static int						MTimeout=Timeout.Infinite;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void WorkerThread1()
		{
			Thread.Sleep(500);

			Console.WriteLine(string.Format("{0} - Thread 111 is GOING TO ENTER LOCK !",DateTime.Now));

			// Vstupim do LOCK.
			lock(MSyn)
			{
				Console.WriteLine(string.Format("{0} - Thread 111 HAS ENTERED INTO LOCK !",DateTime.Now));

				Thread.Sleep(5000);

				Console.WriteLine(string.Format("{0} - Thread 111 is GOING TO PULSE CONDITIONAL VARIABLE !",DateTime.Now));

				// SIGNALIZUJEM CV.
				Monitor.Pulse(MSyn);

				Thread.Sleep(3000);

				Console.WriteLine(string.Format("{0} - Thread 111 is GOING TO LEAVE LOCK !",DateTime.Now));

				// AZ TERAZ KED VYSTUPUJEM z LOCK MOZE 2. THREAD ZNOVA SI CHMATNUT LOCK a pokracovat dalej.
			}
		}
//------------------------------------------------------------------------------
		private static void WorkerThread2()
		{
			Thread.Sleep(100);

			Console.WriteLine(string.Format("{0} - Thread 222 is GOING TO ENTER LOCK !",DateTime.Now));

			// Vojdem do LOCK.
			lock(MSyn)
			{
				Console.WriteLine(string.Format("{0} - Thread 222 HAS ENTERED INTO LOCK !",DateTime.Now));

				Thread.Sleep(1000);

				Console.WriteLine(string.Format("{0} - Thread 222 is GOING TO WAIT FOR CONDITIONAL VARIABLE !",DateTime.Now));

				// !!!!! WAIT mozem spravit IBA AK MAM LOCK na danom objekte.
				// Vyskocim z LOCK (MSyn) a zaroven NASTAVIM CV, aby na nu tento Thread cakal, kym ju iny thread NESIGNALIZUJE.
				// Wait() skonci AZ ked je SIGNALIZOVANA CV a ZAROVEN INY THREAD NEDRZI LOCK (MSyn).
				bool					Ret=Monitor.Wait(MSyn,MTimeout);

				Console.WriteLine(string.Format("{0} - Thread 222 HAS LEFT CONDITIONAL VARIABLE, RETURN: {1} !",DateTime.Now,Ret));

				Console.WriteLine(string.Format("{0} - Thread 222 is GOING TO LEAVE LOCK !",DateTime.Now));
			}
		}
//------------------------------------------------------------------------------
		private static void NoTimeoutTest()
		{
			// Velmi dlhy timeout, ktory nema sancu pretiect.
			MTimeout=1000*1000;

			Thread					T1=new Thread(WorkerThread1);
			Thread					T2=new Thread(WorkerThread2);

			T1.Start();
			T2.Start();

			T1.Join();
			T2.Join();
		}
//------------------------------------------------------------------------------
		private static void WithTimeoutTest()
		{
			// Kratky timeout, ktory pretecie.
			MTimeout=100;

			Thread					T1=new Thread(WorkerThread1);
			Thread					T2=new Thread(WorkerThread2);

			T1.Start();
			T2.Start();

			T1.Join();
			T2.Join();
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//NoTimeoutTest();
			WithTimeoutTest();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------