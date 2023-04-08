using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencySingleLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession,ConcurrencyMode=ConcurrencyMode.Single)]
	public class CConcurrencySingleService : IConcurrencySingleContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencySingleService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public void SlowMethod(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			Thread.Sleep(5*1000);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------