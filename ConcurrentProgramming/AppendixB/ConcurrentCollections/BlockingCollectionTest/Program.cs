using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Collections;
//------------------------------------------------------------------------------
namespace BlockingCollectionTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Consumer(object Param)
		{
			BlockingCollection<int>			Collection=(BlockingCollection<int>) Param;

			while(true)
			{
				int				Value=-1;

				Console.WriteLine(string.Format("Consumer is trying to remove, count: [{0}] !",Collection.Count));

				bool			Ret=Collection.TryRemove(out Value,Timeout.Infinite);

				Console.WriteLine(string.Format("Consumer consumed value: [{0}], return-value: [{1}], count: [{2}] !",Value,Ret,Collection.Count));

				if (Ret==false)
					break;

				Thread.Sleep(2000);
			}

			Console.WriteLine("Consumer FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void ConsumerEnumerator(object Param)
		{
			BlockingCollection<int>			Collection=(BlockingCollection<int>) Param;
			IEnumerable<int>				Enumerator=Collection.GetConsumingEnumerable();

			foreach(int Value in Enumerator)
			{
				Console.WriteLine(string.Format("Consumer consumed value: [{0}], count: [{1}] !",Value,Collection.Count));

				Thread.Sleep(2000);
			}

			Console.WriteLine("Consumer FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Producer(object Param)
		{
			BlockingCollection<int>			Collection=(BlockingCollection<int>) Param;

			Thread.Sleep(500);

			for (int i=0;i<5;i++)
			{
				Thread.Sleep(1000);
				Console.WriteLine(string.Format("Producer generated item: [{0}] !",i+1));

				Collection.Add(i+1);
			}

			Collection.CompleteAdding();

			Console.WriteLine("CompleteAdding() CALLED - Producer FINISHED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			BlockingCollection<int>			Collection=new BlockingCollection<int>();
			Thread							PC=new Thread(Consumer);
			Thread							PP=new Thread(Producer);

			PC.Start(Collection);
			PP.Start(Collection);

			PC.Join();
			PP.Join();
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			BlockingCollection<int>			Collection=new BlockingCollection<int>();
			Thread							PC=new Thread(ConsumerEnumerator);
			Thread							PP=new Thread(Producer);

			PC.Start(Collection);
			PP.Start(Collection);

			PC.Join();
			PP.Join();
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