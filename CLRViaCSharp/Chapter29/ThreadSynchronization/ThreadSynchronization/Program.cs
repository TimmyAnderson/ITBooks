using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace ThreadSynchronization
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static int										VALUE1_INT32=0;
		private static int										VALUE2_INT32=int.MaxValue;
		private static long										VALUE1_INT64=0;
		private static long										VALUE2_INT64=long.MaxValue;
//-------------------------------------------------------------------------------------------------------
		private static object									MLock=new object();
		private static int										MSharedMemory;
		private static CAlignedClassInt32						MAlignedValueInt32=new CAlignedClassInt32();
		private static CNotAlignedClassInt32					MNotAlignedValueInt32=new CNotAlignedClassInt32();
		private static CAlignedClassInt64						MAlignedValueInt64=new CAlignedClassInt64();
		private static CNotAlignedClassInt64					MNotAlignedValueInt64=new CNotAlignedClassInt64();
		private static ManualResetEvent							MEvent=new ManualResetEvent(false);
		// NON-VOLATILE VARIABLE.
		private static byte										MNonVolatileSharedVariable=0;
		// VOLATILE VARIABLE.
		private volatile static byte							MVolatileSharedVariable=0;
		private static string									MSharedString="Timmy Anderson";
		private static int										MInterlockedLock=0;
		private static SpinLock									MSpinLock=new SpinLock();
		private static int										MSharedCounter=0;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// METHOD demonstruje CUSTOM implementaciu INTERLOCKED Increment().
		private static int CustomInterlockedIncrement(ref int TargetValue)
		{
			int													CurrentValue;
			int													StartIterationValue;
			int													ReturnValue;

			CurrentValue=TargetValue;

			do
			{

				StartIterationValue=CurrentValue;

				// !!! Tu sa vykona operacia, ktora ma byt THREAD SAFE.
				ReturnValue=StartIterationValue+1;

				// !!! Zisti sa ci pocas vykonavania THREAD-SAFE operacie nedoslo k zmene 'TargetValue'.
				// !!!!! METHOD Interlocked.CompareExchange() VZDY vracia ako RETURN VALUE POVODNU hodnotu 'TargetValue'.
				CurrentValue=Interlocked.CompareExchange(ref TargetValue,ReturnValue,StartIterationValue);
			}
			// !!! Ak pocas behu cyklu doslo k ZMENE 'TargetValue' inym THREAD, tak sa operacia opakuje.
			while(StartIterationValue!=CurrentValue);

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		private static void MyWaitOrTimerCallback(object State, bool TimedOut)
		{
			Console.WriteLine(string.Format("MyWaitOrTimerCallback(): THREAD: [{0}] - State: [{1}], TimedOut: [{2}] !",Thread.CurrentThread.ManagedThreadId,State,TimedOut));
		}
//-------------------------------------------------------------------------------------------------------
		private static void MutexTest(object Param)
		{
			Mutex												M=(Mutex) Param;

			Console.WriteLine("Waiting for MUTEX to be RELEASED !");

			for (int Index=0;Index<5;Index++)
			{
				// Ziskam LOCK na MUTEX - rekurzivne 5 krat.
				bool											Ret=M.WaitOne();

				if (Ret==true)
				{
					Console.WriteLine("OBJECT was SIGNALIZED !");
				}
				else
				{
					Console.WriteLine("TIMEOUT EXPIRED !");
				}
			}

			// Ziskam MUTEX - rekurzivne 5 krat.
			for (int Index=0;Index<5;Index++)
			{
				M.ReleaseMutex();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void SemaphoreTest(object Param)
		{
			Semaphore											S=(Semaphore) Param;

			for (int Index=0;Index<5;Index++)
			{
				bool											Ret=S.WaitOne(1000);

				if (Ret==true)
				{
					Console.WriteLine("OBJECT was SIGNALIZED !");
				}
				else
				{
					Console.WriteLine("TIMEOUT EXPIRED !");
				}
			}

			S.Release(3);
		}
//-------------------------------------------------------------------------------------------------------
		private static void EventTest(object Param)
		{
			EventWaitHandle										EWH=(EventWaitHandle) Param;

			for (int Index=0;Index<5;Index++)
			{
				bool											Ret=EWH.WaitOne(1000);

				if (Ret==true)
				{
					Console.WriteLine("OBJECT was SIGNALIZED !");
				}
				else
				{
					Console.WriteLine("TIMEOUT EXPIRED !");
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void InterlockedLock(object Param)
		{
			string												Value=(string) Param;

			for (int Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				try
				{
					// !!! Zaciatok LOCK - IBA 1 THREAD v danom case prejde cez WHILE.
					// !!! METHOD VZDY vracia POVODNU HODNOTU 'MInterlockedLock', BEZ OHLADU na to ci sa METHOD hodnotu VARIABLE 'MInterlockedLock' zmenila, alebo nie.
					// !!!!! WHILE skonci iba ak PRED ZAVOLANIM Interlocked.CompareExchange() bola MInterlockedLock==0. Vtedy sa MInterlockedLock sa ATOMICKY nastavi na 1 a WHILE v OSTATNYCH THREADS bude vykonavat SPINNING.
					while(Interlocked.CompareExchange(ref MInterlockedLock,1,0)!=0)
					{
						// Do NOTHING - just SPIN ow WAIT.
						// !!!!! Ak pouzijem SPINING, tak program bezi efektivne IBA DO MAXIMLANEHO POCTU CPU. Ak je prekrokceny, tak sa program VYRAZNE SPOMALI, pretoze 8 THREADS robi SPINING a ZABIJA VSETKY CPU vykonavanim SPINING.
						//Thread.Sleep(0);

						// THREAD sa vzda svojho casoveho kvanta.
						Thread.Yield();
					}

					// !!!!! Tu zacina CRITICAL SECTION.
					MSharedCounter++;

					// !!! Pre NEPARNE THREADS je Value NON NULL a pre PARNE THREADS je Value NULL.
					MSharedString=Value;

					// Ak by sa NEAPLIKOVAL LOCK, tak by pri viacerych THREADS skoncim v NullReferenceException.
					if (MSharedString!=null)
					{
						Thread.Sleep(0);
						MSharedString.ToArray();
					}

					// !!!!! Tu konci CRITICAL SECTION.
					// !!! Ukoncenie LOCK - dalsi THREAD moze prejst cez WHILE.
					Interlocked.Exchange(ref MInterlockedLock,0);
				}
				catch(NullReferenceException E)
				{
					Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void InterlockedLockUsingSpingLock(object Param)
		{
			string												Value=(string) Param;

			for (int Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				try
				{
					bool										SpinLockAcquired=false;

					while(true)
					{
						MSpinLock.Enter(ref SpinLockAcquired);

						if (SpinLockAcquired==true)
						{
							break;
						}

						// Do NOTHING - just SPIN ow WAIT.
						// THREAD sa vzda svojho casoveho kvanta.
						Thread.Yield();
					}

					// !!!!! Tu zacina CRITICAL SECTION.
					MSharedCounter++;

					// !!! Pre NEPARNE THREADS je Value NON NULL a pre PARNE THREADS je Value NULL.
					MSharedString=Value;

					// Ak by sa NEAPLIKOVAL LOCK, tak by pri viacerych THREADS skoncim v NullReferenceException.
					if (MSharedString!=null)
					{
						Thread.Sleep(0);
						MSharedString.ToArray();
					}

					// !!!!! Tu konci CRITICAL SECTION.
					// !!! Ukoncenie LOCK - dalsi THREAD moze prejst cez WHILE.
					MSpinLock.Exit(true);
				}
				catch(NullReferenceException E)
				{
					Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void InterlockedLockUsingSpingLockAndSpinWait(object Param)
		{
			string												Value=(string) Param;

			for (int Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				try
				{
					bool										SpinLockAcquired=false;
					// VALUE TYPE SpinWait realizuje efektivny SPINNING.
					SpinWait									SpinWaitInstance=new SpinWait();

					while(true)
					{
						MSpinLock.Enter(ref SpinLockAcquired);

						if (SpinLockAcquired==true)
						{
							break;
						}

						// Do NOTHING - just SPIN ow WAIT.
						SpinWaitInstance.SpinOnce();
					}

					// !!!!! Tu zacina CRITICAL SECTION.
					MSharedCounter++;

					// !!! Pre NEPARNE THREADS je Value NON NULL a pre PARNE THREADS je Value NULL.
					MSharedString=Value;

					// Ak by sa NEAPLIKOVAL LOCK, tak by pri viacerych THREADS skoncim v NullReferenceException.
					if (MSharedString!=null)
					{
						Thread.Sleep(0);
						MSharedString.ToArray();
					}

					// !!!!! Tu konci CRITICAL SECTION.
					// !!! Ukoncenie LOCK - dalsi THREAD moze prejst cez WHILE.
					MSpinLock.Exit(true);
				}
				catch(NullReferenceException E)
				{
					Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void InterlockedLockUsingSpingLockAndSpinWaitMethod(object Param)
		{
			string												Value=(string) Param;

			for (int Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				try
				{
					bool										SpinLockAcquired=false;

					while(true)
					{
						MSpinLock.Enter(ref SpinLockAcquired);

						if (SpinLockAcquired==true)
						{
							break;
						}

						// Do NOTHING - just SPIN ow WAIT.
						// !!!!! V MULTITHREADED CPU prepne CPU do ineho CPU THREAD.
						Thread.SpinWait(10);
					}

					// !!!!! Tu zacina CRITICAL SECTION.
					MSharedCounter++;

					// !!! Pre NEPARNE THREADS je Value NON NULL a pre PARNE THREADS je Value NULL.
					MSharedString=Value;

					// Ak by sa NEAPLIKOVAL LOCK, tak by pri viacerych THREADS skoncim v NullReferenceException.
					if (MSharedString!=null)
					{
						Thread.Sleep(0);
						MSharedString.ToArray();
					}

					// !!!!! Tu konci CRITICAL SECTION.
					// !!! Ukoncenie LOCK - dalsi THREAD moze prejst cez WHILE.
					MSpinLock.Exit(true);
				}
				catch(NullReferenceException E)
				{
					Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestCustomInterlockedAdd()
		{
			for (int Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				// THREAD-SAFE sposobom inkrementuje 'MSharedCounter'.
				CustomInterlockedIncrement(ref MSharedCounter);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void InvalidOptimalization(object Param)
		{
			int													Counter=0;

			// !!!!! CODE NIE JE THREAD SAFE a pri optimalizacii by mohol generovat NEKOREKTNY MULTITHREAD CODE.
			// !!!!! CODE vo WHILE by sa TEORETICKY pri ZAPNUTEJ OPTIMALIZACII pre X86 mal SA TOCIT DO NEKONECNA, lebo OPTIMALIZATOR by mal detekovat, ze MSharedVariable sa vo WHILE NIKDE NENASTAVUJE na hodnotu odlisnu od 0 a teda OPTIMALIZOVANY KOD by SPRAVIL IBA JEDNO POROVNANIE HNED NA ZACIATKU a POTOM BY KOMPILATOR GENEROVAL OPTIMALIZOVANY CODE NEKONECNEHO CYKLU uz BEZ ZBYTOCNYCH POROVNANI MSharedVariable, ktora sa v CYKLE NIKDY NEMOZE ZMENIT.
			// ????? Vyzera to vsak, ze KOMPILATOR NEGENERUJE TAKTO OPTIMALIZOVANY CODE a GENEROVANY CODE z KOMPILATORA KOREKNTE TESTUJE v KAZDOM CYKLE PODMIENKU.
			while(MNonVolatileSharedVariable==0)
			{
				Counter++;
				Console.WriteLine("WAITING...");
			}

			Console.WriteLine(string.Format("Counter: [{0}] !",Counter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void ValidOptimalization(object Param)
		{
			// !!! Pouzije sa Thread.VolatileRead().
			// !!! Aj ked VARIABLE 'MNonVolatileSharedVariable' NIE JE VOLATILE, kedze sa pouzije VolatileRead(), tak CODE je THREAD-SAFE.
			while(Thread.VolatileRead(ref MNonVolatileSharedVariable)==0)
			{
				Console.WriteLine("WAITING...");
			}

			Console.WriteLine("WAIT FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void VolatileValidOptimalization(object Param)
		{
			// !!! Pouziva sa VOLATILE PREMENNA.
			while(MVolatileSharedVariable==0)
			{
				Console.WriteLine("WAITING...");
			}

			Console.WriteLine("WAIT FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void ChangeValueOnAlignedClassInt32(object Param)
		{
			int													Value=(int) Param;
			int													Temp1;
			int													Temp2;

			for (long Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				MAlignedValueInt32.MValue1=Value;
				Temp1=MAlignedValueInt32.MValue1;

				MAlignedValueInt32.MValue2=Value;
				Temp2=MAlignedValueInt32.MValue2;

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp1!=VALUE1_INT32 && Temp1!=VALUE2_INT32)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp1.ToString("x8"),VALUE1_INT32.ToString("x8"),VALUE2_INT32.ToString("x8")));
					MEvent.Set();
					return;
				}

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp2!=VALUE1_INT32 && Temp2!=VALUE2_INT32)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp2.ToString("x8"),VALUE1_INT32.ToString("x8"),VALUE2_INT32.ToString("x8")));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ChangeValueOnNotAlignedClassInt32(object Param)
		{
			int													Value=(int) Param;
			int													Temp1;
			int													Temp2;

			for (long Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				MNotAlignedValueInt32.MValue1=Value;
				Temp1=MNotAlignedValueInt32.MValue1;

				MNotAlignedValueInt32.MValue2=Value;
				Temp2=MNotAlignedValueInt32.MValue2;

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp1!=VALUE1_INT32 && Temp1!=VALUE2_INT32)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp1.ToString("x8"),VALUE1_INT32.ToString("x8"),VALUE2_INT32.ToString("x8")));
					MEvent.Set();
					return;
				}

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp2!=VALUE1_INT32 && Temp2!=VALUE2_INT32)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp2.ToString("x8"),VALUE1_INT32.ToString("x8"),VALUE2_INT32.ToString("x8")));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ChangeValueOnAlignedClassInt64(object Param)
		{
			long												Value=(long) Param;
			long												Temp1;
			long												Temp2;

			for (long Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				MAlignedValueInt64.MValue1=Value;
				Temp1=MAlignedValueInt64.MValue1;

				MAlignedValueInt64.MValue2=Value;
				Temp2=MAlignedValueInt64.MValue2;

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp1!=VALUE1_INT64 && Temp1!=VALUE2_INT64)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp1.ToString("x16"),VALUE1_INT64.ToString("x16"),VALUE2_INT64.ToString("x16")));
					MEvent.Set();
					return;
				}

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp2!=VALUE1_INT64 && Temp2!=VALUE2_INT64)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp2.ToString("x16"),VALUE1_INT64.ToString("x16"),VALUE2_INT64.ToString("x16")));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ChangeValueOnNotAlignedClassInt64(object Param)
		{
			long												Value=(long) Param;
			long												Temp1;
			long												Temp2;

			for (long Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				if (MEvent.WaitOne(0)==true)
				{
					return;
				}

				MNotAlignedValueInt64.MValue1=Value;
				Temp1=MNotAlignedValueInt64.MValue1;

				MNotAlignedValueInt64.MValue2=Value;
				Temp2=MNotAlignedValueInt64.MValue2;

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp1!=VALUE1_INT64 && Temp1!=VALUE2_INT64)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp1.ToString("x16"),VALUE1_INT64.ToString("x16"),VALUE2_INT64.ToString("x16")));
					MEvent.Set();
					return;
				}

				// !!!!! Viacero THREADS STRIEDAVO zapisuje 2 rozne VALUES a testuje sa ci SHARED VARIABLE VZDY obsahuje iba niektoru z tychto 2 VARIABLES.
				if (Temp2!=VALUE1_INT64 && Temp2!=VALUE2_INT64)
				{
					Console.WriteLine(string.Format("!!!!! DIFFERENT VALUE FOUND [{0}], expected [{1}] or [{2}] !",Temp2.ToString("x16"),VALUE1_INT64.ToString("x16"),VALUE2_INT64.ToString("x16")));
					MEvent.Set();
					return;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void NotSynchronizedTask(object Param)
		{
			int													Value=(int) Param;

			for(int Index=0;Index<5;Index++)
			{
				MSharedMemory=Value;

				Thread.Sleep(1000);

				Console.WriteLine(string.Format("THREAD set VALUE to [{0}] and now is [{1}] !",Value,MSharedMemory));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void SynchronizedTask(object Param)
		{
			int													Value=(int) Param;

			for(int Index=0;Index<5;Index++)
			{
				lock(MLock)
				{
					MSharedMemory=Value;

					Thread.Sleep(1000);

					Console.WriteLine(string.Format("THREAD set VALUE to [{0}] and now is [{1}] !",Value,MSharedMemory));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Nepouzijem LOCK.
		private static void Test1()
		{
			Task												T1=new Task(NotSynchronizedTask,1);
			Task												T2=new Task(NotSynchronizedTask,2);
			Task												T3=new Task(NotSynchronizedTask,3);

			T1.Start();
			T2.Start();
			T3.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// Pouzijem LOCK.
		private static void Test2()
		{
			Task												T1=new Task(SynchronizedTask,1);
			Task												T2=new Task(SynchronizedTask,2);
			Task												T3=new Task(SynchronizedTask,3);

			T1.Start();
			T2.Start();
			T3.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Simuluje paralelny zapis do KOREKTNE ALIGNED VARIABLE pre Int32 VARIABLES.
		// !!!!! Kedze operacie nad KOREKTNE ALIGNED Int32 VARIABLES su THREAD-SAFE, program NEGENEROVAL CHYBU.
		// !!! Test korektne presiel pre X86 aj X64.
		// !!!!! K chybe NEDOSLO ani v BUILD 'Any CPU'.
		private static void Test3()
		{
			Task												T1=new Task(ChangeValueOnAlignedClassInt32,VALUE1_INT32);
			Task												T2=new Task(ChangeValueOnAlignedClassInt32,VALUE2_INT32);
			Task												T3=new Task(ChangeValueOnAlignedClassInt32,VALUE1_INT32);
			Task												T4=new Task(ChangeValueOnAlignedClassInt32,VALUE2_INT32);
			Task												T5=new Task(ChangeValueOnAlignedClassInt32,VALUE1_INT32);
			Task												T6=new Task(ChangeValueOnAlignedClassInt32,VALUE2_INT32);
			Task												T7=new Task(ChangeValueOnAlignedClassInt32,VALUE1_INT32);
			Task												T8=new Task(ChangeValueOnAlignedClassInt32,VALUE2_INT32);
			Task												T9=new Task(ChangeValueOnAlignedClassInt32,VALUE1_INT32);
			Task												T10=new Task(ChangeValueOnAlignedClassInt32,VALUE2_INT32);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Simuluje paralelny zapis do KOREKTNE ALIGNED VARIABLE pre Int64 VARIABLES.
		// !!!!! CLR NEGARANTUJE ATOMICKY pristup k Int64 VARIABLES ani ked su KOREKTNE ALIGNED.
		// !!!!! V X86 DOSLO k chybe, pretoze CLR NEGARANTUJE ATOMICKY pristup k Int64 VARIABLES ani ked su KOREKTNE ALIGNED.
		// ????? V X64 NEDOSLO k chybe, pretoze X64 architektura GARANTUJE ATOMICKY pristup k VARIABLES o dlzke 64 BITS.
		// !!!!! K chybe NEDOSLO ani v BUILD 'Any CPU'.
		private static void Test4()
		{
			Task												T1=new Task(ChangeValueOnAlignedClassInt64,VALUE1_INT64);
			Task												T2=new Task(ChangeValueOnAlignedClassInt64,VALUE2_INT64);
			Task												T3=new Task(ChangeValueOnAlignedClassInt64,VALUE1_INT64);
			Task												T4=new Task(ChangeValueOnAlignedClassInt64,VALUE2_INT64);
			Task												T5=new Task(ChangeValueOnAlignedClassInt64,VALUE1_INT64);
			Task												T6=new Task(ChangeValueOnAlignedClassInt64,VALUE2_INT64);
			Task												T7=new Task(ChangeValueOnAlignedClassInt64,VALUE1_INT64);
			Task												T8=new Task(ChangeValueOnAlignedClassInt64,VALUE2_INT64);
			Task												T9=new Task(ChangeValueOnAlignedClassInt64,VALUE1_INT64);
			Task												T10=new Task(ChangeValueOnAlignedClassInt64,VALUE2_INT64);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Simuluje paralelny zapis do NEKOREKTNE ALIGNED VARIABLE pre Int32 VARIABLES.
		// !!!!! CLR NEGARANTUJE ATOMICKY pristup k NEKOREKTNE ALIGNED Int32 VARIABLES.
		// !!!!! V X86 aj X64 DOSLO k chybe, pretoze CLR NEGARANTUJE ATOMICKY pristup k NEKOREKTNE ALIGNED Int32 VARIABLES.
		// !!!!! K chybe NEDOSLO ani v BUILD 'Any CPU'.
		private static void Test5()
		{
			Task												T1=new Task(ChangeValueOnNotAlignedClassInt32,VALUE1_INT32);
			Task												T2=new Task(ChangeValueOnNotAlignedClassInt32,VALUE2_INT32);
			Task												T3=new Task(ChangeValueOnNotAlignedClassInt32,VALUE1_INT32);
			Task												T4=new Task(ChangeValueOnNotAlignedClassInt32,VALUE2_INT32);
			Task												T5=new Task(ChangeValueOnNotAlignedClassInt32,VALUE1_INT32);
			Task												T6=new Task(ChangeValueOnNotAlignedClassInt32,VALUE2_INT32);
			Task												T7=new Task(ChangeValueOnNotAlignedClassInt32,VALUE1_INT32);
			Task												T8=new Task(ChangeValueOnNotAlignedClassInt32,VALUE2_INT32);
			Task												T9=new Task(ChangeValueOnNotAlignedClassInt32,VALUE1_INT32);
			Task												T10=new Task(ChangeValueOnNotAlignedClassInt32,VALUE2_INT32);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Simuluje paralelny zapis do NEKOREKTNE ALIGNED VARIABLE pre Int64 VARIABLES.
		// !!!!! CLR NEGARANTUJE ATOMICKY pristup k Int64 VARIABLES, bez ohladu na to ci su KOREKTNE, ale NEKOREKTNE ALIGNED.
		// !!!!! V X86 DOSLO k chybe, pretoze CLR NEGARANTUJE ATOMICKY pristup k Int64 VARIABLES, bez ohladu na to ci su KOREKTNE, ale NEKOREKTNE ALIGNED.
		// ????? V X64 NEDOSLO k chybe, prevdepodobne preto, ze X64 architektura GARANTUJE ATOMICKY pristup k VARIABLES o dlzke 64 BITS aj ked NIE SU KOREKTNE ALIGNED.
		// !!!!! V BUILD 'Any CPU' DOSLO k CHYBE.
		private static void Test6()
		{
			Task												T1=new Task(ChangeValueOnNotAlignedClassInt64,VALUE1_INT64);
			Task												T2=new Task(ChangeValueOnNotAlignedClassInt64,VALUE2_INT64);
			Task												T3=new Task(ChangeValueOnNotAlignedClassInt64,VALUE1_INT64);
			Task												T4=new Task(ChangeValueOnNotAlignedClassInt64,VALUE2_INT64);
			Task												T5=new Task(ChangeValueOnNotAlignedClassInt64,VALUE1_INT64);
			Task												T6=new Task(ChangeValueOnNotAlignedClassInt64,VALUE2_INT64);
			Task												T7=new Task(ChangeValueOnNotAlignedClassInt64,VALUE1_INT64);
			Task												T8=new Task(ChangeValueOnNotAlignedClassInt64,VALUE2_INT64);
			Task												T9=new Task(ChangeValueOnNotAlignedClassInt64,VALUE1_INT64);
			Task												T10=new Task(ChangeValueOnNotAlignedClassInt64,VALUE2_INT64);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Thread												T=new Thread(InvalidOptimalization);

			T.Start();

			Thread.Sleep(1000);

			MNonVolatileSharedVariable=1;

			T.Join();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			Thread												T=new Thread(ValidOptimalization);

			T.Start();

			Thread.Sleep(1000);

			// !!! Pouzije sa Thread.VolatileWrite().
			Thread.VolatileWrite(ref MNonVolatileSharedVariable,1);

			T.Join();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			Thread												T=new Thread(VolatileValidOptimalization);

			T.Start();

			Thread.Sleep(500);

			// !!! Pouziva sa VOLATILE VARIABLE.
			MVolatileSharedVariable=1;

			T.Join();
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda simuluje vytvorenie LOCK cez INTERLOCKED METHODS.
		private static void Test10()
		{
			Task												T1=new Task(InterlockedLock,"Timmy Anderson");
			Task												T2=new Task(InterlockedLock,null);
			Task												T3=new Task(InterlockedLock,"Timmy Anderson");
			Task												T4=new Task(InterlockedLock,null);
			Task												T5=new Task(InterlockedLock,"Timmy Anderson");
			Task												T6=new Task(InterlockedLock,null);
			Task												T7=new Task(InterlockedLock,"Timmy Anderson");
			Task												T8=new Task(InterlockedLock,null);
			Task												T9=new Task(InterlockedLock,"Timmy Anderson");
			Task												T10=new Task(InterlockedLock,null);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine(string.Format("TEST FINISHED with VALUE [{0}] !",MSharedCounter));
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda realizuje LOCK cez CLASS SPIN LOCK.
		private static void Test11()
		{
			Task												T1=new Task(InterlockedLockUsingSpingLock,"Timmy Anderson");
			Task												T2=new Task(InterlockedLockUsingSpingLock,null);
			Task												T3=new Task(InterlockedLockUsingSpingLock,"Timmy Anderson");
			Task												T4=new Task(InterlockedLockUsingSpingLock,null);
			Task												T5=new Task(InterlockedLockUsingSpingLock,"Timmy Anderson");
			Task												T6=new Task(InterlockedLockUsingSpingLock,null);
			Task												T7=new Task(InterlockedLockUsingSpingLock,"Timmy Anderson");
			Task												T8=new Task(InterlockedLockUsingSpingLock,null);
			Task												T9=new Task(InterlockedLockUsingSpingLock,"Timmy Anderson");
			Task												T10=new Task(InterlockedLockUsingSpingLock,null);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine(string.Format("TEST FINISHED with VALUE [{0}] !",MSharedCounter));
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda realizuje LOCK cez CLASSES SPIN LOCK a SPIN WAIT.
		private static void Test12()
		{
			Task												T1=new Task(InterlockedLockUsingSpingLockAndSpinWait,"Timmy Anderson");
			Task												T2=new Task(InterlockedLockUsingSpingLockAndSpinWait,null);
			Task												T3=new Task(InterlockedLockUsingSpingLockAndSpinWait,"Timmy Anderson");
			Task												T4=new Task(InterlockedLockUsingSpingLockAndSpinWait,null);
			Task												T5=new Task(InterlockedLockUsingSpingLockAndSpinWait,"Timmy Anderson");
			Task												T6=new Task(InterlockedLockUsingSpingLockAndSpinWait,null);
			Task												T7=new Task(InterlockedLockUsingSpingLockAndSpinWait,"Timmy Anderson");
			Task												T8=new Task(InterlockedLockUsingSpingLockAndSpinWait,null);
			Task												T9=new Task(InterlockedLockUsingSpingLockAndSpinWait,"Timmy Anderson");
			Task												T10=new Task(InterlockedLockUsingSpingLockAndSpinWait,null);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine(string.Format("TEST FINISHED with VALUE [{0}] !",MSharedCounter));
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda realizuje LOCK cez CLASS SPIN LOCK a METHOD Thread.SpinWait().
		private static void Test13()
		{
			Task												T1=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,"Timmy Anderson");
			Task												T2=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,null);
			Task												T3=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,"Timmy Anderson");
			Task												T4=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,null);
			Task												T5=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,"Timmy Anderson");
			Task												T6=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,null);
			Task												T7=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,"Timmy Anderson");
			Task												T8=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,null);
			Task												T9=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,"Timmy Anderson");
			Task												T10=new Task(InterlockedLockUsingSpingLockAndSpinWaitMethod,null);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine(string.Format("TEST FINISHED with VALUE [{0}] !",MSharedCounter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			Task												T1=new Task(TestCustomInterlockedAdd);
			Task												T2=new Task(TestCustomInterlockedAdd);
			Task												T3=new Task(TestCustomInterlockedAdd);
			Task												T4=new Task(TestCustomInterlockedAdd);
			Task												T5=new Task(TestCustomInterlockedAdd);
			Task												T6=new Task(TestCustomInterlockedAdd);
			Task												T7=new Task(TestCustomInterlockedAdd);
			Task												T8=new Task(TestCustomInterlockedAdd);
			Task												T9=new Task(TestCustomInterlockedAdd);
			Task												T10=new Task(TestCustomInterlockedAdd);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();
			T7.Start();
			T8.Start();
			T9.Start();
			T10.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
			T7.Wait();
			T8.Wait();
			T9.Wait();
			T10.Wait();

			Console.WriteLine(string.Format("TEST FINISHED with VALUE [{0}] !",MSharedCounter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			AutoResetEvent										Event=new AutoResetEvent(false);
			Task												T=new Task(EventTest,Event);

			T.Start();

			Event.Set();

			T.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			ManualResetEvent									Event=new ManualResetEvent(false);
			Task												T=new Task(EventTest,Event);

			T.Start();

			Event.Set();

			T.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			Semaphore											S=new Semaphore(3,3);
			Task												T=new Task(SemaphoreTest,S);

			T.Start();
			T.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			Mutex												M=new Mutex();
			Task												T=new Task(MutexTest,M);

			M.WaitOne();

			T.Start();

			Console.WriteLine("\nPress any key to RELEASE MUTEX !");
			Console.ReadLine();

			M.ReleaseMutex();
			T.Wait();

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			AutoResetEvent										AutoEvent=new AutoResetEvent(false);
			ManualResetEvent									ManualEvent=new ManualResetEvent(false);
			// Kedze posledny parameter je FALSE, tak sa CALLBACK bude volat OPAKOVANE.
			RegisteredWaitHandle								RWH=ThreadPool.RegisterWaitForSingleObject(AutoEvent,MyWaitOrTimerCallback,"Timmy Anderson",1000,false);

			Console.WriteLine("Press any key to SET EVENT !");
			Console.ReadLine();

			AutoEvent.Set();

			// ManualEvent bude SIGNALIZOVANY, ked vsetky QUEUED ITEMS vykonane.
			RWH.Unregister(ManualEvent);

			ManualEvent.WaitOne();

			Console.WriteLine("MANUAL RESET EVENT was SIGNALIZED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			//Test8();
			//Test9();
			//Test10();
			//Test11();
			//Test12();
			//Test12();
			//Test13();
			//Test14();
			//Test15();
			//Test16();
			//Test17();
			//Test18();
			Test19();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------