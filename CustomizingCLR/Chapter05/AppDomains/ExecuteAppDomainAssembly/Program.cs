using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ExecuteAppDomainAssembly
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static string									MStaticField;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void StandardTest()
		{
			Console.WriteLine(string.Format("START - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

			for(int Index=0;Index<5;Index++)
			{
				Console.WriteLine(string.Format("INTERATION [{0}] - EXECUTED in APP DOMAIN [{1}] !",Index,AppDomain.CurrentDomain.FriendlyName));
				Thread.Sleep(1000);
			}

			Console.WriteLine(string.Format("STOP - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
		private static void SlowThreadTest()
		{
			Console.WriteLine(string.Format("START - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

			for(int Index=0;Index<5;Index++)
			{
				Console.WriteLine(string.Format("INTERATION [{0}] - EXECUTED in APP DOMAIN [{1}] !",Index,AppDomain.CurrentDomain.FriendlyName));
				Thread.Sleep(1000);
				GC.Collect();

				if (AppDomain.CurrentDomain.FriendlyName=="Domain1")
				{
					Thread.Sleep(2000);
				}
			}

			Console.WriteLine(string.Format("STOP - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
		private static void SharedGCHeapTest()
		{
			Console.WriteLine(string.Format("START - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

			for(int Index=0;Index<10;Index++)
			{
				Console.WriteLine(string.Format("INTERATION [{0}] - EXECUTED in APP DOMAIN [{1}] !",Index,AppDomain.CurrentDomain.FriendlyName));
				Thread.Sleep(1000);

				if (AppDomain.CurrentDomain.FriendlyName=="Domain1")
				{
					CSlowGC										SlowGC=new CSlowGC();

					SlowGC.ToString();
				}

				GC.Collect();
				GC.Collect();
			}

			Console.WriteLine(string.Format("STOP - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
		private static void StaticFieldTest()
		{
			// !!! TEST demonstruje, ze KAZDA APP DOMAIN ma VLASTNU KOPIU STATIC MEMBERS.
			MStaticField=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("START - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

			for(int Index=0;Index<5;Index++)
			{
				Console.WriteLine(string.Format("INTERATION [{0}] - EXECUTED in APP DOMAIN [{1}] !",Index,AppDomain.CurrentDomain.FriendlyName));
				Console.WriteLine(string.Format("INTERATION [{0}] - EXECUTED in APP DOMAIN [{1}], MStaticField [{2}] !",Index,AppDomain.CurrentDomain.FriendlyName,MStaticField));
				Thread.Sleep(1000);
			}

			Console.WriteLine(string.Format("STOP - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Je treba spustat s METHOD UnloadAppDomainsPrematurely() v PROJECT AppDomainTests.
		private static void FinalizerTest()
		{
			try
			{
				Console.WriteLine(string.Format("START - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

				// !!! Zavola sa prenho FINALIZER, ked bude APP DOMAIN UNLOADED
				CClassWithFinalizer									DummyObject=new CClassWithFinalizer();

				for(int Index=0;Index<10;Index++)
				{
					Console.WriteLine(string.Format("INTERATION [{0}] - EXECUTED in APP DOMAIN [{1}] !",Index,AppDomain.CurrentDomain.FriendlyName));
					Thread.Sleep(1000);

					if (AppDomain.CurrentDomain.FriendlyName=="Domain1")
					{
						Thread.Sleep(2000);
					}
				}

				Console.WriteLine(string.Format("STOP - EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
			}
			catch(ThreadAbortException E)
			{
				// !!! Pri UNLOAD APP DOMAIN sa vyhodi tato EXCEPTION.
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E,AppDomain.CurrentDomain.FriendlyName));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//StandardTest();
			//SlowThreadTest();
			//SharedGCHeapTest();
			//StaticFieldTest();
			FinalizerTest();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------