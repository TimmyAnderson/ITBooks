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
namespace ImpersonationLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CImpersonationService : IImpersonationContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CImpersonationService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(Impersonation=ImpersonationOption.Allowed)]
		public void AutomaticImpersonation()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			WindowsIdentity		WI=OperationContext.Current.ServiceSecurityContext.WindowsIdentity;

			CDebugHelper.GetWindowsUserInfo(WI);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			Console.WriteLine();
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(Impersonation=ImpersonationOption.NotAllowed)]
		public void ManualImpersonation()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));
			
			// Ziskam aktualnu identitu.
			WindowsIdentity		WI0=WindowsIdentity.GetCurrent();

			// Ziskam identitu klietna.
			WindowsIdentity		WI1=OperationContext.Current.ServiceSecurityContext.WindowsIdentity;

			CDebugHelper.GetWindowsUserInfo(WI0);
			Console.WriteLine();

			try
			{
				// Dispose() urobi zaroven aj Undo().
				using(WindowsImpersonationContext WIC=WI1.Impersonate())
				{
					// Ziskam identitu po impersonation.
					WindowsIdentity		WI2=OperationContext.Current.ServiceSecurityContext.WindowsIdentity;

					Console.WriteLine(string.Format("Name: {0} !",WI2.Name));
					Console.WriteLine(string.Format("IsAuthenticated: {0} !",WI2.IsAuthenticated));
					Console.WriteLine();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}

			// Ziskam aktualnu identitu.
			WindowsIdentity		WI3=WindowsIdentity.GetCurrent();

			CDebugHelper.GetWindowsUserInfo(WI3);
			Console.WriteLine();

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
			Console.WriteLine();
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