using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyMultipleLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession,ConcurrencyMode=ConcurrencyMode.Multiple)]
	public class CConcurrencyMultipleService : IConcurrencyMultipleContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyMultipleService()
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
        [MethodImpl(MethodImplOptions.Synchronized)]
		public void MethodImplTest(string Message)
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