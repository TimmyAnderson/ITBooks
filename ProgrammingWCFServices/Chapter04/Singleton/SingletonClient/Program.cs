using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SingletonLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SingletonClient
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

			// Vytvorim 2 klientov jednym zapisem stav a druhym ho vycitam.
			CSingletonProxy						Client1=null;
			CSingletonProxy						Client2=null;
			CState								StateIn=new CState(100,"Timmy");
			CState								StateOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client1=new CSingletonProxy(TCPBinding,"net.tcp://localhost:9001/ISingletonContract");
				Client2=new CSingletonProxy(TCPBinding,"net.tcp://localhost:9001/ISingletonContract");

				Client1.SetState(StateIn);
				Console.WriteLine(String.Format("Client1 send StateIn: {0}",StateIn.ToString()));
				Console.WriteLine();

				Console.WriteLine("Client1 is printing its state !");
				Client1.PrintActualState();
				Console.WriteLine("Client2 is printing its state !");
				Client2.PrintActualState();

				StateOut=Client2.GetState();
				Console.WriteLine(String.Format("Client2 retrieved StateOut: {0}",StateOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client1!=null && Client1.State!=CommunicationState.Faulted)
				{
					Client1.Close();
					Client1=null;
				}

				if (Client2!=null && Client2.State!=CommunicationState.Faulted)
				{
					Client2.Close();
					Client2=null;
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