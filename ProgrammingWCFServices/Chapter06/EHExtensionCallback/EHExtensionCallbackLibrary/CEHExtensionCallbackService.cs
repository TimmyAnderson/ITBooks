using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall, ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CEHExtensionCallbackService : IEHExtensionCallbackContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		static private CClientList<IEHExtensionCallbackCallback>	MClientList=new CClientList<IEHExtensionCallbackCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CEHExtensionCallbackService()
		{
			Console.WriteLine("CEHExtensionCallbackService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CEHExtensionCallbackService.Connect() called !");
			MClientList.Add(new CClientListItem<IEHExtensionCallbackCallback>(OperationContext.Current.GetCallbackChannel<IEHExtensionCallbackCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine("CEHExtensionCallbackService.Disconnect() called !");
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<IEHExtensionCallbackCallback>());
        }
//-------------------------------------------------------------------------------------------------------
		public void DoCallback(string Message)
		{
			Console.WriteLine("CEHExtensionCallbackService.DoCallback() called 1 !");

			// Exception sa zachytava dnu v metode MClientList.OnEvent().
			MClientList.OnEvent(Message);

			// Test ci CALLBACK PROXY ZIJE.
			MClientList.OnEvent(Message);

			Console.WriteLine("CEHExtensionCallbackService.DoCallback() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CEHExtensionCallbackService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------