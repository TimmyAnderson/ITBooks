using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace GCDebugVSReleaseBuild
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void MyTimerCallback(object O)
		{
			Console.WriteLine("MyTimerCallback() CALLED !!!");

			// !!! Vykonava GC.
			GC.Collect();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			// !!! TIMER vykonava GC.
			// !!!!! Timer sa bude volat NEUSTALE a to preto, lebo NESKOR v CODE este volam T.Dispose() a teda na objekt sa STALE REFERUJE premenna 'T'.
			Timer												T=new Timer(MyTimerCallback,null,0,500);

			Console.WriteLine("Press any key to STOP TIMER !");
			Console.ReadLine();

			T.Dispose();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			// !!! TIMER vykonava GC.
			Timer												T=new Timer(MyTimerCallback,null,0,500);

			// !!! Timer sa zavola IBA RAZ, lebo na Time sa 'T' uz NEREFERUJE.
			T=null;

			Console.WriteLine("Press any key to STOP TIMER !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			// !!! TIMER vykonava GC.
			// !!!!! V RELEASE VERZII sa Timer zavola IBA RAZ, lebo po tomto riadku sa uz na Timer NEREFERUJE 'T'.
			// !!!!! V DEBUG VERZII sa Timer vola NEUSTALE, lebo v DEBUG verzii C# UMYSELNE PREDLZUJE ZIVOTNOST LOKALNYCH PREMENNYCH AZ PO SKONCENIE KODU METODY, aby sa dali LAHSIE DEBUGGOVAT.
			Timer												T=new Timer(MyTimerCallback,null,0,500);

			Console.WriteLine("Press any key to STOP TIMER !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			// !!! TIMER vykonava GC.
			// !!!!! V RELEASE VERZII sa Timer zavola IBA RAZ.
			// !!!!! V DEBUG VERZII sa Timer vola NEUSTALE.
			Timer												T=new Timer(MyTimerCallback,null,0,500);

			Console.WriteLine("Press any key to STOP TIMER !");
			Console.ReadLine();

			// !!!!! V RELEASE BUILD je tento riadok VYHODENY vdaka OPTIMALIZACII, co znaci, ze na 'T' sa uz STRATILA REFERENCIA HNED NA ZACIATKU METODY a vysledok je taky, ze TIMER SA VOLA IBA RAZ.
			T=null;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			Test4();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------