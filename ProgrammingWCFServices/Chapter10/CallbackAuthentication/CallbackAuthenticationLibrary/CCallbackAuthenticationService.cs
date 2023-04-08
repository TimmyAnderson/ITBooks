using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using System.Security.Principal;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
// 1. Autentifikaciu a kryptovanie je pri callback mozne nastavit iba na urovni metody nie celeho callback rozhrania.
// 2. V callback nemam autentifikaciu a dostava ako Principal a Identity iba prazdne hodnoty.
//-------------------------------------------------------------------------------------------------------
namespace CallbackAuthenticationLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CCallbackAuthenticationService : ICallbackAuthenticationContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		static private CClientList<ICallbackAuthenticationCallback>	MClientList=new CClientList<ICallbackAuthenticationCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCallbackAuthenticationService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			MClientList.Add(new CClientListItem<ICallbackAuthenticationCallback>(OperationContext.Current.GetCallbackChannel<ICallbackAuthenticationCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine(CDebugHelper.GetMethodCallString());
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<ICallbackAuthenticationCallback>());
        }
//-------------------------------------------------------------------------------------------------------
		public void DoCallback()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			WindowsIdentity		WI=OperationContext.Current.ServiceSecurityContext.WindowsIdentity;

			Console.WriteLine(string.Format("Name: {0} !",WI.Name));

			MClientList.OnCallback();

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