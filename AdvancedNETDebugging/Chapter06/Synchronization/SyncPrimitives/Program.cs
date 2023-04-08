using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace SyncPrimitives
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Events()
		{
			AutoResetEvent			Event1=new AutoResetEvent(false);
			ManualResetEvent		Event2=new ManualResetEvent(false);

			Console.WriteLine("Press any key to SET events !");
			Console.ReadLine();

			Event1.Set();
			Event2.Set();

			Console.WriteLine("Press any key to RESET events !");
			Console.ReadLine();

			Event1.Reset();
			Event2.Reset();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Mutexes()
		{
			Mutex					MyMutex=new Mutex(false);

			Console.WriteLine("Press any key to WAIT for MUTEX !");
			Console.ReadLine();

			MyMutex.WaitOne();

			Console.WriteLine("Press any key to RELEASE MUTEX !");
			Console.ReadLine();

			MyMutex.ReleaseMutex();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Semaphore()
		{
			Semaphore				MySemaphore=new Semaphore(1,1);

			Console.WriteLine("Press any key to WAIT for SEMAPHORE !");
			Console.ReadLine();

			MySemaphore.WaitOne();

			Console.WriteLine("Press any key to RELEASE SEMAPHORE !");
			Console.ReadLine();

			MySemaphore.Release();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void MonitorTest()
		{
			object				LockObject=new object();

			Console.WriteLine("Press any key to call GetHashCode() !");
			Console.ReadLine();

			LockObject.GetHashCode();

			Console.WriteLine("Press any key to ENTER MONITOR !");
			Console.ReadLine();

			Monitor.Enter(LockObject);

			Console.WriteLine("Press any key to EXIT MONITOR !");
			Console.ReadLine();

			Monitor.Exit(LockObject);

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void ReaderWriterLockTest()
		{
			ReaderWriterLock		RWL=new ReaderWriterLock();

			Console.WriteLine("Press any key to ACQUIRE READER lock !");
			Console.ReadLine();

			RWL.AcquireReaderLock(1000);

			Console.WriteLine("Press any key to RELEASE READER lock !");
			Console.ReadLine();

			RWL.ReleaseReaderLock();

			Console.WriteLine("Press any key to ACQUIRE WRITER lock !");
			Console.ReadLine();

			RWL.AcquireWriterLock(1000);

			Console.WriteLine("Press any key to RELEASE WRITER lock !");
			Console.ReadLine();

			RWL.ReleaseWriterLock();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void ReaderWriterLockSlimTest()
		{
			ReaderWriterLockSlim	RWLS=new ReaderWriterLockSlim();

			Console.WriteLine("Press any key to ENTER READER LOCK !");
			Console.ReadLine();

			RWLS.EnterReadLock();

			Console.WriteLine("Press any key to EXIT READER LOCK !");
			Console.ReadLine();

			RWLS.ExitReadLock();

			Console.WriteLine("Press any key to ENTER WRITER LOCK !");
			Console.ReadLine();

			RWLS.EnterWriteLock();

			Console.WriteLine("Press any key to EXIT WRITER LOCK !");
			Console.ReadLine();

			RWLS.ExitWriteLock();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Events();
			//Mutexes();
			//Semaphore();
			MonitorTest();
			//ReaderWriterLockTest();
			//ReaderWriterLockSlimTest();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------