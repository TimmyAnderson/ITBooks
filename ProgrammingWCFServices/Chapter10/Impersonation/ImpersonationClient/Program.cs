using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.Security.Principal;
using System.Net;
using ImpersonationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ImpersonationClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CImpersonationProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim security.
			TCPBinding.Security.Mode=SecurityMode.Transport;
			TCPBinding.Security.Transport.ProtectionLevel=ProtectionLevel.EncryptAndSign;
			TCPBinding.Security.Transport.ClientCredentialType=TcpClientCredentialType.Windows;

			try
			{
				Client=new CImpersonationProxy(TCPBinding,"net.tcp://localhost:9001/IImpersonationContract");

				NetworkCredential				Credentials=new NetworkCredential( );

				// !!! Musi byt vytvoreny ucet 'test' s passwordom: 'test' a zaradeny v skupine Administrators.
				Credentials.UserName="test";
				Credentials.Password="test";

				Client.ClientCredentials.Windows.ClientCredential=Credentials;

				Client.AutomaticImpersonation();

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.ManualImpersonation();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CImpersonationProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim security.
			TCPBinding.Security.Mode=SecurityMode.Transport;
			TCPBinding.Security.Transport.ProtectionLevel=ProtectionLevel.EncryptAndSign;
			TCPBinding.Security.Transport.ClientCredentialType=TcpClientCredentialType.Windows;

			try
			{
				Client=new CImpersonationProxy(TCPBinding,"net.tcp://localhost:9001/IImpersonationContract");

				NetworkCredential				Credentials=new NetworkCredential( );

				// !!! Musi byt vytvoreny ucet 'test' s passwordom: 'test' a zaradeny v skupine Administrators.
				Credentials.UserName="test";
				Credentials.Password="test";

				Client.ClientCredentials.Windows.ClientCredential=Credentials;

				// Zakazem impersonation.
				Client.ClientCredentials.Windows.AllowedImpersonationLevel=TokenImpersonationLevel.Identification;

				Client.AutomaticImpersonation();

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.ManualImpersonation();
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					try
					{
						Client.Close();
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test1();
			//Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------