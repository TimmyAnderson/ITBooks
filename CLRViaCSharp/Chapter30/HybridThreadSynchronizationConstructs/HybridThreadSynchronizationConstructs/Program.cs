using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace HybridThreadSynchronizationConstructs
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static CSimpleHybridLock						MSimpleHybridLock=new CSimpleHybridLock();
		private static CComplexHybridLock						MComplexHybridLock=new CComplexHybridLock();
		private static ManualResetEventSlim						MManualResetEventSlim=new ManualResetEventSlim(false);
		private static SemaphoreSlim							MSemaphoreSlim=new SemaphoreSlim(1,1);
		private static SemaphoreSlim							MSemaphoreSlimAsync=new SemaphoreSlim(1,1);
		private static object									MMonitorLock=new object();
		private static ReaderWriterLockSlim						MReaderWriterLockSlim=new ReaderWriterLockSlim(LockRecursionPolicy.NoRecursion);
		private static ReaderWriterLock							MReaderWriterLock=new ReaderWriterLock();
		private static CountdownEvent							MCountdownEvent=new CountdownEvent(3);
		private static Barrier									MBarrier=new Barrier(2,PhaseFinished);
		private static volatile bool							MConditionVariable=false;
		private static ConcurrentQueue<int>						MConcurrentQueue=new ConcurrentQueue<int>();
		private static int										MConcurrentQueueEmptyCounter=0;
		private static ConcurrentStack<int>						MConcurrentStack=new ConcurrentStack<int>();
		private static int										MConcurrentStackEmptyCounter=0;
		private static ConcurrentBag<int>						MConcurrentBag=new ConcurrentBag<int>();
		private static int										MConcurrentBagEmptyCounter=0;
		private static ConcurrentDictionary<int,int>			MConcurrentDictionary=new ConcurrentDictionary<int,int>();
		private static int										MConcurrentDictionaryNoItemFoundCounter=0;
		private static int										MConcurrentDictionaryNoItemAddedCounter=0;
		private static BlockingCollection<int>					MBlockingCollection=new BlockingCollection<int>(new ConcurrentQueue<int>());
		private static int										MSharedCounter;
		// Vsetky 3 COLLECTIONS maju CAPACITY==3.
		private static BlockingCollection<int>					MBlockingCollection1=new BlockingCollection<int>(new ConcurrentQueue<int>(),3);
		private static BlockingCollection<int>					MBlockingCollection2=new BlockingCollection<int>(new ConcurrentQueue<int>(),3);
		private static BlockingCollection<int>					MBlockingCollection3=new BlockingCollection<int>(new ConcurrentQueue<int>(),3);
		private static BlockingCollection<int>[]				MBlockingCollections=new BlockingCollection<int>[]{MBlockingCollection1,MBlockingCollection2,MBlockingCollection3};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void InsertToDictionaryTask()
		{
			MConcurrentDictionary.TryAdd(1,1);
			Console.WriteLine(string.Format("PAIR [1,1] ADDED to DICTIONARY !"));
			MConcurrentDictionary.TryAdd(2,2);
			Console.WriteLine(string.Format("PAIR [2,2] ADDED to DICTIONARY !"));

			Thread.Sleep(1000);

			MConcurrentDictionary.TryAdd(3,3);
			Console.WriteLine(string.Format("PAIR [3,3] ADDED to DICTIONARY !"));
			MConcurrentDictionary.TryAdd(4,4);
			Console.WriteLine(string.Format("PAIR [4,4] ADDED to DICTIONARY !"));

			Thread.Sleep(1000);

			MConcurrentDictionary.TryAdd(5,5);
			Console.WriteLine(string.Format("PAIR [5,5] ADDED to DICTIONARY !"));
			MConcurrentDictionary.TryAdd(6,6);
			Console.WriteLine(string.Format("PAIR [6,6] ADDED to DICTIONARY !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void EnumerateDictionaryTask()
		{
			Thread.Sleep(1200);

			// !!!!! Pocas enumerovania sa NEVYTVARA KOPIA, ale enumerovana COLLECTION je ZIVA. To znaci, ze ked sa do DICTIONARY prida novy ITEM, tak ENUMERATION ju ZACHYTI a zobrazi.
			foreach(KeyValuePair<int,int> Pair in MConcurrentDictionary)
			{
				Console.WriteLine(string.Format("PAIR [{0},{1}] READ from DICTIONARY !",Pair.Key,Pair.Value));

				Thread.Sleep(500);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void InsertToQueueTask()
		{
			MConcurrentQueue.Enqueue(1);
			Console.WriteLine(string.Format("VALUE [1] ADDED to QUEUE !"));
			MConcurrentQueue.Enqueue(2);
			Console.WriteLine(string.Format("VALUE [2] ADDED to QUEUE !"));

			Thread.Sleep(1000);

			MConcurrentQueue.Enqueue(3);
			Console.WriteLine(string.Format("VALUE [3] ADDED to QUEUE !"));
			MConcurrentQueue.Enqueue(4);
			Console.WriteLine(string.Format("VALUE [4] ADDED to QUEUE !"));

			Thread.Sleep(1000);

			MConcurrentQueue.Enqueue(5);
			Console.WriteLine(string.Format("VALUE [5] ADDED to QUEUE !"));
			MConcurrentQueue.Enqueue(6);
			Console.WriteLine(string.Format("VALUE [6] ADDED to QUEUE !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void EnumerateQueueTask()
		{
			Thread.Sleep(1200);

			// !!!!! Pocas enumerovania sa VYTVARA KOPIA QUEUE.
			foreach(int Value in MConcurrentQueue)
			{
				Console.WriteLine(string.Format("VALUE [{0}] READ from QUEUE !",Value));

				Thread.Sleep(500);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void ExclusiveTask(object Param)
		{
			int													Index=(int) Param;

			Console.WriteLine(string.Format("THREAD [{0}] - EXCLUSIVE TASK: [{1}] STARTED !",Thread.CurrentThread.ManagedThreadId,Index+1));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD [{0}] - EXCLUSIVE TASK: [{1}] STOPPED !",Thread.CurrentThread.ManagedThreadId,Index+1));
		}
//-------------------------------------------------------------------------------------------------------
		private static void ConcurrentTask(object Param)
		{
			int													Index=(int) Param;

			Console.WriteLine(string.Format("THREAD [{0}] - SHARED TASK: [{1}] STARTED !",Thread.CurrentThread.ManagedThreadId,Index+1));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD [{0}] - SHARED TASK: [{1}] STOPPED !",Thread.CurrentThread.ManagedThreadId,Index+1));
		}
//-------------------------------------------------------------------------------------------------------
		private async static Task TestAsynchronousSynchronization1(int Index)
		{
			// !!!!! BEZ OHLADU na to ci SEMAPHORE ma namiesto INITIAL a MAX COUNT hodnotu 2 a viac, VZDY je prepusteny za OPERATOR AWAIT IBA 1 THREAD.
			await MSemaphoreSlimAsync.WaitAsync();

			Console.WriteLine(string.Format("THREAD [{0}] - TASK: [{1}] is INSIDE LOCK !",Thread.CurrentThread.ManagedThreadId,Index+1));

			Thread.Sleep(1000);

			Console.WriteLine(string.Format("THREAD [{0}] - TASK: [{1}] is GOING to LEAVE LOCK !",Thread.CurrentThread.ManagedThreadId,Index+1));

			MSemaphoreSlimAsync.Release();
		}
//-------------------------------------------------------------------------------------------------------
		private static Task TestAsynchronousSynchronization2(int Index)
		{
			Action												TaskMethod=() =>
			{
				Task											AsyncTask=MSemaphoreSlimAsync.WaitAsync();

				// !!!!! Tu zas ked dam v SEMAPHORE namiesto INITIAL a MAX COUNT hodnotu 2 a viac, tak je NARAZ UKONCENYCH aj VIACERO TASKS.
				AsyncTask.Wait();

				Console.WriteLine(string.Format("THREAD [{0}] - TASK: [{1}] is INSIDE LOCK !",Thread.CurrentThread.ManagedThreadId,Index+1));

				Thread.Sleep(1000);

				Console.WriteLine(string.Format("THREAD [{0}] - TASK: [{1}] is GOING to LEAVE LOCK !",Thread.CurrentThread.ManagedThreadId,Index+1));

				MSemaphoreSlimAsync.Release();
			};

			Task												NewTask=new Task(TaskMethod);

			NewTask.Start();

			return(NewTask);
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestDoubleCheckLockingAlgorithm(object Param)
		{
			Barrier												SharedBarrier=(Barrier) Param;

			for(int Index=0;Index<1000;Index++)
			{
				if (((Index+1) % 100)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index+1));
				}

				SharedBarrier.SignalAndWait();

				CDoubleCheckLockingAlgorithm.ResetExpensiveObjectToCreate();

				SharedBarrier.SignalAndWait();

				CExpensiveObjectToCreate						ExpensiveObjectToCreate=CDoubleCheckLockingAlgorithm.GetExpensiveObjectToCreate();

				// !!!!! Detekuje potencialnu CHYBU DOUBLE CHECK LOCKING ALGORITHM.
				if (ExpensiveObjectToCreate==null)
				{
					Console.WriteLine(string.Format("!!!!! THREAD [{0}] - DETECTED NULL VALUE in CExpensiveObjectToCreate !",Thread.CurrentThread.ManagedThreadId));
				}
				else if (ExpensiveObjectToCreate.MVariable1==false || ExpensiveObjectToCreate.MVariable2==false)
				{
					Console.WriteLine(string.Format("!!!!! THREAD [{0}] - DETECTED INVALID VALUE in CExpensiveObjectToCreate !",Thread.CurrentThread.ManagedThreadId));
				}

				SharedBarrier.SignalAndWait();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestDoubleCheckLockingAlgorithmWithError(object Param)
		{
			Barrier												SharedBarrier=(Barrier) Param;

			for(int Index=0;Index<1000;Index++)
			{
				if (((Index+1) % 100)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index+1));
				}

				SharedBarrier.SignalAndWait();

				CDoubleCheckLockingAlgorithm.ResetExpensiveObjectToCreate();

				SharedBarrier.SignalAndWait();

				CExpensiveObjectToCreate						ExpensiveObjectToCreate=CDoubleCheckLockingAlgorithm.GetExpensiveObjectToCreateWithError();

				// !!!!! Detekuje potencialnu CHYBU DOUBLE CHECK LOCKING ALGORITHM.
				if (ExpensiveObjectToCreate==null)
				{
					Console.WriteLine(string.Format("!!!!! THREAD [{0}] - DETECTED NULL VALUE in CExpensiveObjectToCreate !",Thread.CurrentThread.ManagedThreadId));
				}
				else if (ExpensiveObjectToCreate.MVariable1==false || ExpensiveObjectToCreate.MVariable2==false)
				{
					Console.WriteLine(string.Format("!!!!! THREAD [{0}] - DETECTED INVALID VALUE in CExpensiveObjectToCreate !",Thread.CurrentThread.ManagedThreadId));
				}

				SharedBarrier.SignalAndWait();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseSimpleHybridLock()
		{
			for (int Index=0;Index<10;Index++)
			{
				MSimpleHybridLock.Enter();

				Console.WriteLine(string.Format("THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(1000);

				MSimpleHybridLock.Leave();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseComplexHybridLock()
		{
			for (int Index=0;Index<10;Index++)
			{
				MComplexHybridLock.Enter();

				Console.WriteLine(string.Format("THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(1000);

				MComplexHybridLock.Leave();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestSimpleHybridLock()
		{
			for (int Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				MSimpleHybridLock.Enter();

				MSharedCounter++;

				MSimpleHybridLock.Leave();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestComplexHybridLock()
		{
			for (int Index=1;Index<=1000000;Index++)
			{
				if ((Index % 1000)==0)
				{
					Console.WriteLine(string.Format("THREAD [{0}] - Counter: [{1}] !",Thread.CurrentThread.ManagedThreadId,Index));
				}

				MComplexHybridLock.Enter();

				MSharedCounter++;

				MComplexHybridLock.Leave();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseManualResetEventSlim(object Param)
		{
			CancellationToken									CT=(CancellationToken) Param;

			Console.WriteLine(string.Format("THREAD [{0}] is WAITING !",Thread.CurrentThread.ManagedThreadId));

			try
			{
				MManualResetEventSlim.Wait(CT);
				Console.WriteLine(string.Format("THREAD [{0}] - SYNCHRONIZATION OBJECT WAS SIGNALIZED !",Thread.CurrentThread.ManagedThreadId));
			}
			catch(OperationCanceledException)
			{
				Console.WriteLine(string.Format("THREAD [{0}] - SYNCHRONIZATION OBJECT WAS CANCELLED !",Thread.CurrentThread.ManagedThreadId));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseSemaphoreSlim()
		{
			for (int Index=0;Index<10;Index++)
			{
				MSemaphoreSlim.Wait();

				Console.WriteLine(string.Format("THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(100);

				MSemaphoreSlim.Release();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseMonitor()
		{
			for (int Index=0;Index<10;Index++)
			{
				Monitor.Enter(MMonitorLock);

				Console.WriteLine(string.Format("THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(500);

				Monitor.Exit(MMonitorLock);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseLockKeyword()
		{
			for (int Index=0;Index<10;Index++)
			{
				lock(MMonitorLock)
				{
					Console.WriteLine(string.Format("THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
					Thread.Sleep(500);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseReaderWriterLockSlim_Reader()
		{
			for (int Index=0;Index<10;Index++)
			{
				MReaderWriterLockSlim.EnterReadLock();

				Console.WriteLine(string.Format("READER THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(500);

				MReaderWriterLockSlim.ExitReadLock();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseReaderWriterLockSlim_UpgradableReader()
		{
			for (int Index=0;Index<10;Index++)
			{
				MReaderWriterLockSlim.EnterUpgradeableReadLock();

				Console.WriteLine(string.Format("UPGRADABLE READER THREAD [{0}] is in READER LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(500);

				MReaderWriterLockSlim.EnterWriteLock();

				Console.WriteLine(string.Format("UPGRADABLE READER THREAD [{0}] is in WRITER LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(500);

				MReaderWriterLockSlim.ExitWriteLock();

				MReaderWriterLockSlim.ExitUpgradeableReadLock();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseReaderWriterLockSlim_Writer()
		{
			for (int Index=0;Index<10;Index++)
			{
				MReaderWriterLockSlim.EnterWriteLock();

				Console.WriteLine(string.Format("WRITER THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(500);

				MReaderWriterLockSlim.ExitWriteLock();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseReaderWriterLock_Reader()
		{
			for (int Index=0;Index<10;Index++)
			{
				MReaderWriterLock.AcquireReaderLock(TimeSpan.FromDays(1));

				Console.WriteLine(string.Format("READER THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(500);

				MReaderWriterLock.ReleaseReaderLock();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseReaderWriterLock_Writer()
		{
			for (int Index=0;Index<10;Index++)
			{
				MReaderWriterLock.AcquireWriterLock(TimeSpan.FromDays(1));

				Console.WriteLine(string.Format("WRITER THREAD [{0}] is in LOCK !",Thread.CurrentThread.ManagedThreadId));
				Thread.Sleep(500);

				MReaderWriterLock.ReleaseWriterLock();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseCountdownEvent()
		{
			while(true)
			{
				if (MCountdownEvent.Wait(1000)==false)
				{
					Console.WriteLine(string.Format("TIMEOUT EXPIRED - CountdownEvent.CurrentCount: [{0}] !",MCountdownEvent.CurrentCount));
				}
				else
				{
					Console.WriteLine(string.Format("COUNT DOWN EVENT SIGNALIZED - CountdownEvent.CurrentCount: [{0}] !",MCountdownEvent.CurrentCount));
					break;
				}
			}

			Console.WriteLine("THREAD FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// CALLBACK METODA volana KED PHASE v BARRIER SKONCI.
		private static void PhaseFinished(Barrier B)
		{
			Console.WriteLine(string.Format("!!! THREAD [{0}] - PHASE [{1}] FINISHED !",Thread.CurrentThread.ManagedThreadId,B.CurrentPhaseNumber));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseBarrier_Thread1()
		{
			int													Timeout;

			Timeout=3000;
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAITING for [{2}] !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber,Timeout));
			Thread.Sleep(Timeout);

			MBarrier.SignalAndWait();
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAIT FINISHED !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber));

			Timeout=5000;
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAITING for [{2}] !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber,Timeout));
			Thread.Sleep(Timeout);
			
			MBarrier.SignalAndWait();
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAIT FINISHED !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber));

			Timeout=12000;
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAITING for [{2}] !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber,Timeout));
			Thread.Sleep(Timeout);

			MBarrier.SignalAndWait();
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAIT FINISHED !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber));

			Console.WriteLine(string.Format("THREAD [{0}] FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseBarrier_Thread2()
		{
			int													Timeout;

			Timeout=10000;
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAITING for [{2}] !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber,Timeout));
			Thread.Sleep(Timeout);

			MBarrier.SignalAndWait();
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAIT FINISHED !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber));

			Timeout=2000;
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAITING for [{2}] !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber,Timeout));
			Thread.Sleep(Timeout);
			
			MBarrier.SignalAndWait();
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAIT FINISHED !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber));

			Timeout=8000;
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAITING for [{2}] !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber,Timeout));
			Thread.Sleep(Timeout);

			MBarrier.SignalAndWait();
			Console.WriteLine(string.Format("THREAD [{0}] - PHASE [{1}], WAIT FINISHED !",Thread.CurrentThread.ManagedThreadId,MBarrier.CurrentPhaseNumber));

			Console.WriteLine(string.Format("THREAD [{0}] FINISHED !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static string CreateString1()
		{
			Console.WriteLine("!!! CreateString1() CALLED !");

			return("Timmy Anderson");
		}
//-------------------------------------------------------------------------------------------------------
		private static string CreateString2()
		{
			Console.WriteLine("!!! CreateString2() CALLED !");

			return("Jenny Thompson");
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConditionVariable_CoditionTester()
		{
			Console.WriteLine(string.Format("THREAD [{0}] - BEFORE Monitor.Enter() !",Thread.CurrentThread.ManagedThreadId));

			Monitor.Enter(MMonitorLock);

			while(MConditionVariable==false)
			{
				Console.WriteLine(string.Format("THREAD [{0}] - CONDITION WASN'T MET - WAITING !",Thread.CurrentThread.ManagedThreadId));

				Monitor.Wait(MMonitorLock);
			}

			Console.WriteLine(string.Format("!!! THREAD [{0}] - CONDITION WAS MET - EXECUTION CRITICAL SECTION !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			Monitor.Exit(MMonitorLock);

			Console.WriteLine(string.Format("THREAD [{0}] - AFTER Monitor.Exit() !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConditionVariable_CoditionSetter()
		{
			Console.WriteLine(string.Format("THREAD [{0}] - BEFORE Monitor.Enter() !",Thread.CurrentThread.ManagedThreadId));

			Monitor.Enter(MMonitorLock);

			Console.WriteLine(string.Format("THREAD [{0}] - CONDITION WAS SET and PulseAll() WAS CALLED !",Thread.CurrentThread.ManagedThreadId));

			Thread.Sleep(1000);

			MConditionVariable=true;
			Monitor.PulseAll(MMonitorLock);

			Thread.Sleep(1000);

			Monitor.Exit(MMonitorLock);

			Console.WriteLine(string.Format("THREAD [{0}] - AFTER Monitor.Exit() !",Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentQueue_Reader()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				int												Dummy;

				if (MConcurrentQueue.TryDequeue(out Dummy)==false)
				{
					Interlocked.Increment(ref MConcurrentQueueEmptyCounter);
				}

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS tried to REMOVE from QUEUE !",Index));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentQueue_Writer()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				MConcurrentQueue.Enqueue(1000);

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS ADDED to QUEUE !",Index));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentStack_Reader()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				int												Dummy;

				if (MConcurrentStack.TryPop(out Dummy)==false)
				{
					Interlocked.Increment(ref MConcurrentStackEmptyCounter);
				}

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS tried to REMOVE from STACK !",Index));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentStack_Writer()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				MConcurrentStack.Push(1000);

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS ADDED to STACK !",Index));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentBag_Reader()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				int												Dummy;

				if (MConcurrentBag.TryTake(out Dummy)==false)
				{
					Interlocked.Increment(ref MConcurrentBagEmptyCounter);
				}

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS tried to REMOVE from BAG !",Index));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentBag_Writer()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				MConcurrentBag.Add(1000);

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS ADDED to BAG !",Index));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentDictionary_Reader()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				int												Dummy;

				if (MConcurrentDictionary.TryRemove(Index,out Dummy)==false)
				{
					Interlocked.Increment(ref MConcurrentDictionaryNoItemFoundCounter);
				}

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS tried to REMOVE from DICTIONARY !",Index));
					Thread.Sleep(1);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseConcurrentDictionary_Writer()
		{
			for (int Index=1;Index<=(1000*1000);Index++)
			{
				if (MConcurrentDictionary.TryAdd(Index,Index)==false)
				{
					Interlocked.Increment(ref MConcurrentDictionaryNoItemAddedCounter);
				}

				if ((Index%1000)==0)
				{
					Console.WriteLine(string.Format("[{0}] ITEMS ADDED to DICTIONARY !",Index));
					Thread.Sleep(1);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseBlockingCollection_Reader()
		{
			Console.WriteLine(string.Format("!!!!! READER THREAD STARTED !"));
			
			// !!!!! Opakuje sa AZ KYM NIE JE VOLANA METODA CompleteAdding().
			foreach (int Value in MBlockingCollection.GetConsumingEnumerable())
			{
				Console.WriteLine(string.Format("Value [{0}] READ FROM QUEUE !",Value));
			}

			Console.WriteLine(string.Format("!!!!! READER THREAD FINISHED !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseBlockingCollection_Writer()
		{
			Console.WriteLine(string.Format("!!!!! WRITER THREAD STARTED !"));

			for (int Index=0;Index<10;Index++)
			{
				int												Value=Index+1;

				Console.WriteLine(string.Format("Value [{0}] is GOING to WRITE TO QUEUE !",Value));
				MBlockingCollection.TryAdd(Value);

				Console.WriteLine(string.Format("Value [{0}] is GOING to WRITE TO QUEUE !",Value*2));
				MBlockingCollection.TryAdd(Value*2);

				Thread.Sleep(500);
			}

			Console.WriteLine(string.Format("!!!!! WRITER THREAD CALLED METHOD CompleteAdding() !"));

			MBlockingCollection.CompleteAdding();

			Console.WriteLine(string.Format("!!!!! WRITER THREAD FINISHED !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseMultiBlockingCollection_Reader()
		{
			Console.WriteLine(string.Format("!!!!! READER THREAD STARTED !"));

			Thread.Sleep(10*1000);

			for (int Index=0;Index<30;Index++)
			{
				int												Value;
				// !!! BLOCKING operacia, ktora ZABLOKUJE THREAD.
				int												CollectionIndex=BlockingCollection<int>.TakeFromAny(MBlockingCollections,out Value);

				Console.WriteLine(string.Format("Value [{0}] was READ from QUEUE [{1}] !",Value,CollectionIndex));
			}

			Console.WriteLine(string.Format("!!!!! READER THREAD FINISHED !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseMultiBlockingCollection_Writer()
		{
			Console.WriteLine(string.Format("!!!!! WRITER THREAD STARTED !"));

			for (int Index=0;Index<30;Index++)
			{
				int												CollectionIndex=BlockingCollection<int>.TryAddToAny(MBlockingCollections,Index);

				if (CollectionIndex!=-1)
				{
					Console.WriteLine(string.Format("Value [{0}] was WRITTEN to QUEUE [{1}] !",Index,CollectionIndex));
				}
				else
				{
					Console.WriteLine(string.Format("Value [{0}] FAILED to be WRITTEN to ANY QUEUE !",Index));
					Index--;
				}

				Thread.Sleep(500);
			}

			Console.WriteLine(string.Format("!!!!! WRITER THREAD FINISHED !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseSimpleBlockingCollection_Reader()
		{
			Console.WriteLine(string.Format("!!!!! READER THREAD STARTED !"));

			for (int Index=0;Index<10;Index++)
			{
				int												Value;
				
				if (MBlockingCollection.TryTake(out Value,500)==true)
				{
					Console.WriteLine(string.Format("Value [{0}] was READ from QUEUE !",Value));
				}
				else
				{
					Console.WriteLine(string.Format("VALUE FAILED to READ from QUEUE !"));
					Index--;
				}
			}

			Console.WriteLine(string.Format("!!!!! READER THREAD FINISHED !"));
		}
//-------------------------------------------------------------------------------------------------------
		private static void UseSimpleBlockingCollection_Writer()
		{
			Console.WriteLine(string.Format("!!!!! WRITER THREAD STARTED !"));

			Thread.Sleep(3000);

			for (int Index=0;Index<10;Index++)
			{
				MBlockingCollection.Add(Index);

				Console.WriteLine(string.Format("Value [{0}] was WRITTEN to QUEUE !",Index));

				Thread.Sleep(1000);
			}

			Console.WriteLine(string.Format("!!!!! WRITER THREAD FINISHED !"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Task												T1=new Task(UseSimpleHybridLock);
			Task												T2=new Task(UseSimpleHybridLock);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Task												T1=new Task(UseComplexHybridLock);
			Task												T2=new Task(UseComplexHybridLock);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Thread[]											Threads=new Thread[10];

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index]=new Thread(TestSimpleHybridLock);
				Threads[Index].Start();
			}
	
			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index].Join();
			}

			Console.WriteLine(string.Format("SHARED COUNTER [{0}] !",MSharedCounter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Thread[]											Threads=new Thread[10];

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index]=new Thread(TestComplexHybridLock);
				Threads[Index].Start();
			}
	
			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index].Join();
			}

			Console.WriteLine(string.Format("SHARED COUNTER [{0}] !",MSharedCounter));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Task												T=new Task(UseManualResetEventSlim,CTS.Token,CTS.Token);

			T.Start();

			Console.WriteLine("Press any key to SET MANUAL RESET EVENT SLIM !");
			Console.ReadLine();

			MManualResetEventSlim.Set();

			T.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			CancellationTokenSource								CTS=new CancellationTokenSource();
			Task												T=new Task(UseManualResetEventSlim,CTS.Token,CTS.Token);

			T.Start();

			Console.WriteLine("Press any key to CANCEL MANUAL RESET EVENT SLIM !");
			Console.ReadLine();

			CTS.Cancel();

			T.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Task												T1=new Task(UseSemaphoreSlim);
			Task												T2=new Task(UseSemaphoreSlim);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			Task												T1=new Task(UseMonitor);
			Task												T2=new Task(UseMonitor);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			Task												T1=new Task(UseLockKeyword);
			Task												T2=new Task(UseLockKeyword);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			Task												T1=new Task(UseReaderWriterLockSlim_Reader);
			Task												T2=new Task(UseReaderWriterLockSlim_Reader);
			Task												T3=new Task(UseReaderWriterLockSlim_Writer);
			Task												T4=new Task(UseReaderWriterLockSlim_Writer);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			Task												T1=new Task(UseReaderWriterLockSlim_Reader);
			Task												T2=new Task(UseReaderWriterLockSlim_Reader);
			Task												T3=new Task(UseReaderWriterLockSlim_UpgradableReader);
			Task												T4=new Task(UseReaderWriterLockSlim_UpgradableReader);
			Task												T5=new Task(UseReaderWriterLockSlim_Writer);
			Task												T6=new Task(UseReaderWriterLockSlim_Writer);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();
			T5.Start();
			T6.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
			T5.Wait();
			T6.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			Task												T1=new Task(UseReaderWriterLock_Reader);
			Task												T2=new Task(UseReaderWriterLock_Reader);
			Task												T3=new Task(UseReaderWriterLock_Writer);
			Task												T4=new Task(UseReaderWriterLock_Writer);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			Task												T=new Task(UseCountdownEvent);

			T.Start();

			for (int Index=0;Index<MCountdownEvent.InitialCount;Index++)
			{
				Console.WriteLine("Press any key to SIGNAL COUNT DOWN EVENT !");
				Console.ReadLine();

				// !!! DEKREMENTUJE COUNTER.
				MCountdownEvent.Signal();
			}

			T.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			Task												T1=new Task(UseBarrier_Thread1);
			Task												T2=new Task(UseBarrier_Thread2);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		// METHOD testuje CDoubleCheckLockingAlgorithm pricom pouziva BARRIER.
		private static void Test15()
		{
			Console.WriteLine("TEST STARTED !");

			Thread[]											Threads=new Thread[10];
			Barrier												SharedBarrier=new Barrier(Threads.Length);

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index]=new Thread(TestDoubleCheckLockingAlgorithm);
			}

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index].Start(SharedBarrier);
			}

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index].Join();
			}

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! METHOD testuje POTENCIALNU CHYBU v CDoubleCheckLockingAlgorithm pricom pouziva BARRIER.
		// !!!!! Pocas mojich testov CHYBA DETEKOVANA NEBOLA.
		private static void Test16()
		{
			Console.WriteLine("TEST STARTED !");

			Thread[]											Threads=new Thread[10];
			Barrier												SharedBarrier=new Barrier(Threads.Length);

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index]=new Thread(TestDoubleCheckLockingAlgorithmWithError);
			}

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index].Start(SharedBarrier);
			}

			for(int Index=0;Index<Threads.Length;Index++)
			{
				Threads[Index].Join();
			}

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			// !!! Druhy parameter znamena, ze sa ma vytvorit instancia THREAD SAFE SPOSOBOM.
			Lazy<string>										Name=new Lazy<string>(CreateString1,LazyThreadSafetyMode.ExecutionAndPublication);

			Console.WriteLine(string.Format("Name.IsValueCreated: [{0}] !",Name.IsValueCreated));

			// Zavola sa FACTORY METODA.
			Console.WriteLine(string.Format("Name.Value: [{0}] !",Name.Value));

			Console.WriteLine(string.Format("Name.IsValueCreated: [{0}] !",Name.IsValueCreated));

			// Nezavola sa FACTORY METODA.
			Console.WriteLine(string.Format("Name.Value: [{0}] !",Name.Value));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			object												Lock=new object();
			string												Name=null;
			bool												Initialized=false;

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));

			// !!! Zavola sa FACTORY METHOD.
			LazyInitializer.EnsureInitialized<string>(ref Name,ref Initialized,ref Lock,CreateString1);

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));

			Console.WriteLine(string.Format("Name: [{0}] !",Name));

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));

			// !!! Kedze premenna je uz inicializovana, tak sa toto volanie BUDE IGNOROVAT a NOVA FACTORY METODA CreateString2() sa NEZAVOLA.
			// !!! Toto vsak plati IBA AK Initialized je TRUE.
			LazyInitializer.EnsureInitialized<string>(ref Name,ref Initialized,ref Lock,CreateString2);

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));

			// !!! Nezavola sa FACTORY METODA.
			Console.WriteLine(string.Format("Name: [{0}] !",Name));

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));

			// !!! Ak nastavim Initialized na FALSE, tak nasledujuce volanie EnsureInitialized<T>() APLIKUJE a zavola sa NOVA FACTORY METODA.
			Initialized=false;

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));

			// !!! Hoci premenna je uz inicializovana, tak kedze Initialized je FALSE, tak sa CreateString2() ZAVOLA.
			// !!! Zavola sa FACTORY METHOD.
			LazyInitializer.EnsureInitialized<string>(ref Name,ref Initialized,ref Lock,CreateString2);

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));

			Console.WriteLine(string.Format("Name: [{0}] !",Name));

			Console.WriteLine(string.Format("Initialized: [{0}] !",Initialized));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			Task												T1=new Task(UseConditionVariable_CoditionTester);
			Task												T2=new Task(UseConditionVariable_CoditionTester);

			T1.Start();
			T2.Start();

			Thread.Sleep(100);

			Task												T3=new Task(UseConditionVariable_CoditionSetter);

			T3.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			Console.WriteLine("TEST STARTED !");

			Task[]												Tasks=new Task[10];
			
			for (int Index=0;Index<Tasks.Length;Index++)
			{
				Tasks[Index]=TestAsynchronousSynchronization1(Index);
			}

			Task.WaitAll(Tasks);

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test21()
		{
			Console.WriteLine("TEST STARTED !");

			Task[]												Tasks=new Task[10];
			
			for (int Index=0;Index<Tasks.Length;Index++)
			{
				Tasks[Index]=TestAsynchronousSynchronization2(Index);
			}

			Task.WaitAll(Tasks);

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test22()
		{
			Console.WriteLine("TEST STARTED !");

			Task[]												Tasks=new Task[10];
			ConcurrentExclusiveSchedulerPair					SchedulerPair=new ConcurrentExclusiveSchedulerPair();
			TaskFactory											ConcurrentTaskFactory=new TaskFactory(SchedulerPair.ConcurrentScheduler);
			TaskFactory											ExclusiveTaskFactory=new TaskFactory(SchedulerPair.ExclusiveScheduler);

			for(int Index=0;Index<Tasks.Length;Index++)
			{
				if ((Index % 2)==0)
				{
					// V danom case moze bezat VIACERO CONCURRENT TASKS.
					Tasks[Index]=ConcurrentTaskFactory.StartNew(ConcurrentTask,Index);
				}
				else
				{
					// V danom case moze bezat IBA 1 EXCLUSIVE TASK.
					Tasks[Index]=ExclusiveTaskFactory.StartNew(ExclusiveTask,Index);
				}
			}

			Task.WaitAll(Tasks);

			Console.WriteLine("TEST FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test23()
		{
			Task												T1=new Task(UseConcurrentQueue_Writer);
			Task												T2=new Task(UseConcurrentQueue_Writer);
			Task												T3=new Task(UseConcurrentQueue_Reader);
			Task												T4=new Task(UseConcurrentQueue_Reader);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();

			Console.WriteLine(string.Format("!!!!! [{0}] times was QUEUE EMPTY !",MConcurrentQueueEmptyCounter));
			Console.WriteLine(string.Format("NUMBER of ITEMS in QUEUE [{0}] !",MConcurrentQueue.Count));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test24()
		{
			Task												T1=new Task(UseConcurrentStack_Writer);
			Task												T2=new Task(UseConcurrentStack_Writer);
			Task												T3=new Task(UseConcurrentStack_Reader);
			Task												T4=new Task(UseConcurrentStack_Reader);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();

			Console.WriteLine(string.Format("!!!!! [{0}] times was STACK EMPTY !",MConcurrentQueueEmptyCounter));
			Console.WriteLine(string.Format("NUMBER of ITEMS in STACK [{0}] !",MConcurrentQueue.Count));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test25()
		{
			Task												T1=new Task(UseConcurrentBag_Writer);
			Task												T2=new Task(UseConcurrentBag_Writer);
			Task												T3=new Task(UseConcurrentBag_Reader);
			Task												T4=new Task(UseConcurrentBag_Reader);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();

			Console.WriteLine(string.Format("!!!!! [{0}] times was BAG EMPTY !",MConcurrentBagEmptyCounter));
			Console.WriteLine(string.Format("NUMBER of ITEMS in BAG [{0}] !",MConcurrentBag.Count));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test26()
		{
			Task												T1=new Task(UseConcurrentDictionary_Writer);
			Task												T2=new Task(UseConcurrentDictionary_Writer);
			Task												T3=new Task(UseConcurrentDictionary_Reader);
			Task												T4=new Task(UseConcurrentDictionary_Reader);

			T1.Start();
			T2.Start();
			T3.Start();
			T4.Start();

			T1.Wait();
			T2.Wait();
			T3.Wait();
			T4.Wait();

			Console.WriteLine(string.Format("!!!!! [{0}] times ITEM was NOT ADDED !",MConcurrentDictionaryNoItemAddedCounter));
			Console.WriteLine(string.Format("!!!!! [{0}] times ITEM was NOT FOUND !",MConcurrentDictionaryNoItemFoundCounter));
			Console.WriteLine(string.Format("NUMBER of ITEMS in DICTIONARY [{0}] !",MConcurrentDictionary.Count));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test27()
		{
			Task												Insert=new Task(InsertToDictionaryTask);
			Task												Enumerate=new Task(EnumerateDictionaryTask);

			Insert.Start();
			Enumerate.Start();

			Insert.Wait();
			Enumerate.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test28()
		{
			Task												Insert=new Task(InsertToQueueTask);
			Task												Enumerate=new Task(EnumerateQueueTask);

			Insert.Start();
			Enumerate.Start();

			Insert.Wait();
			Enumerate.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test29()
		{
			Task												T1=new Task(UseBlockingCollection_Reader);
			Task												T2=new Task(UseBlockingCollection_Writer);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test30()
		{
			Task												T1=new Task(UseMultiBlockingCollection_Reader);
			Task												T2=new Task(UseMultiBlockingCollection_Writer);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test31()
		{
			Task												T1=new Task(UseSimpleBlockingCollection_Reader);
			Task												T2=new Task(UseSimpleBlockingCollection_Writer);

			T1.Start();
			T2.Start();

			T1.Wait();
			T2.Wait();
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
			//Test13();
			//Test14();
			//Test15();
			//Test16();
			//Test17();
			//Test18();
			//Test19();
			//Test20();
			//Test21();
			//Test22();
			//Test23();
			//Test24();
			Test25();
			//Test26();
			//Test27();
			//Test28();
			//Test29();
			//Test30();
			//Test31();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------