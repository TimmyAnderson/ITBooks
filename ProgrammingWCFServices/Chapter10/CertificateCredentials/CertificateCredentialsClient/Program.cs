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
using CertificateCredentialsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CertificateCredentialsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CCertificateCredentialsProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.Certificate;

			try
			{
				Client=new CCertificateCredentialsProxy(TCPBinding,"net.tcp://localhost:9001/ICertificateCredentialsContract");

				// Nastavim rezim overovania certifikatu SERVICE.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerTrust;
				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestCC");

				// Nastavim klientsky certifikat.
				Client.ClientCredentials.ClientCertificate.SetCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"Client1CC");

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
			CCertificateCredentialsProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.Certificate;

			try
			{
				Client=new CCertificateCredentialsProxy(TCPBinding,"net.tcp://localhost:9001/ICertificateCredentialsContract");

				// Nastavim rezim overovania certifikatu SERVICE.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerTrust;
				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestCC");

				// Nastavim klientsky certifikat.
				Client.ClientCredentials.ClientCertificate.SetCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"Client2CC");

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
		private static void Test3()
		{
			CCertificateCredentialsProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.Certificate;

			try
			{
				Client=new CCertificateCredentialsProxy(TCPBinding,"net.tcp://localhost:9001/ICertificateCredentialsContract");

				// Nastavim rezim overovania certifikatu SERVICE.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerTrust;
				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestCC");

				// Nastavim klientsky certifikat.
				Client.ClientCredentials.ClientCertificate.SetCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"Client1CC");

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
		private static void Test4()
		{
			CCertificateCredentialsProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.Certificate;

			try
			{
				Client=new CCertificateCredentialsProxy(TCPBinding,"net.tcp://localhost:9001/ICertificateCredentialsContract");

				// Nastavim rezim overovania certifikatu SERVICE.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerTrust;
				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestCC");

				// Nastavim klientsky certifikat.
				Client.ClientCredentials.ClientCertificate.SetCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"Client2CC");

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
			Test4();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------