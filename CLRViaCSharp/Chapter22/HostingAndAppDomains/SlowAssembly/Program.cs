using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace SlowAssembly
{
//-------------------------------------------------------------------------------------------------------
    public class CSlowAssembly
    {
//-------------------------------------------------------------------------------------------------------
		private static void ThreadMethod()
		{
			try
			{
				Console.WriteLine(string.Format("SlowAssembly - APP DOMAIN [{0}], THREAD [{1}] - THREAD STARTED !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));

				// !!! THREAD za zablokuje na dlhy cas. CLR ho pri AppDomain.Unload() ZLIKVIDUJE.
				Thread.Sleep(1000*1000);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("SlowAssembly - APP DOMAIN [{0}], THREAD [{1}] - THREAD CAUGHT EXCEPTION [{2}] !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId,E));
			}
			finally
			{
				Console.WriteLine(string.Format("SlowAssembly - APP DOMAIN [{0}], THREAD [{1}] - THREAD FINISHED !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));
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