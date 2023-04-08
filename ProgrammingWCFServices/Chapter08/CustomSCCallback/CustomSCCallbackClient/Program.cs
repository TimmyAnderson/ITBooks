using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CustomSCCallbackLibrary;
using MySynchronizationContext;
//-------------------------------------------------------------------------------------------------------
namespace CustomSCCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CCustomSCCallbackProxy				Client=null;
			ICustomSCCallbackCallback			CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			CMySynchronizationContext			MySynchronizationContext=new CMySynchronizationContext();

			// !!! Nastavim SynchronizationContext.
			SynchronizationContext.SetSynchronizationContext(MySynchronizationContext);

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				CallBack=new CCustomSCCallbackCatcher();

				Client=new CCustomSCCallbackProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/ICustomSCCallbackContract");

				Client.Connect("Client");

				Console.WriteLine(string.Format("{0} - TID: {1} !",CDebugHelper.GetMethodCallString(),Thread.CurrentThread.ManagedThreadId));
				Client.CallCallback("HELLO CALLBACK");

				Console.WriteLine("ALL OK !\n");

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.Disconnect();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					// !!! Interny thread SynchronizationContext je treba zastavit volanim Dispose().
					MySynchronizationContext.Dispose();

					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");

					Client=null;
				}
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------