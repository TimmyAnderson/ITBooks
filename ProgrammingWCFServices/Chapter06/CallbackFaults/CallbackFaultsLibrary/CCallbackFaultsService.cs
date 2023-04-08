using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace CallbackFaultsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall, ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CCallbackFaultsService : ICallbackFaultsContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		static private CClientList<ICallbackFaultsCallback>		MClientList=new CClientList<ICallbackFaultsCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCallbackFaultsService()
		{
			Console.WriteLine("CCallbackFaultsService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void LaunchNonFaultThread(object Param)
		{
			Console.WriteLine("CCallbackFaultsService.LaunchNonFaultThread() 1 !");

			CPair<string, int>		Pair=(CPair<string, int>) Param;

			Thread.Sleep(Pair.Second);
			MClientList.NonFaultCallback(Pair.First);

			Console.WriteLine("CCallbackFaultsService.LaunchNonFaultThread() 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		static void LaunchFaultThread(object Param)
		{
			Console.WriteLine("CCallbackFaultsService.LaunchFaultThread() 1 !");

			CPair<string, int>		Pair=(CPair<string, int>) Param;

			Thread.Sleep(Pair.Second);
			MClientList.FaultCallback(Pair.First);

			Console.WriteLine("CCallbackFaultsService.LaunchFaultThread() 2 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CCallbackFaultsService.Connect() called !");
			MClientList.Add(new CClientListItem<ICallbackFaultsCallback>(OperationContext.Current.GetCallbackChannel<ICallbackFaultsCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine("CSimpleCallbackService.Disconnect() called !");
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<ICallbackFaultsCallback>());
        }
//-------------------------------------------------------------------------------------------------------
		public void SynchroNonFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsService.SynchroNonFaultException() called 1 !");

			Thread.Sleep(Timeout);

			// Callback proxy je mrtve.
			MClientList.NonFaultCallback(Message);

			Console.WriteLine("CCallbackFaultsService.SynchroNonFaultException() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		public void AsynchroNonFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsService.AsynchroNonFaultException() called !");

			// Do something.
			Thread		T=new Thread(new ParameterizedThreadStart(LaunchNonFaultThread));

			T.Start(new CPair<string, int>(Message, Timeout));
			Console.WriteLine("THREAD LAUNCHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void SynchroFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsService.SynchroFaultException() called 1 !");

			Thread.Sleep(Timeout);

			MClientList.FaultCallback(Message);

			Console.WriteLine("CCallbackFaultsService.SynchroFaultException() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		public void AsynchroFaultException(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackFaultsService.AsynchroFaultException() called !");

			// Do something.
			Thread		T=new Thread(new ParameterizedThreadStart(LaunchFaultThread));

			T.Start(new CPair<string, int>(Message, Timeout));
			Console.WriteLine("THREAD LAUNCHED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CCallbackFaultsService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------