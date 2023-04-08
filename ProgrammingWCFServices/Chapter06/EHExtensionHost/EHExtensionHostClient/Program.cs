using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using EHExtensionHostLibrary;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionHostClient
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

			CEHExtensionHostProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CEHExtensionHostProxy(TCPBinding,"net.tcp://localhost:9001/IEHExtensionHostContract");

				try
				{
					Client.ThrowException();
				}
				catch(FaultException<ObjectDisposedException> E)
				{
					Console.WriteLine(string.Format("FaultException<ObjectDisposedException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				try
				{
					Client.IsAlive();
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
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