using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------
namespace NETThreadAbort
{
//------------------------------------------------------------------------
	public class MainClass
	{
//------------------------------------------------------------------------
		private static void Dump(string Text, bool ShowTS)
		{
			if (ShowTS==true)
				Console.WriteLine("{0}, [{1}], TS: {2} !",DateTime.Now.ToString("HH:mm:ss.fff"),Text,Thread.CurrentThread.ThreadState);
			else
				Console.WriteLine("{0}, [{1}] !",DateTime.Now.ToString("HH:mm:ss.fff"),Text);
		}
//------------------------------------------------------------------------
		private static void Thread1()
		{
			try
			{
				Dump("Thread1() 1",true);
				Thread.Sleep(5000);
				Dump("Thread1() 2",true);
			}
			catch(Exception E)
			{
				Dump(string.Format("Thread1() - EXCEPTION: {0}",E.Message),true);
				Dump("Thread1() 3",true);
				Thread.Sleep(5000);
				Dump("Thread1() 4",true);
			}
		}
//------------------------------------------------------------------------
		private static void Thread2()
		{
			try
			{
				Dump("Thread2() 1",true);

				try
				{
				}
				finally
				{
					// !!!!! Pocas behu FINALLY BLOKU sa ThreadAbortException NEVOLA.

					Dump("Thread2() 2",true);
					Thread.Sleep(5000);
					Dump("Thread2() 3",true);
				}
			}
			catch(Exception E)
			{
				// !!!!! ThreadAbortException sa NEZAVOLA, lebo kod po FINALLY BLOKU vyssie HNED KONCI.

				Dump(string.Format("Thread2() - EXCEPTION: {0}",E.Message),true);
				Dump("Thread2() 4",true);
			}
		}
//------------------------------------------------------------------------
		private static void Thread3()
		{
			try
			{
				Dump("Thread3() 1",true);

				try
				{
				}
				finally
				{
					// !!!!! Pocas behu FINALLY BLOKU sa ThreadAbortException NEVOLA.

					Dump("Thread3() 2",true);
					Thread.Sleep(5000);
					Dump("Thread3() 3",true);
				}

				// !!!!! Kedze sa pokusam po POZIADAVKE NA ABORT pustat nejaky kod TAK SA OKAMZTIE HODI ThreadAbortException.
				Dump("Thread3() 4",true);
				Thread.Sleep(5000);
				Dump("Thread3() 5",true);
			}
			catch(Exception E)
			{
				Dump(string.Format("Thread3() - EXCEPTION: {0}",E.Message),true);
				Dump("Thread3() 6",true);
			}
		}
//------------------------------------------------------------------------
		private static void Thread4()
		{
			try
			{
				Dump("Thread4() 1",true);

				try
				{
					throw(new Exception());
				}
				catch
				{
					// !!!!! Pocas behu CATCH BLOKU sa ThreadAbortException NEVOLA.

					Dump("Thread4() 2",true);
					Thread.Sleep(5000);
					Dump("Thread4() 3",true);
				}

				// !!!!! Kedze sa pokusam po POZIADAVKE NA ABORT pustat nejaky kod TAK SA OKAMZTIE HODI ThreadAbortException.
				Dump("Thread4() 4",true);
				Thread.Sleep(5000);
				Dump("Thread4() 5",true);
			}
			catch(Exception E)
			{
				Dump(string.Format("Thread4() - EXCEPTION: {0}",E.Message),true);
				Dump("Thread4() 6",true);
			}
		}
//------------------------------------------------------------------------
		private static void Thread5()
		{
			try
			{
				Dump("Thread5() 1",true);
				Thread.Sleep(5000);
				Dump("Thread5() 2",true);
			}
			catch(Exception E)
			{
				Dump(string.Format("Thread5() - EXCEPTION: {0}",E.Message),true);
				Dump("Thread5() 3",true);

				// !!!!! Zrusim Thread ABORT.
				Thread.ResetAbort();
				Dump("Thread5() 4",true);
			}

			Dump("Thread5() 5",true);
		}
//------------------------------------------------------------------------
		private static void Thread6()
		{
			try
			{
				Dump("Thread6() 1",true);

				// !!!!! Vstupim do KRITICKEHO BLOKU, kedy NIE JE MOZNE ABORTOVAT THREAD.

				// ????? BOHUZIAL TO NEFUNGUJE ASI BY TO SLO IBA ak by HOST bol SQL SERVER.
				Thread.BeginCriticalRegion();

				Dump("Thread6() 2",true);
				Thread.Sleep(5000);
				Dump("Thread6() 3",true);

				// !!!!! Opustim KRITICKY BLOK.
				Thread.EndCriticalRegion();

				// TERAZ SA HNED HODI ThreadAbortException.
				Dump("Thread6() 4",true);
			}
			catch(Exception E)
			{
				Dump(string.Format("Thread6() - EXCEPTION: {0}",E.Message),true);
				Dump("Thread6() 5",true);
			}
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		private static void Test1()
		{
			Thread			T=new Thread(Thread1);

			Dump("Test1() 1",false);
			T.Start();

			Dump("Test1() 2",false);
			Thread.Sleep(500);
			Dump("Test1() 3",false);

			T.Abort();
			Dump("Test1() 4",false);

			T.Join();
			Dump("Test1() 5",false);
		}
//------------------------------------------------------------------------
		private static void Test2()
		{
			Thread			T=new Thread(Thread2);

			Dump("Test2() 1",false);
			T.Start();

			Dump("Test2() 2",false);
			Thread.Sleep(500);
			Dump("Test2() 3",false);

			T.Abort();
			Dump("Test2() 4",false);

			T.Join();
			Dump("Test2() 5",false);
		}
//------------------------------------------------------------------------
		private static void Test3()
		{
			Thread			T=new Thread(Thread3);

			Dump("Test3() 1",false);
			T.Start();

			Dump("Test3() 2",false);
			Thread.Sleep(500);
			Dump("Test3() 3",false);

			T.Abort();
			Dump("Test3() 4",false);

			T.Join();
			Dump("Test3() 5",false);
		}
//------------------------------------------------------------------------
		private static void Test4()
		{
			Thread			T=new Thread(Thread4);

			Dump("Test4() 1",false);
			T.Start();

			Dump("Test4() 2",false);
			Thread.Sleep(500);
			Dump("Test4() 3",false);

			T.Abort();
			Dump("Test4() 4",false);

			T.Join();
			Dump("Test4() 5",false);
		}
//------------------------------------------------------------------------
		private static void Test5()
		{
			Thread			T=new Thread(Thread5);

			Dump("Test5() 1",false);
			T.Start();

			Dump("Test5() 2",false);
			Thread.Sleep(500);
			Dump("Test5() 3",false);

			T.Abort();
			Dump("Test5() 4",false);

			T.Join();
			Dump("Test5() 5",false);
		}
//------------------------------------------------------------------------
		private static void Test6()
		{
			Thread			T=new Thread(Thread6);

			Dump("Test6() 1",false);
			T.Start();

			Dump("Test6() 2",false);
			Thread.Sleep(500);
			Dump("Test6() 3",false);

			T.Abort();
			Dump("Test6() 4",false);

			T.Join();
			Dump("Test6() 5",false);
		}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			Test6();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------