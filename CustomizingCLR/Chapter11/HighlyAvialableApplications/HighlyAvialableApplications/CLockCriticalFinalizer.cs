using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.ConstrainedExecution;
using System.Threading;
//------------------------------------------------------------------------------------------------------
namespace HighlyAvialableApplications
{
//------------------------------------------------------------------------------------------------------
	public sealed class CLockCriticalFinalizer : CriticalFinalizerObject
	{
//------------------------------------------------------------------------------------------------------
		~CLockCriticalFinalizer()
		{
			Console.WriteLine("FINALIZER CLockCriticalFinalizer CALLED !");
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		public void DoSomething()
		{
			Console.WriteLine("CLockCriticalFinalizer.DoSomething() CALLED and LOCK will OCCUR !");

			Thread.Sleep(int.MaxValue);
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------