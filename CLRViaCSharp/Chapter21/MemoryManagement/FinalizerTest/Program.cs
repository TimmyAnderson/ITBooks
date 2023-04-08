using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;
//-------------------------------------------------------------------------------------------------------
namespace FinalizerTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CClassWithFinalizer									Instance=new CClassWithFinalizer();

			Instance=null;

			Console.WriteLine("GARBAGE COLLECTON STARTED !");

			// !!! Dal som CONCURRENT SUBMODE GARBAGE COLLECTON, ktora bezi v SEPARATNOM THREADE.
			GC.Collect(2,GCCollectionMode.Forced,false);

			Console.WriteLine("GARBAGE COLLECTON is IN PROGRESS !");

			GC.WaitForPendingFinalizers();

			Console.WriteLine("ALL FINALIZERS EXECUTED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// CLASS ma FINALIZER, ktory sposobi LOOP.
			CSlowFinalizer										Instance=new CSlowFinalizer();

			Instance=null;

			GC.Collect();

			Console.WriteLine("WHEN FINISHING PROGRAM - it will get into INFINITE LOOP and after 2 SECONDS it will be TERMINATED. !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Sposobi UNHANDLED EXCEPTION.
		private static void Test3()
		{
			// CLASS ma FINALIZER, ktory sposobi UNHANDLED EXCEPTION.
			CUnhandledExceptionFinalizer						Instance=new CUnhandledExceptionFinalizer();

			Instance=null;

			Console.WriteLine("Press any KEY ! PROGRAM WILL BE TERMINATED because UNHANDLED EXCEPTION in FINALIZER METHOD has HAPPENED !");
			Console.ReadLine();

			GC.Collect();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			try
			{
				CFileAsCriticalFinalizerObject					File=new CFileAsCriticalFinalizerObject(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// Standardne ukoncenie UNMANAGED RESOURCE - na pozadi sa vola Dispose().
				File.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			try
			{
				CFileAsCriticalFinalizerObject					File=new CFileAsCriticalFinalizerObject(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// Standardne ukoncenie UNMANAGED RESOURCE cez Dispose().
				File.Dispose();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			try
			{
				CFileAsCriticalFinalizerObject					File=new CFileAsCriticalFinalizerObject(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// !!! Zrusim referenciu na objekt BEZ jeho UVOLNENIA.
				File=null;

				// !!! Zavolam GC, ktory spusti FINALIZER.
				GC.Collect();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			try
			{
				CFileAsCriticalFinalizerObject					File=new CFileAsCriticalFinalizerObject(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// !!! UNMANAGED objekt NEUVOLNIM a necham FINALIZER, ktory sa spusti pri UKOCENI PROCESU, aby zavolal Finalize(), ktora vypise informaciu do DEBUG OKNA.
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			try
			{
				// !!! UMYSELNE NEDEFINUJEM MENO SUBORU, aby KONSTUKTOR HODIL EXCEPTION.
				CFileAsCriticalFinalizerObject					File=new CFileAsCriticalFinalizerObject(null);
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// !!! UNMANAGED objekt NEUVOLNIM a necham FINALIZER, ktory sa spusti pri UKOCENI PROCESU, aby zavolal Finalize(), ktora vypise informaciu do DEBUG OKNA.
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			try
			{
				CFileAsSafeHandle								File=new CFileAsSafeHandle(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// Standardne ukoncenie UNMANAGED RESOURCE - na pozadi sa vola Dispose().
				File.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			try
			{
				CFileAsSafeHandle								File=new CFileAsSafeHandle(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// Standardne ukoncenie UNMANAGED RESOURCE cez Dispose().
				File.Dispose();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			try
			{
				CFileAsSafeHandle								File=new CFileAsSafeHandle(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// !!! Zrusim referenciu na objekt BEZ jeho UVOLNENIA.
				File=null;

				// !!! Zavolam GC, ktory spusti FINALIZER.
				GC.Collect();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			try
			{
				CFileAsSafeHandle								File=new CFileAsSafeHandle(@"..\..\TextFiles\Timmy.txt");
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();

				// !!! UNMANAGED objekt NEUVOLNIM a necham FINALIZER, ktory sa spusti pri UKOCENI PROCESU, aby zavolal Finalize(), ktora vypise informaciu do DEBUG OKNA.
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			try
			{
				// !!! UMYSELNE NEDEFINUJEM MENO SUBORU, aby KONSTUKTOR HODIL EXCEPTION.
				// !!! Kedze sa FILE NEOTVORIL, tak UNMANAGED HANDLE NEBOL alokovany.
				CFileAsSafeHandle								File=new CFileAsSafeHandle(null);
			
				File.OpenFile();

				string											FileContent=File.ReadAllContent();

				Console.WriteLine(string.Format("FILE: [{0}] !",FileContent));

				File.ReadAllContent();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			using (CDisposable Disposable1=new CDisposable("DISPOSABLE 1"))
			{
			}

			try
			{
				using (CDisposable Disposable2=new CDisposable("DISPOSABLE 2"))
				{
					throw(new Exception("Some STUPID EXCEPTION !"));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			// NESIMULUJE sa ALOKOVANIE ZIADNEJ UNMANAGED PAMATE.
			for (int Count=0;Count<1000;Count++)
			{
				// !!! Pouziva METHODS GC.AddMemoryPressure() a GC.RemoveMemoryPressure().
				new CBigNativeResource(0);
			}

			Console.WriteLine("Press any KEY to START GARBAGE COLLECTION !");
			Console.ReadLine();

			GC.Collect();
			GC.WaitForPendingFinalizers();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			// SIMULUJE sa ALOKOVANIE UNMANAGED PAMATE o velkosti 10 MB.
			for (int Count=0;Count<1000;Count++)
			{
				// !!! Pouziva METHODS GC.AddMemoryPressure() a GC.RemoveMemoryPressure().
				// !!!!! GARBAGE COLLECTION sa bude volat CASTEJSIE, pretoze kazdy CBigNativeResource() pouziva METHOD GC.AddMemoryPressure(), ktora indikuje CLR, ze sa pouziva velke mnozstvo MEMORY.
				new CBigNativeResource(10*1024*1024);
			}

			Console.WriteLine("Press any KEY to START GARBAGE COLLECTION !");
			Console.ReadLine();

			GC.Collect();
			GC.WaitForPendingFinalizers();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			// Simulujem vytvorenie objektov, ktorych POCET MOZNYCH VYTVARANYCH INSTANCII je LIMITOVANY.
	        for (int Count=0;Count<10;Count++)
			{
		        new CLimitedResource();

				Thread.Sleep(500);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			CSimpleResurrection									Name=new CSimpleResurrection("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));

			Name=null;

			GC.Collect();
			GC.WaitForPendingFinalizers();
			GC.Collect();
			GC.WaitForPendingFinalizers();

			Console.WriteLine("Press any key to CANCEL RESURRECTION !");
			Console.ReadLine();

			// Zrusim ROOT na CSimpleResurrection.
			CSimpleResurrection.ResetResurrectedObjectToNULL();

			GC.Collect();
			GC.WaitForPendingFinalizers();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			CNameWithResurrection								Name=new CNameWithResurrection("Timmy","Anderson",12);

			Console.WriteLine(string.Format("Name: [{0}] !",Name));

			// Vytvorim si WeakTrackResurrection HANDLE.
			GCHandle											HandleToName=GCHandle.Alloc(Name,GCHandleType.WeakTrackResurrection);

			// Zrusim REFERENCIU na CNameWithResurrection objekt.
			Name=null;

			// Vykonam opakovane GC az kym NESKONCI RESURRECTION (pocet definovany v CNameWithResurrection.MResurrectionCounter).
			while(HandleToName.Target!=null)
			{
				GC.Collect();
				GC.WaitForPendingFinalizers();

				Console.WriteLine(string.Format("IsAllocated [{0}] !",HandleToName.IsAllocated));

				Thread.Sleep(1000);

				// Zrusim ROOT na CNameWithResurrection.
				CNameWithResurrection.ResetResurrectedObjectToNULL();
			}

			Console.WriteLine(string.Format("IsAllocated [{0}] !",HandleToName.IsAllocated));

			HandleToName.Free();

			Console.WriteLine(string.Format("IsAllocated [{0}] !",HandleToName.IsAllocated));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			try
			{
				int												Size=1;

				while(true)
				{
					// Alokuje vzdy 1 MB MEMORY.
					using (MemoryFailPoint MFP=new MemoryFailPoint(Size))
					{
						// Tu sa moze vykonat algoritmus NAROCNY na PAMAT.
						Console.WriteLine(string.Format("Reserved [{0}] MB of memory !",Size));
					}

					Size++;
				}
			}
			catch(InsufficientMemoryException E)
			{
				// The memory could not be reserved.
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
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
			Test20();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------