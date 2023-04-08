using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace TransportSessionsSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	public static class CTestHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static string SomeServiceMethod(string Param)
		{
			Console.WriteLine(string.Format("[{0}] SESSION_ID: [{1}] !",Param,OperationContext.Current.SessionId));

			return(Param.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static void WorkerThreadMethod(object Param)
		{
			ISimpleService			Proxy=(ISimpleService) Param;

			Proxy.SomeServiceMethod("WORKER thread");
		}
//-------------------------------------------------------------------------------------------------------
		public static void SimpleTest<T>(string ConfigName) where T : class, ISimpleService
		{
			try
			{
				using(ChannelFactory<T> CF=new ChannelFactory<T>(ConfigName))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						IContextChannel 		CC=(IContextChannel) Disp;

						CC.Open();

						Console.WriteLine(string.Format("SessionID: {0} !",CC.SessionId));

						T						Proxy=Disp as T;
						Thread					WorkerThread=new Thread(WorkerThreadMethod);

						WorkerThread.Start(Proxy);

						Proxy.SomeServiceMethod("PRIMARY thread");

						WorkerThread.Join();
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------