using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyModesLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Single)]
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Reentrant)]
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Multiple)]
	public class CConcurrencyModesService : IConcurrencyModesContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static CClientList<IConcurrencyModesCallback>	MClientList=new CClientList<IConcurrencyModesCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CConcurrencyModesService()
		{
			Console.WriteLine("CConcurrencyModesService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void LaunchEventThread(object Param)
		{
			Console.WriteLine("LaunchEventThread() called 1 !");

			CPair<string, int>		Pair=(CPair<string, int>) Param;

			Thread.Sleep(Pair.Second);

			try
			{
				MClientList.OnCallback(Pair.First);
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
			Console.WriteLine("CConcurrencyModesService.Connect() called !");
			MClientList.Add(new CClientListItem<IConcurrencyModesCallback>(OperationContext.Current.GetCallbackChannel<IConcurrencyModesCallback>(), ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine("CConcurrencyModesService.Disconnect() called !");
			MClientList.Remove(OperationContext.Current.GetCallbackChannel<IConcurrencyModesCallback>());
        }
//-------------------------------------------------------------------------------------------------------
        public void SlowMethod(string Message, int Timeout)
		{
			Console.WriteLine(string.Format("CConcurrencyModesService.SlowMethod({0}) called 1 !",Message));

			Thread.Sleep(Timeout);

			Console.WriteLine(string.Format("CConcurrencyModesService.SlowMethod({0}) called 2 !",Message));
		}
//-------------------------------------------------------------------------------------------------------
		// Zasiela sa callback IBA senderovi.
        public void DoSynchroCallbackToJustSender(string Message, int Timeout)
		{
			Console.WriteLine("CConcurrencyModesService.DoSynchroCallbackToJustSender() called 1 !");

			IConcurrencyModesCallback		Callback=OperationContext.Current.GetCallbackChannel<IConcurrencyModesCallback>();
			string							ServerMessage=string.Format("SYNCHRO: {0}",Message);

			Thread.Sleep(Timeout);

			try
			{
				// Ak je ConcurrencyMode na Single tak dostanem exception kedze by toto volanie viedlo k deadlock.
				Callback.OnCallback(ServerMessage);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("DoSynchroCallback EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("CConcurrencyModesService.DoSynchroCallbackToJustSender() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		// Zasiela sa callback VSETKYM klientom.
        public void DoSynchroCallbackForAllClients(string Message, int Timeout)
		{
			Console.WriteLine("CConcurrencyModesService.DoSynchroCallbackForAllClients() called 1 !");

			IConcurrencyModesCallback		Callback=OperationContext.Current.GetCallbackChannel<IConcurrencyModesCallback>();
			string							ServerMessage=string.Format("SYNCHRO: {0}",Message);

			Thread.Sleep(Timeout);

			try
			{
				// !!!!! Simuluje dve veci.
				// 1. Ze ak sa hodi Exception tak chybne proxy vyhodi.
				// 2. Ak je ConcurrencyMode na Single potom JE MOZNE VOLAT INYCH KLIENTOV, ALE NIE TOHO, ktory zavolal tuto metodu.
				MClientList.OnCallback(ServerMessage);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("DoSynchroCallbackForAllClients EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("CConcurrencyModesService.DoSynchroCallbackForAllClients() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
        public void DoAsynchroCallback(string Message, int Timeout)
		{
			Console.WriteLine("CConcurrencyModesService.DoAsynchroCallback() called 1 !");

			// Do something.
			Thread							T=new Thread(new ParameterizedThreadStart(LaunchEventThread));
			string							ServerMessage=string.Format("ASYNCHRO: {0}",Message);

			T.Start(new CPair<string, int>(ServerMessage, Timeout));

			Console.WriteLine("CConcurrencyModesService.DoAsynchroCallback() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CConcurrencyModesService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------