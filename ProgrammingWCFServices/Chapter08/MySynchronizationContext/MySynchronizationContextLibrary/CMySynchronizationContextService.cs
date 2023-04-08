using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContextLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall, UseSynchronizationContext=true)]
	public class CMySynchronizationContextService : IMySynchronizationContextContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CMySynchronizationContextService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void ShowText(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(Thread.CurrentThread.ManagedThreadId));

			Console.WriteLine(string.Format("MESSAGE: {0} !",Message));

			Thread.Sleep(3*1000);

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