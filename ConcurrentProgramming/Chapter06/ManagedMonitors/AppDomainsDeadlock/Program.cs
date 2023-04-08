#define DOMAIN_NEUTRAL
//------------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
// !!!!! Program v skutocnosti NESKONCI NIKDY V DEADLOCK.
//------------------------------------------------------------------------------
namespace AppDomainsDeadlock
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private const string				MEventName="__SharedEvent";
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		// Conditionally turn on/off domain neutrality.
#if DOMAIN_NEUTRAL
		[LoaderOptimization(LoaderOptimization.MultiDomain)]
#endif
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void AppDomainWorker(object Obj)
		{
			AppDomain				Ad=(AppDomain) Obj;

			// Nasledujuci kod sa vykona v SEKUNDARNEJ APP DOMAIN.
			Ad.DoCallBack(delegate
			{
				EventWaitHandle		WH = EventWaitHandle.OpenExisting(MEventName);

				Console.WriteLine("#2: Acquiring lock !");

				// Vykonam LOCK na typeof(Program).
				// !!!!! Ak je NASTAVENY DOMAIN_NEUTRAL, potom je 'typeof(Program)' ulozeny v SHARED NEUTRAL APP DOMAIN a EXISTUJE IBA JEDNA INSTANCIA OBJEKTU. To vedie ku CROSS APP DOMAIN LOCKS.
				lock (typeof(Program))
				{
					Console.WriteLine("#2: Lock acquired, setting event !");

					// !!!!! Ak je NASTAVENY DOMAIN_NEUTRAL - SPOSOBI TO DEADLOCK.
					WH.Set();

					Console.WriteLine("#2: Exiting lock !");
				}
			});
		}
//------------------------------------------------------------------------------
		static void Main()
		{
			EventWaitHandle			WH=new EventWaitHandle(false, EventResetMode.ManualReset, MEventName);

			Console.WriteLine("#1: Acquiring lock !");

			// Vykonam LOCK na typeof(Program).
			lock (typeof(Program))
			{
				// Vytvorim novu APP DOMAIN.
				AppDomain			AD2=AppDomain.CreateDomain("2");

				ThreadPool.QueueUserWorkItem(AppDomainWorker, AD2);

				// Cakam na uvolnenie Eventu zo sekundarneho APP DOMAIN.
				Console.WriteLine("#1: Waiting for event !");
				WH.WaitOne();
				Console.WriteLine("#1: Exiting lock !");
			}

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------