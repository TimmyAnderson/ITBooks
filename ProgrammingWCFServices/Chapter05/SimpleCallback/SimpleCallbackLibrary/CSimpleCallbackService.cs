using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace SimpleCallbackLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CSimpleCallbackService : ISimpleCallbackContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static CClientList<ISimpleCallbackCallback>		MClientList=new CClientList<ISimpleCallbackCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSimpleCallbackService()
		{
			Console.WriteLine("CSimpleCallbackService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void LaunchEvent(object Param)
		{
			CPair<string, int>		Pair=(CPair<string, int>) Param;

			Thread.Sleep(Pair.Second);
			MClientList.OnCallback(Pair.First);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CSimpleCallbackService.Connect() called !");
			MClientList.Add(new CClientListItem<ISimpleCallbackCallback>(OperationContext.Current.GetCallbackChannel<ISimpleCallbackCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine("CSimpleCallbackService.Disconnect() called !");
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<ISimpleCallbackCallback>());
        }
//-------------------------------------------------------------------------------------------------------
        public void DoSomething(string ClientName, string Message, int Timeout)
		{
			Console.WriteLine("CSimpleCallbackService.DoSomething() called !");
			// !!! Tu prave vyuzivam, fakt, ze v kazdom volani metody service je pritomny callback a mozem ho zaradit do zoznamu clietnov. Priacom ak uz je tak ho nezaradim.
			MClientList.Add(new CClientListItem<ISimpleCallbackCallback>(OperationContext.Current.GetCallbackChannel<ISimpleCallbackCallback>(),ClientName));


			// Do something.
			Thread		T=new Thread(new ParameterizedThreadStart(LaunchEvent));

			T.Start(new CPair<string, int>(Message, Timeout));
			Console.WriteLine("THREAD LAUNCHED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CSimpleCallbackService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------