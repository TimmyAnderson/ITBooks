using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.IdentityModel.Claims;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.ServiceModel.Description;
using System.ServiceModel.Security;
using System.Web.Security;
using System.IdentityModel.Selectors;
using SQLProviderLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SQLProviderClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CSQLProviderProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			try
			{
				Client=new CSQLProviderProxy(TCPBinding,"net.tcp://localhost:9001/ISQLProviderContract");

				// Nastavim rezim overovania certifikatu.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerOrChainTrust;

				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestSQL");

				// Nastavim credentials.
				Client.ClientCredentials.UserName.UserName="MySQLTest1";
				Client.ClientCredentials.UserName.Password="aaaaaa1+";

				// !!! Nezabudnut nastavit DNS - v konstruktore proxy triedy.

				try
				{
					Client.AutoAuthorization();
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
			CSQLProviderProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			try
			{
				Client=new CSQLProviderProxy(TCPBinding,"net.tcp://localhost:9001/ISQLProviderContract");

				// Nastavim rezim overovania certifikatu.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerOrChainTrust;

				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestSQL");

				// Nastavim credentials - narokom CHYBNE. Nesedi heslo.
				Client.ClientCredentials.UserName.UserName="MySQLTest1";
				Client.ClientCredentials.UserName.Password="dggjhjerh";

				// !!! Nezabudnut nastavit DNS - v konstruktore proxy triedy.

				try
				{
					Client.AutoAuthorization();
				}
				catch(Exception E)
				{
					Console.WriteLine(CDebugHelper.GetExceptionString(E));
				}

				// Opravim heslo.
				// !!! Ale teraz to uz nejde, lebo kanal je otvoreny.
				Client.ClientCredentials.UserName.Password="aaaaaa1+";
				
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
			CSQLProviderProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			try
			{
				Client=new CSQLProviderProxy(TCPBinding,"net.tcp://localhost:9001/ISQLProviderContract");

				// Nastavim rezim overovania certifikatu.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerOrChainTrust;

				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestSQL");

				// Nastavim credentials.
				// User sice existuje ale patri do skupiny MySQLRole2.
				Client.ClientCredentials.UserName.UserName="MySQLTest2";
				Client.ClientCredentials.UserName.Password="aaaaaa2+";

				// !!! Nezabudnut nastavit DNS - v konstruktore proxy triedy.

				try
				{
					Client.AutoAuthorization();
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
			CSQLProviderProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			try
			{
				Client=new CSQLProviderProxy(TCPBinding,"net.tcp://localhost:9001/ISQLProviderContract");

				// Nastavim rezim overovania certifikatu.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerOrChainTrust;

				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestSQL");

				// Nastavim credentials.
				Client.ClientCredentials.UserName.UserName="MySQLTest1";
				Client.ClientCredentials.UserName.Password="aaaaaa1+";

				// !!! Nezabudnut nastavit DNS - v konstruktore proxy triedy.

				try
				{
					Client.ManualAuthorization();
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
		private static void Test5()
		{
			CSQLProviderProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			try
			{
				Client=new CSQLProviderProxy(TCPBinding,"net.tcp://localhost:9001/ISQLProviderContract");

				// Nastavim rezim overovania certifikatu.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerOrChainTrust;

				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestSQL");

				// Nastavim credentials.
				// User sice existuje ale patri do skupiny MySQLRole2.
				Client.ClientCredentials.UserName.UserName="MySQLTest2";
				Client.ClientCredentials.UserName.Password="aaaaaa2+";

				// !!! Nezabudnut nastavit DNS - v konstruktore proxy triedy.

				try
				{
					Client.ManualAuthorization();
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

			//Test1();
			//Test2();
			//Test3();
			//Test4();
			Test5();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------