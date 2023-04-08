using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using InstanceDeactivationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace InstanceDeactivationClient
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

			CInstanceDeactivationProxy			Client1=null;
			CInstanceDeactivationProxy			Client2=null;
			CInstanceDeactivationProxy			Client3=null;
			CInstanceDeactivationProxy			Client4=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();
			NetTcpBinding						TCPBinding3=new NetTcpBinding();
			NetTcpBinding						TCPBinding4=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;
			TCPBinding3.ReliableSession.Enabled=true;
			TCPBinding4.ReliableSession.Enabled=true;

			try
			{
				Client1=new CInstanceDeactivationProxy(TCPBinding1,"net.tcp://localhost:9001/IInstanceDeactivationContract");
				Client2=new CInstanceDeactivationProxy(TCPBinding2,"net.tcp://localhost:9001/IInstanceDeactivationContract");
				Client3=new CInstanceDeactivationProxy(TCPBinding3,"net.tcp://localhost:9001/IInstanceDeactivationContract");
				Client4=new CInstanceDeactivationProxy(TCPBinding4,"net.tcp://localhost:9001/IInstanceDeactivationContract");

				Client1.StartSession(10);
				Client2.StartSession(20);
				Client3.StartSession(30);
				Client4.StartSession(40);
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client1.BeforeCall(110);
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client2.AfterCall(120);
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client3.BeforeAndAfterCall(130);
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				// Aj ked sa serverovsky objekt zlikvidoval je proxy nie a je mozne volat na nom dalsie metody.
				Client3.StartSession(999);
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client4.ManualRelease(140);
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				// Aj ked sa serverovsky objekt zlikvidoval je proxy nie a je mozne volat na nom dalsie metody.
				Client4.StartSession(888);
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();
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

				if (Client3!=null && Client3.State!=CommunicationState.Faulted)
				{
					Client3.Close();
					Client3=null;
				}

				if (Client4!=null && Client4.State!=CommunicationState.Faulted)
				{
					Client4.Close();
					Client4=null;
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