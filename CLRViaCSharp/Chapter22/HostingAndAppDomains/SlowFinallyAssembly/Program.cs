using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace SlowFinallyAssembly
{
//-------------------------------------------------------------------------------------------------------
    public class CSlowFinallyAssembly
    {
//-------------------------------------------------------------------------------------------------------
		private static void ThreadMethod()
		{
			try
			{
				Console.WriteLine(string.Format("SlowFinallyAssembly [{0}] - APP DOMAIN [{1}], THREAD [{2}] - THREAD STARTED !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

				// !!! THREAD za zablokuje na dlhy cas. CLR ho pri AppDomain.Unload() ZLIKVIDUJE.
				Thread.Sleep(1000*1000);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("SlowFinallyAssembly [{0}] - APP DOMAIN [{1}], THREAD [{2}] - THREAD CAUGHT EXCEPTION [{3}] !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId,E));
			}
			finally
			{
				Console.WriteLine(string.Format("SlowFinallyAssembly [{0}] - APP DOMAIN [{1}], THREAD [{2}] - THREAD will FINISH in 30 SECONDS !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

				// !!! THREAD za zablokuje na dlhsi cas. CLR po 10 sekundach hodi EXCEPTION z METHOD AppDomain.Unload().
				Thread.Sleep(30*1000);

				Console.WriteLine(string.Format("SlowFinallyAssembly [{0}] - APP DOMAIN [{1}], THREAD [{2}] - THREAD FINISHED !",DateTime.Now,AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine(string.Format("SlowAssembly - APP DOMAIN [{0}], THREAD [{1}] !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

			// V REMOTE APP DOMAIN sa vytvori THREAD.
			Thread												T=new Thread(ThreadMethod);

			T.Start();
		}
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------