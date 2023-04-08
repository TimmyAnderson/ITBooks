using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace Promise
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void CalculateValueThread(object Param)
		{
			CPromise<int>			MyPromise=(CPromise<int>) Param;

			Thread.Sleep(3000);

			// Nastavim hodnotu Promise - ktoru som vypocital.
			MyPromise.Value=60;
		}
//------------------------------------------------------------------------------
		private static void PromiseCallback(int PromiseValue)
		{
			Console.WriteLine(string.Format("PROMISE VALUE: [{0}] !",PromiseValue));
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CPromise<int>			MyPromise=new CPromise<int>();
			Thread					T=new Thread(CalculateValueThread);
			
			T.Start(MyPromise);

			Console.WriteLine("Getting PROMISE value !");

			int					Value=MyPromise.Value;

			Console.WriteLine(string.Format("PROMISE VALUE: [{0}] !",Value));
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CPromise<int>			MyPromise=new CPromise<int>();
			Thread					T=new Thread(CalculateValueThread);
			
			// Zaregistrujem CALLBACK.
			MyPromise.When(PromiseCallback);

			T.Start(MyPromise);

			Console.WriteLine("Getting PROMISE value !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------