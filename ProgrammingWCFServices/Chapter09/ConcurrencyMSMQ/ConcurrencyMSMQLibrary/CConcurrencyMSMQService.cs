using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyMSMQLibrary
{
//-------------------------------------------------------------------------------------------------------
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single, ConcurrencyMode=ConcurrencyMode.Single)]
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single, ConcurrencyMode=ConcurrencyMode.Multiple)]
	public class CConcurrencyMSMQService : IConcurrencyMSMQContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyMSMQService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void PrintText(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Thread.Sleep(5*1000);
			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));

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