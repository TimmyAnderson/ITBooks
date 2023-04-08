using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.Remoting;
using System.Runtime.ExceptionServices;
//-------------------------------------------------------------------------------------------------------
namespace AppDomains
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void MainDomain_FirstChanceException(object Sender, FirstChanceExceptionEventArgs E)
		{
			string							CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("!!!!!! MAIN DOMAIN - FIRST CHANCE EXCEPTION - APP DOMAIN: [{0}] - EXCEPTION: [{1}] !",CurrentDomainName,E.Exception.Message));
		}
//-------------------------------------------------------------------------------------------------------
		private static void NewDomain_FirstChanceException(object Sender, FirstChanceExceptionEventArgs E)
		{
			string							CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("!!!!!! NEW DOMAIN - FIRST CHANCE EXCEPTION - APP DOMAIN: [{0}] - EXCEPTION: [{1}] !",CurrentDomainName,E.Exception.Message));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			AppDomain											MyDomain1=AppDomain.CreateDomain("MyDomain1");
			AppDomain											MyDomain2=AppDomain.CreateDomain("MyDomain2");

			// Spusti sa EXECUTEBLE ASSEMBLY v APP DOMAIN.
			MyDomain1.ExecuteAssembly("ExecutableAssembly.exe");
			// Spusti sa EXECUTEBLE ASSEMBLY v APP DOMAIN.
			MyDomain2.ExecuteAssembly("ExecutableAssembly.exe");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			AppDomain											MyDomain1=AppDomain.CreateDomain("MyDomain1");
			AppDomain											MyDomain2=AppDomain.CreateDomain("MyDomain2");
			
			// !!! Vytvori sa THREAD pre APP DOMAIN.
			ThreadStart											CreateThread1=new ThreadStart(() =>
			{
				MyDomain1.ExecuteAssembly("ExecutableAssembly.exe");
			});

			// !!! Vytvori sa THREAD pre APP DOMAIN.
			ThreadStart											CreateThread2=new ThreadStart(() =>
			{
				MyDomain2.ExecuteAssembly("ExecutableAssembly.exe");
			});

			Thread												Thread1=new Thread(CreateThread1);
			Thread												Thread2=new Thread(CreateThread2);

			Thread1.Start();
			Thread2.Start();

			Console.WriteLine(string.Format("MAIN - APP DOMAIN [{0}], THREAD [{1}] !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			AppDomain											MyDomain=AppDomain.CreateDomain("MyDomain");
			Type												MBRType=typeof(CName_MarshalByReference);

			// !!! Vytvori sa REMOTE OBJECT v REMOTE APP DOMAIN.
			ObjectHandle										OH=MyDomain.CreateInstance(MBRType.Assembly.FullName,MBRType.FullName);

			// !!! Z OBJECT HANDLE sa vytvori PROXY OBJECT v CURRENT APP DOMAIN.
			CName_MarshalByReference							MBR=(CName_MarshalByReference) OH.Unwrap();

			MBR.PrintFullName();

			// APP DOMAIN sa ODSTRANI.
			AppDomain.Unload(MyDomain);

			try
			{
				// Pri volani METHODz REMOTE APP DOMAIN dojde k EXCEPTION, pretoze APP DOMAIN uz bola odstranena a PROXY OBJECT referuje na NEEXISTUJUCI REMOTE OBJECT.
				MBR.PrintFullName();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));
			
			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			// Vytvorim REMOTE OBJECT v NewDomain.
			CName_MarshalByReference							Name=(CName_MarshalByReference) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_MarshalByReference");

			// Zistim ci Name je PROXY OBJECT.
			if (RemotingServices.IsTransparentProxy(Name)==true)
			{
				Console.WriteLine("Name IS PROXY !");
			}
			else
			{
				Console.WriteLine("Name IS NOT PROXY !");
			}

			// Volam metodu na VZDIALENEJ APP DOMAIN cez PROXY.
			Name.PrintFullName();

			// Uvolnim APP DOMAIN - vola sa i GC.
			AppDomain.Unload(NewDomain);

			Console.WriteLine("APP DOMAIN UNLOADED !");

			try
			{
				// Volam metodu na VZDIALENEJ APP DOMAIN cez PROXY.
				// !!! Zlyha, lebo APP DOMAIN uz bola ODSTRANENA.
				Name.PrintFullName();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));

			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			// Vytvorim REMOTE OBJECT v NewDomain.
			CName_MarshalByReference							Name=(CName_MarshalByReference) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_MarshalByReference");

			// Zistim ci Name je PROXY OBJECT.
			if (RemotingServices.IsTransparentProxy(Name)==true)
			{
				Console.WriteLine("Name IS PROXY !");
			}
			else
			{
				Console.WriteLine("Name IS NOT PROXY !");
			}

			// Volam metodu na VZDIALENEJ APP DOMAIN cez PROXY.
			Name.PrintFullName();

			Console.WriteLine("Waiting 20 seconds to EXPIRE LEASE !");
			Thread.Sleep(20*1000);

			try
			{
				// Volam metodu na VZDIALENEJ APP DOMAIN cez PROXY.
				// !!! Zlyha, lebo LEASE EXPIROVAL.
				Name.PrintFullName();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			// Uvolnim APP DOMAIN - vola sa i GC.
			AppDomain.Unload(NewDomain);

			Console.WriteLine("APP DOMAIN UNLOADED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));
			
			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			// Vytvorim REMOTE OBJECT v NewDomain, ktory kedze sa prenesie cez VALUE, tak sa vlastne vytvori KOPIA v AKTUALNEJ APP DOMAIN z OBJECTu vytvoreneho vo VZDIALENEJ APP DOMAIN.
			// !!!!! Remote OBJECT sa OKAMZITE STAVA ROOT-LESS, lebo vratena referencia je referencou na LOKALNU KOPIU v AKTUALNEJ APP DOMAIN a vytvoreny OBJECT vo VZDIALENEJ APP DOMAIN NEMA ROOT - ziadnu referovanu premennu.
			CName_MarshalByValue								Name=(CName_MarshalByValue) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_MarshalByValue");

			// Zistim ci Name je PROXY OBJECT.
			if (RemotingServices.IsTransparentProxy(Name)==true)
			{
				Console.WriteLine("Name IS PROXY !");
			}
			else
			{
				Console.WriteLine("Name IS NOT PROXY !");
			}

			// !!! Volam metodu, ktora sa vykona na AKTUALNEJ APP DOMAIN, pretoze PROXY NEBOLO vdaka MARSHAL BY VALUE VYTVORENE.
			Name.PrintFullName();

			// Uvolnim APP DOMAIN - vola sa i GC.
			AppDomain.Unload(NewDomain);

			Console.WriteLine("APP DOMAIN UNLOADED !");

			try
			{
				// !!! Volam metodu, ktora sa vykona na AKTUALNEJ APP DOMAIN, pretoze PROXY NEBOLO vdaka MARSHAL BY VALUE VYTVORENE.
				// !!! NEZLYHA, lebo Name je KOPIA, ktora ostava ZACHOVANA pri ZLIKVIDOVANI VZDIALENEJ APP DOMAIN.
				Name.PrintFullName();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));
			
			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			try
			{
				// !!!!! OBJECT vo VZDIALENEJ APP DOMAIN sa VYTVORI, ale kedze NIE JE MARSHALOVATELNY, tak jeho prenesenie cez HRANICE APP DOMAIN ZLYHA. OBJECT sa vsak vo vzdialenej APP DOMAIN VYTVORI.
				CName_NotMarshaled								Name=(CName_NotMarshaled) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_NotMarshaled");

				// Zistim ci Name je PROXY OBJECT.
				if (RemotingServices.IsTransparentProxy(Name)==true)
				{
					Console.WriteLine("Name IS PROXY !");
				}
				else
				{
					Console.WriteLine("Name IS NOT PROXY !");
				}

				try
				{
					// Volam metodu na VZDIALENEJ APP DOMAIN cez PROXY.
					// !!! NEZLYHA, lebo Name je KOPIA, ktora ostava ZACHOVANA pri ZLIKVIDOVANI VZDIALENEJ APP DOMAIN.
					Name.PrintFullName();
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			// Uvolnim APP DOMAIN - vola sa i GC.
			AppDomain.Unload(NewDomain);

			Console.WriteLine("APP DOMAIN UNLOADED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));
			
			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			try
			{
				// !!!!! Aj ked je CLASS oznacena pomocou [DataContract], tak takato CLASS NIE JE POVAZOVANA za SERIALIZABLE a NIE JE PRENOSITELNA cez APP DOMAINS.
				CName_MarshalByValueDataContract					Name=(CName_MarshalByValueDataContract) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_MarshalByValueDataContract");

				// Zistim ci Name je PROXY OBJECT.
				if (RemotingServices.IsTransparentProxy(Name)==true)
				{
					Console.WriteLine("Name IS PROXY !");
				}
				else
				{
					Console.WriteLine("Name IS NOT PROXY !");
				}

				// !!! Volam metodu, ktora sa vykona na AKTUALNEJ APP DOMAIN, pretoze PROXY NEBOLO vdaka MARSHAL BY VALUE VYTVORENE.
				Name.PrintFullName();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));

			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			// Vytvorim REMOTE OBJECT v NewDomain.
			CName_MarshalByReferenceWithFields					Name=(CName_MarshalByReferenceWithFields) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_MarshalByReferenceWithFields");

			// Zistim ci Name je PROXY OBJECT.
			if (RemotingServices.IsTransparentProxy(Name)==true)
			{
				Console.WriteLine("Name IS PROXY !");
			}
			else
			{
				Console.WriteLine("Name IS NOT PROXY !");
			}

			// PROXY zabezpecuje, ze sa FIELDS nastavia na REMOTE OBJECT v REMOTE APP DOMAIN.
			Name.MFirstName="Timmy";
			Name.MLastName="Anderson";
			Name.MAge=12;

			// PROXY zabezpecuje, ze sa FIELDS citaju z REMOTE OBJECT v REMOTE APP DOMAIN.
			Console.WriteLine(string.Format("NAME [{0} {1}], AGE [{2}] !",Name.MFirstName,Name.MLastName,Name.MAge));

			// Uvolnim APP DOMAIN - vola sa i GC.
			AppDomain.Unload(NewDomain);

			Console.WriteLine("APP DOMAIN UNLOADED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			AppDomain											MyDomain=AppDomain.CreateDomain("MyDomain");

			Console.WriteLine(string.Format("MAIN - APP DOMAIN [{0}], THREAD [{1}] - DOMAIN will be EXECUTED !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

			// Spusti sa EXECUTEBLE ASSEMBLY v APP DOMAIN.
			MyDomain.ExecuteAssembly("SlowAssembly.exe");

			Console.WriteLine(string.Format("MAIN - APP DOMAIN [{0}], THREAD [{1}] - DOMAIN will be UNLOADED !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

			AppDomain.Unload(MyDomain);

			Console.WriteLine(string.Format("MAIN - APP DOMAIN [{0}], THREAD [{1}] - DOMAIN was UNLOADED !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			AppDomain											MyDomain=AppDomain.CreateDomain("MyDomain");

			Console.WriteLine(string.Format("MAIN [{0}] - APP DOMAIN [{1}], THREAD [{2}] - DOMAIN will be EXECUTED !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

			// Spusti sa EXECUTEBLE ASSEMBLY v APP DOMAIN.
			MyDomain.ExecuteAssembly("SlowFinallyAssembly.exe");

			Console.WriteLine(string.Format("MAIN [{0}] - APP DOMAIN [{1}], THREAD [{2}] - DOMAIN will be UNLOADED !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

			try
			{
				// !!!!! Kedze APP DOMAIN THREAD sa zablokoval v CRITICAL CODE (FINALLY) na 30 sekund co je dlhsie ako 10 sekundovy TIMEOUT, kedy AppDomain.Unload() caka na ukocenie THREAD, METHOD AppDomain.Unload() generuje EXCEPTION [CannotUnloadAppDomainException].
				AppDomain.Unload(MyDomain);

				Console.WriteLine(string.Format("MAIN [{0}] - APP DOMAIN [{1}], THREAD [{2}] - DOMAIN was UNLOADED !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("MAIN [{0}] - APP DOMAIN [{1}], THREAD [{2}] - DOMAIN FAILED to FINISH [{3}] !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId,E));

				// !!!!! THREAD, ktory vo FINALLY caka 30 sekund, skonci za po 30 sekundach a nie 20 (30-10 sekund na ktore cakala METHOD AppDomain.Unload() na ukoncenie THREADU), pretoze pocas volania METHOD AppDomain.Unload() su VSETKY THREAD SUSPENDED.
				Console.WriteLine("!!!!!! WAIT 30 SECONDS !!!!!!");
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			// Zapnem MONITORING APP DOMAINS.
			AppDomain.MonitoringIsEnabled=true;

			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));

			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			Console.WriteLine(string.Format("MonitoringSurvivedMemorySize: [{0}] !",NewDomain.MonitoringSurvivedMemorySize));
			Console.WriteLine(string.Format("MonitoringTotalAllocatedMemorySize: [{0}] !",NewDomain.MonitoringTotalAllocatedMemorySize));
			Console.WriteLine(string.Format("MonitoringTotalProcessorTime: [{0}] !",NewDomain.MonitoringTotalProcessorTime));
			Console.WriteLine(string.Format("MonitoringSurvivedProcessMemorySize: [{0}] !",AppDomain.MonitoringSurvivedProcessMemorySize));

			// Vytvorim REMOTE OBJECT v NewDomain.
			CName_MarshalByReference							Name=(CName_MarshalByReference) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_MarshalByReference");

			// Zistim ci Name je PROXY OBJECT.
			if (RemotingServices.IsTransparentProxy(Name)==true)
			{
				Console.WriteLine("Name IS PROXY !");
			}
			else
			{
				Console.WriteLine("Name IS NOT PROXY !");
			}

			// Volam metodu na VZDIALENEJ APP DOMAIN cez PROXY.
			Name.PrintFullName();

			Console.WriteLine(string.Format("MonitoringSurvivedMemorySize: [{0}] !",NewDomain.MonitoringSurvivedMemorySize));
			Console.WriteLine(string.Format("MonitoringTotalAllocatedMemorySize: [{0}] !",NewDomain.MonitoringTotalAllocatedMemorySize));
			Console.WriteLine(string.Format("MonitoringTotalProcessorTime: [{0}] !",NewDomain.MonitoringTotalProcessorTime));
			Console.WriteLine(string.Format("MonitoringSurvivedProcessMemorySize: [{0}] !",AppDomain.MonitoringSurvivedProcessMemorySize));

			// Uvolnim APP DOMAIN - vola sa i GC.
			AppDomain.Unload(NewDomain);

			Console.WriteLine("APP DOMAIN UNLOADED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			string												CurrentDomainName=AppDomain.CurrentDomain.FriendlyName;

			Console.WriteLine(string.Format("MAIN DOMAIN: [{0}] !",CurrentDomainName));
			
			AppDomain											NewDomain=AppDomain.CreateDomain("TestDomain");

			// Zaregistruje zachytavanie FIRST CHANCE EXCEPTIONS v CURRENT aj NEW APP DOMAINS.
			AppDomain.CurrentDomain.FirstChanceException+=new EventHandler<FirstChanceExceptionEventArgs>(MainDomain_FirstChanceException);
			NewDomain.FirstChanceException+=new EventHandler<FirstChanceExceptionEventArgs>(NewDomain_FirstChanceException);

			// Vytvorim REMOTE OBJECT v NewDomain.
			CName_MarshalByReference							Name=(CName_MarshalByReference) NewDomain.CreateInstanceAndUnwrap("AppDomains","AppDomains.CName_MarshalByReference");

			// Zistim ci Name je PROXY OBJECT.
			if (RemotingServices.IsTransparentProxy(Name)==true)
			{
				Console.WriteLine("Name IS PROXY !");
			}
			else
			{
				Console.WriteLine("Name IS NOT PROXY !");
			}

			try
			{
				// !!! Volam metodu na VZDIALENEJ APP DOMAIN cez PROXY, ktora GENERUJE EXCEPTION.
				// !!! Vzdialena APP DOMAIN EXCEPTION NEZACHYTI a tak je EXCEPTION PRENESENA do AKTUALNEJ APP DOMAIN pomocou SERIALIZACIE, kde je DESERIALIZOVANA a ZNOVA HODENA.
				Name.PrintFullNameAndThrowException();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("APP DOMAIN: [{0}] - EXCEPTION: [{1}] !",CurrentDomainName,E));
			}

			// Uvolnim APP DOMAIN - vola sa i GC.
			AppDomain.Unload(NewDomain);

			Console.WriteLine("APP DOMAIN UNLOADED !");
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
			Test13();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------