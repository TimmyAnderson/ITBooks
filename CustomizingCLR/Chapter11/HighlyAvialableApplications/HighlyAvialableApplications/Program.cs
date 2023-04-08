using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Diagnostics;
//------------------------------------------------------------------------------------------------------
namespace HighlyAvialableApplications
{
//------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static object									MSyn=new object();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void AbortThreadInNonCriticalRegionThreadMethod()
		{
			try
			{
				Console.WriteLine("THREAD STARTED !");

				Thread.Sleep(int.MaxValue);

				Console.WriteLine("THREAD FINISHED !");
			}
			catch(ThreadAbortException)
			{
				Console.WriteLine("THREAD ABORTED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void AbortThreadInCriticalRegionThreadMethod()
		{
			try
			{
				// !!! Vytvorim CRITICAL REGION, kedze k THREAD ABORT dojde pocas DRZANIA LOCKU.
				Monitor.Enter(MSyn);

				Console.WriteLine("THREAD STARTED !");

				Thread.Sleep(int.MaxValue);

				Console.WriteLine("THREAD FINISHED !");

				Monitor.Exit(MSyn);
			}
			catch(ThreadAbortException)
			{
				Console.WriteLine("THREAD ABORTED !");
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void CallbackThrowExceptionInRemoteAppDomain()
		{
			try
			{
				Console.WriteLine(string.Format("Code is EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

				throw(new Exception("EXCEPTION in REMOTE APP DOMAIN !!!"));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));

				// !!!!! Ak sa EXCEPTION z APP DOMAIN VYHODI VON, tak PROCESS NESKONCI, pretoze APP DOMAIN su NEZAVISLE.
				throw;
			}
		}
//-------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		private static void ThrowExceptionInRemoteAppDomain()
		{
			try
			{
				AppDomain										Domain=AppDomain.CreateDomain("MyAppDomain");

				// !!!!! METHOD AppDomain.DoCallBack() spusta CALLBACK METHOD v REMOTE APP DOMAIN.
				// !!!!! Kedze REMOTE APP DOMAIN hodila UNHANDLED EXCEPTION, tak tato je RETRHOWN v DEFAULT APP DOMAIN.
				Domain.DoCallBack(CallbackThrowExceptionInRemoteAppDomain);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));
			}
		}
//------------------------------------------------------------------------------------------------------
		private static void FinalizerRunOnProcessKill()
		{
			CFinalizer											Finalizer=new CFinalizer();
			CCriticalFinalizer									CriticalFinalizer=new CCriticalFinalizer();

			Finalizer.DoSomething();
			CriticalFinalizer.DoSomething();

			// !!! FINALIZERS sa NEVOLAJU.
			Process.GetCurrentProcess().Kill();
		}
//------------------------------------------------------------------------------------------------------
		private static void FinalizerRunOnProcessExit1()
		{
			CFinalizer											Finalizer=new CFinalizer();
			CCriticalFinalizer									CriticalFinalizer=new CCriticalFinalizer();

			Finalizer.DoSomething();
			CriticalFinalizer.DoSomething();

			// !!! FINALIZERS sa VOLAJU.
			Environment.Exit(0);
		}
//------------------------------------------------------------------------------------------------------
		private static void FinalizerRunOnProcessExit2()
		{
			// !!!!! NON-CRITICAL FINALIZER, ktory sposobi INFINITE LOCK.
			CLockFinalizer										LockFinalizer1=new CLockFinalizer();
			CFinalizer											Finalizer=new CFinalizer();
			CCriticalFinalizer									CriticalFinalizer=new CCriticalFinalizer();
			CLockFinalizer										LockFinalizer2=new CLockFinalizer();

			LockFinalizer1.DoSomething();
			Finalizer.DoSomething();
			CriticalFinalizer.DoSomething();
			LockFinalizer2.DoSomething();

			// !!!!! Sposobi, ze FINALIZER v CLockFinalizer vojde do INFINITE LOCK a aj ked tento FINALIZER NIE je CRITICAL, tak program sa NEUKONCI.
			Environment.Exit(0);
		}
//------------------------------------------------------------------------------------------------------
		private static void FinalizerRunOnProcessExit3()
		{
			// !!!!! CRITICAL FINALIZER, ktory sposobi INFINITE LOCK.
			CLockCriticalFinalizer								LockFinalizer1=new CLockCriticalFinalizer();
			CFinalizer											Finalizer=new CFinalizer();
			CCriticalFinalizer									CriticalFinalizer=new CCriticalFinalizer();
			CLockCriticalFinalizer								LockFinalizer2=new CLockCriticalFinalizer();

			LockFinalizer1.DoSomething();
			Finalizer.DoSomething();
			CriticalFinalizer.DoSomething();
			LockFinalizer2.DoSomething();

			// !!!!! Sposobi, ze FINALIZER v CLockCriticalFinalizer vojde do INFINITE LOCK a kedze tento FINALIZER je CRITICAL, tak program sa NEUKONCI.
			Environment.Exit(0);
		}
//------------------------------------------------------------------------------------------------------
		private static void FinalizerRunOnProcessExit4()
		{
			// !!!!! NON-CRITICAL FINALIZER, ktory sposobi INFINITE LOCK.
			CLockFinalizer										LockFinalizer1=new CLockFinalizer();
			CFinalizer											Finalizer=new CFinalizer();
			CLockFinalizer										LockFinalizer2=new CLockFinalizer();

			LockFinalizer1.DoSomething();
			Finalizer.DoSomething();
			LockFinalizer2.DoSomething();

			// !!!!! Sposobi, ze FINALIZER v CLockFinalizer vojde do INFINITE LOCK a aj ked tento FINALIZER NIE je CRITICAL, tak program sa NEUKONCI.
			Environment.Exit(0);
		}
//------------------------------------------------------------------------------------------------------
		private static void ThreadAbortInNonCriticalRegion()
		{
			Thread												TestThread=new Thread(AbortThreadInNonCriticalRegionThreadMethod);

			TestThread.Start();

			Thread.Sleep(1000);

			TestThread.Abort();

			TestThread.Join();
		}
//------------------------------------------------------------------------------------------------------
		private static void ThreadAbortInCriticalRegion()
		{
			Thread												TestThread=new Thread(AbortThreadInCriticalRegionThreadMethod);

			TestThread.Start();

			Thread.Sleep(1000);

			TestThread.Abort();

			TestThread.Join();
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				//ThrowExceptionInRemoteAppDomain();
				//FinalizerRunOnProcessKill();
				//FinalizerRunOnProcessExit1();
				//FinalizerRunOnProcessExit2();
				//FinalizerRunOnProcessExit3();
				//FinalizerRunOnProcessExit4();
				//ThreadAbortInNonCriticalRegion();
				ThreadAbortInCriticalRegion();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));
			}

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------