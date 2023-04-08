using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall, ConcurrencyMode=ConcurrencyMode.Single)]
	public class CConcurrencyCallbackService : IConcurrencyCallbackContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		static private CClientList<IConcurrencyCallbackCallback>	MClientList=new CClientList<IConcurrencyCallbackCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyCallbackService()
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
			MClientList.Add(new CClientListItem<IConcurrencyCallbackCallback>(OperationContext.Current.GetCallbackChannel<IConcurrencyCallbackCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine(CDebugHelper.GetMethodCallString());
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<IConcurrencyCallbackCallback>());
        }
//-------------------------------------------------------------------------------------------------------
        public void CallCallbackWithoutWait(string Message)
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
        public void CallCallbackWithWait(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			// Do something.
			Thread			T1=new Thread(new ParameterizedThreadStart(LaunchEvent));
			Thread			T2=new Thread(new ParameterizedThreadStart(LaunchEvent));

			T1.Start(Message + "_1");
			T2.Start(Message + "_2");

			// Pockam kym thready skoncia.
			Thread.Sleep(15*1000);

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