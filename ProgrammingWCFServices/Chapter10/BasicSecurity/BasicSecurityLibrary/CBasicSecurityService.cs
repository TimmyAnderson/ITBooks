using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace BasicSecurityLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CBasicSecurityService : IBasicSecurityContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CBasicSecurityService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			WindowsIdentity		WI=OperationContext.Current.ServiceSecurityContext.WindowsIdentity;

			CDebugHelper.GetWindowsUserInfo(WI);

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