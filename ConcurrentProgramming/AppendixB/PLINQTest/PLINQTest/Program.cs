using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Collections;
using System.Threading.ConcurrencyScheduler;
using System.Threading.Internal;
using System.Linq.Parallel;
//------------------------------------------------------------------------------
namespace PLINQTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static bool MyWhere(int Param)
		{
			Console.WriteLine(string.Format("MyWhere(): {0} !",Param));

			return(true);
		}
//------------------------------------------------------------------------------
		private static bool MyWhereWithException(int Param)
		{
			Console.WriteLine(string.Format("MyWhere(): {0} !",Param));

			if (Param==12)
				throw(new ArgumentException("Can't go beyond 12 !!!"));

			return(true);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		private static void Test1()
		{
			int[]							Numbers=new int[20];

			for (int i=0;i<Numbers.Length;i++)
				Numbers[i]=i+1;

			var								PE=	from I in Numbers.AsParallel()
												select I;

			foreach(int I in PE)
				Console.WriteLine(string.Format("Item: {0} !",I));
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			int[]							Numbers=new int[20];

			for (int i=0;i<Numbers.Length;i++)
				Numbers[i]=i+1;

			var								PE=Numbers.AsParallel().Where(MyWhere).Select(P => P);

			foreach(int I in PE)
				Console.WriteLine(string.Format("Item: {0} !",I));
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			int[]							Numbers=new int[20];

			for (int i=0;i<Numbers.Length;i++)
				Numbers[i]=i+1;
			
			var								PE=Numbers.AsParallel().AsSequential().Where(MyWhere).Select(P => P);

			foreach(int I in PE)
				Console.WriteLine(string.Format("Item: {0} !",I));
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			int[]							Numbers=new int[20];

			for (int i=0;i<Numbers.Length;i++)
				Numbers[i]=i+1;

			var								PE=Numbers.AsParallel().AsUnordered().Where(MyWhere).Select(P => P);

			foreach(int I in PE)
				Console.WriteLine(string.Format("Item: {0} !",I));
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			try
			{
				int[]							Numbers=new int[20];

				for (int i=0;i<Numbers.Length;i++)
					Numbers[i]=i+1;

				var								PE=Numbers.AsParallel().AsUnordered().Where(MyWhereWithException).Select(P => P);

				foreach(int I in PE)
					Console.WriteLine(string.Format("Item: {0} !",I));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}]",E));
			}
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			//Test3();
			//Test4();
			Test5();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------