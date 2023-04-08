using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using EHExtensionCallbackLibrary;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionCallbackClient
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

			CEHExtensionCallbackProxy			Client=null;
			CEHExtensionCallbackCatcher			Catcher=new CEHExtensionCallbackCatcher();

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CEHExtensionCallbackProxy(Catcher,TCPBinding,"net.tcp://localhost:9001/IEHExtensionCallbackContract");

				Client.Connect("EHExtension");

				try
				{
					Client.DoCallback("HELLO");
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(CommunicationException E)
				{
					Console.WriteLine(string.Format("CommunicationException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				try
				{
					Client.Disconnect();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Disconnect() - Exception: {0} !",E.Message));
				}

				Console.WriteLine("ALL OK !\n");
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null)
				{
					try
					{
						Client.Close();
						Console.WriteLine(String.Format("Close() OK"));
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

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