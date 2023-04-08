using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime;
//-------------------------------------------------------------------------------------------------------
namespace GC
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void NotificationThreadMethod()
		{
			while(true)
			{
				// !!! Je to BLOCKING METHOD.
				GCNotificationStatus							StatusApproach=System.GC.WaitForFullGCApproach();

				Console.WriteLine(string.Format("StatusApproach [{0}] !",StatusApproach));

				// !!! Je to BLOCKING METHOD.
				GCNotificationStatus							StatusComplete=System.GC.WaitForFullGCComplete();

				Console.WriteLine(string.Format("StatusComplete [{0}] !",StatusComplete));

				if (StatusComplete==GCNotificationStatus.NotApplicable)
				{
					break;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void CreateDummyLargeObjects()
		{
			for(int Index=0;Index<10;Index++)
			{
				double[]										Array=new double[1000000];

				Console.WriteLine(string.Format("ARRAY [{0}] - LENGTH [{1}] !",Index+1,Array.Length));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			Console.WriteLine(string.Format("GCSettings.IsServerGC [{0}] !",GCSettings.IsServerGC));
			Console.WriteLine(string.Format("GCSettings.LargeObjectHeapCompactionMode [{0}] !",GCSettings.LargeObjectHeapCompactionMode));
			Console.WriteLine(string.Format("GCSettings.LatencyMode [{0}] !",GCSettings.LatencyMode));
			Console.WriteLine(string.Format("GC.GetTotalMemory() [{0}] !",System.GC.GetTotalMemory(false)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Console.WriteLine(string.Format("GCSettings.LatencyMode [{0}] !",GCSettings.LatencyMode));

			GCSettings.LatencyMode=GCLatencyMode.LowLatency;

			Console.WriteLine(string.Format("GCSettings.LatencyMode [{0}] !",GCSettings.LatencyMode));

			// Simuluje sa nejaka vypoctovo narocna cinnost.
			Thread.Sleep(1000);

			GCSettings.LatencyMode=GCLatencyMode.Interactive;

			Console.WriteLine(string.Format("GCSettings.LatencyMode [{0}] !",GCSettings.LatencyMode));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Console.WriteLine(string.Format("GCSettings.LargeObjectHeapCompactionMode [{0}] !",GCSettings.LargeObjectHeapCompactionMode));

			// !!! Zmeni sa hodnota tak aby nasledujuci FULL GARBAGE COLLECTION sposobil LOH HEAP COMPACTION.
			GCSettings.LargeObjectHeapCompactionMode=GCLargeObjectHeapCompactionMode.CompactOnce;

			Console.WriteLine(string.Format("GCSettings.LargeObjectHeapCompactionMode [{0}] !",GCSettings.LargeObjectHeapCompactionMode));

			// OBJECTS sa ulozia do LOH.
			CreateDummyLargeObjects();

			Console.WriteLine(string.Format("GCSettings.LargeObjectHeapCompactionMode [{0}] !",GCSettings.LargeObjectHeapCompactionMode));

			// !!! Vykona sa FULL GARBAGE COLLECTION.
			System.GC.Collect();

			// !!!!! Po vykonani COMPACTION LOH je hodnota PROPERTY GCSettings.LargeObjectHeapCompactionMode vratena na hodnotu [Default].
			Console.WriteLine(string.Format("!!!!! GCSettings.LargeObjectHeapCompactionMode [{0}] !",GCSettings.LargeObjectHeapCompactionMode));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Console.WriteLine(string.Format("GC.MaxGeneration [{0}] !",System.GC.MaxGeneration));

			object												SomeObject=new object();

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			System.GC.Collect();

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			System.GC.Collect();

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			System.GC.Collect();

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			// Vykona NEUPLNU GARBAGE COLLECTION.
			System.GC.Collect(0);

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			// Vykona NEUPLNU GARBAGE COLLECTION.
			System.GC.Collect(1);

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			// Vykona NEUPLNU GARBAGE COLLECTION.
			System.GC.Collect(1,GCCollectionMode.Forced);

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			// Vykona NEUPLNU GARBAGE COLLECTION, ale IBA ak to prinesie uvolnenie MEMORY.
			// !!! V skutocnosti GARBAGE COLLECTION NEVYKONA, pretoze niet co uvolnit.
			System.GC.Collect(1,GCCollectionMode.Optimized);

			Console.WriteLine(string.Format("GC.GetGeneration(SomeObject) [{0}] !",System.GC.GetGeneration(SomeObject)));

			Console.WriteLine();

			for(int Index=0;Index<=System.GC.MaxGeneration;Index++)
			{
				Console.WriteLine(string.Format("GC.GetGeneration({0}) [{1}] !",Index,System.GC.CollectionCount(Index)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Na to aby test fungoval MUSI byt VYPNUTY CONCURRENT SUBMODE v .CONFIG FILE.
		private static void Test5()
		{
			// Zaregistruje NOTIFICATION o vykonani GARBAGE COLLECTION.
			System.GC.RegisterForFullGCNotification(10,10);

			Thread												NotificationThread=new Thread(NotificationThreadMethod);

			NotificationThread.IsBackground=true;

			NotificationThread.Start();

			for(int Index=0;Index<10;Index++)
			{
				for(int X=0;X<100;X++)
				{
					double[]									SmallArray=new double[1000];
					double[]									BigArray=new double[1000000];

					SmallArray.ToString();
					BigArray.ToString();
				}

				System.GC.Collect();

				Console.WriteLine("GC COMPLETED !");
			}

			// Odregistruje NOTIFICATION o vykonani GARBAGE COLLECTION.
			System.GC.CancelFullGCNotification();

			Console.WriteLine();

			for(int Index=0;Index<=System.GC.MaxGeneration;Index++)
			{
				Console.WriteLine(string.Format("GC.GetGeneration({0}) [{1}] !",Index,System.GC.CollectionCount(Index)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Console.WriteLine(string.Format("Maximum generations: [{0}] !",System.GC.MaxGeneration));

			Object												O=new CGenObj();

			Console.WriteLine(string.Format("Gen [{0}] !",System.GC.GetGeneration(O)));

			System.GC.Collect();
			Console.WriteLine(string.Format("Gen [{0}] !",System.GC.GetGeneration(O)));

			System.GC.Collect();
			Console.WriteLine(string.Format("Gen [{0}] !",System.GC.GetGeneration(O)));

			System.GC.Collect();
			Console.WriteLine(string.Format("Gen [{0}] !",System.GC.GetGeneration(O)));

			O=null;

			Console.WriteLine("Collecting Gen 0 !");
			System.GC.Collect(0);
			System.GC.WaitForPendingFinalizers();

			Console.WriteLine("Collecting Gen 1 !");
			System.GC.Collect(1);
			System.GC.WaitForPendingFinalizers();

			Console.WriteLine("Collecting Gen 2 !");
			System.GC.Collect(2);
			System.GC.WaitForPendingFinalizers();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			// Maly objekt.
			byte[]												SmallObject=new byte[100];

			// Velky objekt, ktory sa umiestni do LOH.
			byte[]												LargeObject=new byte[85*1000];

			Console.WriteLine(string.Format("SmallObject - GENERATION: [{0}] !",System.GC.GetGeneration(SmallObject)));
			Console.WriteLine(string.Format("LargeObject - GENERATION: [{0}] !",System.GC.GetGeneration(LargeObject)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			long												MemoryUsed=System.GC.GetTotalMemory(false);

			Console.WriteLine(string.Format("MemoryUsed: [{0}] !",MemoryUsed));

			Console.WriteLine(string.Format("Number of GENERATION 0 GC: [{0}] !",System.GC.CollectionCount(0)));
			Console.WriteLine(string.Format("Number of GENERATION 1 GC: [{0}] !",System.GC.CollectionCount(1)));
			Console.WriteLine(string.Format("Number of GENERATION 2 GC: [{0}] !",System.GC.CollectionCount(2)));

			// Urobi GC pre GENERATION 0.
			System.GC.Collect(0);

			Console.WriteLine();
			Console.WriteLine(string.Format("Number of GENERATION 0 GC: [{0}] !",System.GC.CollectionCount(0)));
			Console.WriteLine(string.Format("Number of GENERATION 1 GC: [{0}] !",System.GC.CollectionCount(1)));
			Console.WriteLine(string.Format("Number of GENERATION 2 GC: [{0}] !",System.GC.CollectionCount(2)));

			// Urobi GC pre VSETKY GENERATIONS.
			System.GC.Collect();

			Console.WriteLine();
			Console.WriteLine(string.Format("Number of GENERATION 0 GC: [{0}] !",System.GC.CollectionCount(0)));
			Console.WriteLine(string.Format("Number of GENERATION 1 GC: [{0}] !",System.GC.CollectionCount(1)));
			Console.WriteLine(string.Format("Number of GENERATION 2 GC: [{0}] !",System.GC.CollectionCount(2)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			CNameWithFinalize									Name=new CNameWithFinalize("Timmy","Anderson",12);

			// Zaradim poziadavku na volanie Finalize() VIACKRAT.
			System.GC.ReRegisterForFinalize(Name);
			System.GC.ReRegisterForFinalize(Name);
			System.GC.ReRegisterForFinalize(Name);

			// Zrusim referenciu a Name NEBUDE ROOTED objekt.
			Name=null;

			// Vykonam GC.
			// !!! FINALIZER METHOD sa vykona VIACKRAT.
			System.GC.Collect();
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
			Test9();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------