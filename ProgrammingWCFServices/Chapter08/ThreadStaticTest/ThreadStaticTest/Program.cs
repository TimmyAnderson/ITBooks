using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
//-------------------------------------------------------------------------------------------------------
namespace ThreadStaticTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Thread			T1=new Thread(CThreadStatic.ThreadFunction);
			Thread			T2=new Thread(CThreadStatic.ThreadFunction);

			T1.Start(10);
			T2.Start(20);
			
			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------