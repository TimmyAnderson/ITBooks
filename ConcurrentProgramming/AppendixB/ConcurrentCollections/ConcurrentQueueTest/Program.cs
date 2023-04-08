using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Collections;
//------------------------------------------------------------------------------
namespace ConcurrentQueueTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static AutoResetEvent					MEvent=new AutoResetEvent(false);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Consumer(object Param)
		{
			ConcurrentQueue<int>			Collection=(ConcurrentQueue<int>) Param;

			while(true)
			{
				int				Value=-1;

				Console.WriteLine(string.Format("Consumer is trying to remove, count: [{0}] !",Collection.Count));

				// Ak nema hodnotu hned skonci s FALSE.
				bool			Ret=Collection.TryDequeue(out Value);

				Console.WriteLine(string.Format("Consumer consumed value: [{0}], return-value: [{1}], count: [{2}] !",Value,Ret,Collection.Count));

				if (MEvent.WaitOne(0)==true)
					break;

				Thread.Sleep(2000);
			}

			Console.WriteLine("Consumer FINISHED !");
		}
//------------------------------------------------------------------------------
		private static void Producer(object Param)
		{
			ConcurrentQueue<int>			Collection=(ConcurrentQueue<int>) Param;

			Thread.Sleep(500);

			for (int i=0;i<5;i++)
			{
				Thread.Sleep(1000);
				Console.WriteLine(string.Format("Producer generated item: [{0}] !",i+1));

				Collection.Enqueue(i+1);
			}

			MEvent.Set();

			Console.WriteLine("Producer FINISHED !");
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test()
		{
			ConcurrentQueue<int>			Collection=new ConcurrentQueue<int>();
			Thread							PC=new Thread(Consumer);
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
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------