using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace CustomSCCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall, ConcurrencyMode=ConcurrencyMode.Single)]
	public class CCustomSCCallbackService : ICustomSCCallbackContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		static private CClientList<ICustomSCCallbackCallback>	MClientList=new CClientList<ICustomSCCallbackCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCustomSCCallbackService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void LaunchEvent(object Param)
		{
			string			Message=(string) Param;

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(1),Message));

			MClientList.OnCallback(Message);

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(2),Message));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			MClientList.Add(new CClientListItem<ICustomSCCallbackCallback>(OperationContext.Current.GetCallbackChannel<ICustomSCCallbackCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine(CDebugHelper.GetMethodCallString());
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<ICustomSCCallbackCallback>());
        }
//-------------------------------------------------------------------------------------------------------
        public void CallCallback(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			// Do something.
			Thread			T1=new Thread(new ParameterizedThreadStart(LaunchEvent));
			Thread			T2=new Thread(new ParameterizedThreadStart(LaunchEvent));

			T1.Start(Message + "_1");
			T2.Start(Message + "_2");

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