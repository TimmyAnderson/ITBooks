using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleCallbackClient
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

			int									ID=new Random().Next(100,999);
			CSimpleCallbackProxy				Client=null;
			string								ClientName="C_" + ID;
			ISimpleCallbackCallback				CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				CallBack=new CSimpleCallbackCatcher();

				Client=new CSimpleCallbackProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/ISimpleCallbackContract");

				Client.Connect(ClientName);

				Client.DoSomething(ClientName,"HELLO CALLBACK " + ID,5*1000);

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