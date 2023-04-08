using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace CallbackContractHierarchyLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Single)]
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Reentrant)]
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Multiple)]
	public class CCallbackContractHierarchyService : ICallbackContractHierarchyContract2, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		static private CClientList<ICallbackContractHierarchyCallback2> MClientList = new CClientList<ICallbackContractHierarchyCallback2>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCallbackContractHierarchyService()
		{
			Console.WriteLine("CCallbackContractHierarchyService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void LaunchEvent1Thread(object Param)
		{
			Console.WriteLine("LaunchEventThread() called 1 !");

			CPair<string, int>		Pair=(CPair<string, int>) Param;

			Thread.Sleep(Pair.Second);

			try
			{
				MClientList.OnCallback1(Pair.First);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("LAUNCH EVENT THREAD EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("LaunchEventThread() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		static void LaunchEvent2Thread(object Param)
		{
			Console.WriteLine("LaunchEventThread() called 1 !");

			CTriple<string, string, int>		Triple=(CTriple<string, string, int>) Param;

			Thread.Sleep(Triple.Third);

			try
			{
				MClientList.OnCallback2(Triple.First, Triple.Second);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("LAUNCH EVENT THREAD EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("LaunchEventThread() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine("CCallbackContractHierarchyService.Connect() called !");
			MClientList.Add(new CClientListItem<ICallbackContractHierarchyCallback2>(OperationContext.Current.GetCallbackChannel<ICallbackContractHierarchyCallback2>(), ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine("CCallbackContractHierarchyService.Disconnect() called !");
			MClientList.Remove(OperationContext.Current.GetCallbackChannel<ICallbackContractHierarchyCallback2>());
        }
//-------------------------------------------------------------------------------------------------------
        public void CallCallback1(string Message, int Timeout)
		{
			Console.WriteLine("CCallbackContractHierarchyService.CallCallback1() called 1 !");

			// Do something.
			Thread							T=new Thread(new ParameterizedThreadStart(LaunchEvent1Thread));
			string							ServerMessage=string.Format("ASYNCHRO: {0}",Message);

			T.Start(new CPair<string, int>(ServerMessage, Timeout));

			Console.WriteLine("CCallbackContractHierarchyService.CallCallback1() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
        public void CallCallback2(string MessagePart1, string MessagePart2, int Timeout)
		{
			Console.WriteLine("CCallbackContractHierarchyService.CallCallback2() called 1 !");

			// Do something.
			Thread							T=new Thread(new ParameterizedThreadStart(LaunchEvent2Thread));
			string							ServerMessage1=string.Format("ASYNCHRO: {0}",MessagePart1);
			string							ServerMessage2=string.Format("ASYNCHRO: {0}",MessagePart2);

			T.Start(new CTriple<string, string, int>(ServerMessage1, ServerMessage2, Timeout));

			Console.WriteLine("CCallbackContractHierarchyService.CallCallback2() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CCallbackContractHierarchyService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------