using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace ExecutableAssembly
{
//-------------------------------------------------------------------------------------------------------
    public class CExecutableAssembly
    {
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.WriteLine(string.Format("ExecutableAssembly - APP DOMAIN [{0}], THREAD [{1}] !",AppDomain.CurrentDomain.FriendlyName,Thread.CurrentThread.ManagedThreadId));
		}
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------