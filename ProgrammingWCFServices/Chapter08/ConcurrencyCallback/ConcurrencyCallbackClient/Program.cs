using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyCallbackClient
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

			// !!! Na testovanie je treba menit hodnotu ConcurrencyMode v CConcurrencyCallbackCatcher.

			int									ID=new Random().Next(100,999);
			CConcurrencyCallbackProxy			Client=null;
			string								ClientName="C_" + ID;
			IConcurrencyCallbackCallback		CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				CallBack=new CConcurrencyCallbackCatcher();

				Client=new CConcurrencyCallbackProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/IConcurrencyCallbackContract");

				Client.Connect(ClientName);

				Client.CallCallbackWithoutWait("HELLO CALLBACK WITHOUT WAIT " + ID);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.CallCallbackWithWait("HELLO CALLBACK WITH WAIT " + ID);

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