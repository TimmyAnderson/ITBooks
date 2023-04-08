using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
//------------------------------------------------------------------------------
namespace SpinWaitTest
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test()
		{
			SpinWait			SW=new SpinWait();
			int					Counter=0;

			SW.SpinOnce();

			while(true)
			{
				if (SW.NextSpinWillYield==true)
				{
					Console.WriteLine(string.Format("Now you SHOULD employ REAL LOCK - Counter: [{0}], SW.Count: [{1}] !",Counter,SW.Count));
					break;
				}
				else
				{
					Counter++;
					SW.SpinOnce();
				}
			}
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