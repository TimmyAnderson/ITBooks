using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DemarcatingOperationsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DemarcatingOperationsClient
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

			CDemarcatingOperationsProxy			Client1=null;
			CDemarcatingOperationsProxy			Client2=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client1=new CDemarcatingOperationsProxy(TCPBinding,"net.tcp://localhost:9001/IDemarcatingOperationsContract");
				Client2=new CDemarcatingOperationsProxy(TCPBinding,"net.tcp://localhost:9001/IDemarcatingOperationsContract");

				// Hodi vynimku - zacinat musi IsIntializing operaciou.
				//Client1.Inside2();

				Client1.Start1();

				Client1.Inside2();
				Client1.Inside3();
				// Pokracuje v povodnej session.
				Client1.Start1();
				Client1.Inside3();

				// Konci sesion - na servri sa vola Dispose().
				Client1.Terminate1();

				// Hodi vynimku - uz bola zavolana IsTerminating.
				//Client1.Inside2();

				Client2.Start2();
				Client2.Inside1();
				Client2.Inside2();
				Client2.Inside3();
				Client2.Terminate2();
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