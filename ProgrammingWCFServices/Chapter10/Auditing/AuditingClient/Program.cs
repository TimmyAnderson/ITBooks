using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.Net;
using System.ServiceModel.Description;
using AuditingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AuditingClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CAuditingProxy						Client=null;

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
				Client=new CAuditingProxy(TCPBinding,"net.tcp://localhost:9001/IAuditingContract");

				NetworkCredential				Credentials=new NetworkCredential( );

				// Musi to byt VALIDNY Windows LOGIN.
				Credentials.UserName="test";
				Credentials.Password="test";

				Client.ClientCredentials.Windows.ClientCredential=Credentials;

				try
				{
					Client.DoAudit1();
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}

				Client.IsAlive();
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
			CAuditingProxy						Client=null;

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
				Client=new CAuditingProxy(TCPBinding,"net.tcp://localhost:9001/IAuditingContract");

				NetworkCredential				Credentials=new NetworkCredential( );

				// Musi to byt VALIDNY Windows LOGIN.
				Credentials.UserName="test";
				Credentials.Password="test";

				Client.ClientCredentials.Windows.ClientCredential=Credentials;

				try
				{
					Client.DoAudit2();
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}

				Client.IsAlive();
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
		private static void Test3()
		{
			CAuditingProxy						Client=null;

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
				Client=new CAuditingProxy(TCPBinding,"net.tcp://localhost:9001/IAuditingContract");

				NetworkCredential				Credentials=new NetworkCredential( );

				// Musi to byt VALIDNY Windows LOGIN.
				Credentials.UserName="test";
				Credentials.Password="test";

				Client.ClientCredentials.Windows.ClientCredential=Credentials;

				try
				{
					Client.DoAudit3();
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}

				Client.IsAlive();
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
		private static void Test4()
		{
			CAuditingProxy						Client=null;

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
				Client=new CAuditingProxy(TCPBinding,"net.tcp://localhost:9001/IAuditingContract");

				NetworkCredential				Credentials=new NetworkCredential( );

				// Neexistujuci login.
				Credentials.UserName="neexistujuci_login";
				Credentials.Password="pitomost";

				Client.ClientCredentials.Windows.ClientCredential=Credentials;

				try
				{
					Client.DoAudit1();
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}

				Client.IsAlive();
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
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test1();
			//Test2();
			//Test3();
			//Test4();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------