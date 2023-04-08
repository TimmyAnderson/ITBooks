using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace PLINQ
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static string LogSELECT(string Value)
		{
			Console.WriteLine(string.Format("LogSELECT(): [{0}] !",Value));

			return(Value.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
		private static string SlowLogSELECT(string Value)
		{
			Console.WriteLine(string.Format("BEGIN - SlowLogSELECT(): [{0}] !",Value));

			Thread.Sleep(5000);

			Console.WriteLine(string.Format("END - SlowLogSELECT(): [{0}] !",Value));

			return(Value.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
		private static void SlowForAll(string Value)
		{
			Console.WriteLine(string.Format("BEGIN - SlowForAll() - Value: [{0}] !",Value));

			Thread.Sleep(5000);

			Console.WriteLine(string.Format("END - SlowForAll() - Value: [{0}] !",Value));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			ParallelQuery<string>								PQ=Strings.AsParallel().Where(P => P.Length>1);

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Umyselne pridavam operacie, aby som trochu spomalil vykonavanie jednotlivych ITEMS.
			ParallelQuery<string>								PQ=Strings.AsParallel().AsUnordered().Where(P => P.Length>1).Select(MyLogSelect);

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Func<string,string>									MyLogSelect=SlowLogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			ParallelQuery<string>								PQ=Strings.AsParallel().Where(P => P.Length>1).Select(MyLogSelect);

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Umyselne pridavam operacie, aby som trochu spomalil vykonavanie jednotlivych ITEMS.
			ParallelQuery<string>								PQ=Strings.AsParallel().AsUnordered().Where(P => P.Length>1).Select(MyLogSelect);

			Console.WriteLine("!!! BEFORE FOREACH !");

			// !!! Vysledky budu taktiez spracovane PARALELNE. Teda jednotlive ITEMS FOR EACH budu vykonane PARALELNE.
			PQ.ForAll(P => Console.WriteLine(string.Format("Value: [{0}] !",P)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			// !!! Pouzije sa SLOW FUNCTION.
			Func<string,string>									MyLogSelect=SlowLogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Umyselne pridavam operacie, aby som trochu spomalil vykonavanie jednotlivych ITEMS.
			ParallelQuery<string>								PQ=Strings.AsParallel().AsUnordered().Where(P => P.Length>1).Select(MyLogSelect);

			Console.WriteLine("!!! BEFORE FOREACH !");

			// !!! Vysledky budu taktiez spracovane PARALELNE. Teda jednotlive ITEMS FOR EACH budu vykonane PARALELNE.
			PQ.ForAll(P => Console.WriteLine(string.Format("Value: [{0}] !",P)));
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Umyselne pridavam operacie, aby som trochu spomalil vykonavanie jednotlivych ITEMS.
			ParallelQuery<string>								PQ=Strings.AsParallel().AsUnordered().Where(P => P.Length>1).Select(MyLogSelect);

			Console.WriteLine("!!! BEFORE FOREACH !");

			// !!! Vysledky budu taktiez spracovane PARALELNE. Teda jednotlive ITEMS FOR EACH budu vykonane PARALELNE.
			// !!!!! PROBLEM je v tom, ze kedze SlowForAll() caka 5 SEKUND, tak ZABLOKUJE vykonavanie CELEHO THREAD POOL. To znaci, ze sa zablokuju na 5 SEKUND NIELEN TASKS vykonavajuce ForAll(), ale aj ESTE NEVYKONANE TASKS z PLINQ QUERY.
			PQ.ForAll(SlowForAll);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Umyselne pridavam operacie, aby som trochu spomalil vykonavanie jednotlivych ITEMS.
			ParallelQuery<string>								PQ=Strings.AsParallel().AsUnordered().Where(P => P.Length>1).Select(MyLogSelect).WithDegreeOfParallelism(30).WithExecutionMode(ParallelExecutionMode.ForceParallelism);

			Console.WriteLine("!!! BEFORE FOREACH !");

			// !!! Vysledky budu taktiez spracovane PARALELNE. Teda jednotlive ITEMS FOR EACH budu vykonane PARALELNE.
			// !!!!! PROBLEM je v tom, ze kedze SlowForAll() caka 5 SEKUND, tak ZABLOKUJE vykonavanie CELEHO THREAD POOL. To znaci, ze sa zablokuju na 5 SEKUND NIELEN TASKS vykonavajuce ForAll(), ale aj ESTE NEVYKONANE TASKS z PLINQ QUERY.
			// !!!!! Tento PROBLEM je tu ELIMINOVANY vdaka pouzitiu WithDegreeOfParallelism(30) a WithExecutionMode(ParallelExecutionMode.ForceParallelism), cim sa NUTI THREAD POOL, aby VYTVORIL DALSIE TASKS.
			PQ.ForAll(SlowForAll);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Umyselne pridavam operacie, aby som trochu spomalil vykonavanie jednotlivych ITEMS.
			ParallelQuery<string>								PQ=Strings.AsParallel().AsUnordered().Where(P => P.Length>1).Select(MyLogSelect);

			Console.WriteLine("!!! BEFORE ToArray() !");

			string[]											Items=PQ.ToArray();

			Console.WriteLine("!!! BEFORE FOREACH !");

			// !!! Vysledky budu taktiez spracovane PARALELNE. Teda FOR EACH bude vykonany PARALELNE.
			Items.AsParallel().ForAll(SlowForAll);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Vysledky BUDU ZOTRIEDENE.
			ParallelQuery<string>								PQ=Strings.AsParallel().AsOrdered().Where(P => P.Length>1).Select(MyLogSelect);

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Pouzijem WithExecutionMode(ParallelExecutionMode.ForceParallelism).
			ParallelQuery<string>								PQ=Strings.AsParallel().AsOrdered().Where(P => P.Length>1).Select(MyLogSelect).WithExecutionMode(ParallelExecutionMode.ForceParallelism);

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Pouzijem WithExecutionMode(ParallelExecutionMode.ForceParallelism).
			ParallelQuery<string>								PQ=Strings.AsParallel().AsOrdered().Where(P => P.Length>1).Select(MyLogSelect).WithExecutionMode(ParallelExecutionMode.ForceParallelism);

			Console.WriteLine("!!! BEFORE ToArray() !");

			string[]											SelectedStrigs=PQ.ToArray();

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in SelectedStrigs)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Pouzijem WithExecutionMode(ParallelExecutionMode.ForceParallelism).
			ParallelQuery<string>								PQ=Strings.AsParallel().Where(P => P.Length>1).Select(MyLogSelect).WithExecutionMode(ParallelExecutionMode.ForceParallelism);

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Pouzijem WithExecutionMode(ParallelExecutionMode.ForceParallelism).
			ParallelQuery<string>								PQ=Strings.AsParallel().Where(P => P.Length>1).Select(MyLogSelect).WithMergeOptions(ParallelMergeOptions.NotBuffered);

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			Func<string,string>									MyLogSelect=LogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			// Pouzijem WithExecutionMode(ParallelExecutionMode.ForceParallelism).
			ParallelQuery<string>								PQ=Strings.AsParallel().Where(P => P.Length>1).Select(MyLogSelect).WithMergeOptions(ParallelMergeOptions.FullyBuffered);

			Console.WriteLine("!!! BEFORE FOREACH !");

			foreach(string Value in PQ)
			{
				Console.WriteLine(string.Format("Value: [{0}] !",Value));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			// !!! Po 2 SEKUNDACH bude vykonany CANCELLATION.
			CancellationTokenSource								CTS=new CancellationTokenSource(2000);
			Func<string,string>									MyLogSelect=SlowLogSELECT;

			string[]											Strings=new string[]{"Timothy Anderson","Jennifer Thompson","Atreyu","Bubu","Tony Randal","Bart King","David Kong","Tina","Jane"};
			ParallelQuery<string>								PQ=Strings.AsParallel().Where(P => P.Length>1).Select(MyLogSelect).WithCancellation(CTS.Token);

			Console.WriteLine("!!! BEFORE FOREACH !");

			try
			{
				foreach(string Value in PQ)
				{
					Console.WriteLine(string.Format("Value: [{0}] !",Value));
				}
			}
			catch(Exception E)
			{
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
			Test15();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------