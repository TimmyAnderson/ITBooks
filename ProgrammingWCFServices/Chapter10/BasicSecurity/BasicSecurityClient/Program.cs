using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.Net;
using BasicSecurityLibrary;
//-------------------------------------------------------------------------------------------------------
namespace BasicSecurityClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CBasicSecurityProxy					Client=null;

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
				Client=new CBasicSecurityProxy(TCPBinding,"net.tcp://localhost:9001/IBasicSecurityContract");

				// S default Credential.
				Client.SomeOperation();
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
			CBasicSecurityProxy					Client=null;

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
				Client=new CBasicSecurityProxy(TCPBinding,"net.tcp://localhost:9001/IBasicSecurityContract");

				NetworkCredential				Credentials=new NetworkCredential( );

				// Je potrebne NASTAVIT VALIDNY PASSWORD.
				Credentials.UserName="administrator";
				Credentials.Password="";

				Client.ClientCredentials.Windows.ClientCredential=Credentials;

				Client.SomeOperation();
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

			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------