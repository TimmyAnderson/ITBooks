using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace SCCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall, ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CSCCallbackWithoutSCService : ISCCallbackWithoutSCContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static CClientList2<ISCCallbackWithoutSCCallback>	MClientList=new CClientList2<ISCCallbackWithoutSCCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSCCallbackWithoutSCService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			MClientList.Add(new CClientListItem<ISCCallbackWithoutSCCallback>(OperationContext.Current.GetCallbackChannel<ISCCallbackWithoutSCCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine(CDebugHelper.GetMethodCallString());
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<ISCCallbackWithoutSCCallback>());
        }
//-------------------------------------------------------------------------------------------------------
        public void DoCallback(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			MClientList.OnCallback(Message);

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