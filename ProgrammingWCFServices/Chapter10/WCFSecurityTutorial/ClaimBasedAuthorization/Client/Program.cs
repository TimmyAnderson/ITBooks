using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Security;
using Service;
//-------------------------------------------------------------------------------------------------------
namespace Client
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void UserNameTestForUser(string UserName, string Password, Binding B)
		{
			try
			{
				using(ChannelFactory<IMyCustomAuthorizationService> F=new ChannelFactory<IMyCustomAuthorizationService>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new DnsEndpointIdentity("MyTestCert"),new AddressHeaderCollection())))
				{
					F.Credentials.UserName.UserName=UserName;
					F.Credentials.UserName.Password=Password;

					F.Credentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerTrust;

					try
					{
						using(IDisposable Proxy=(F.CreateChannel() as IDisposable))
						{
							string					MethodName="Method1";

							try
							{
								IMyCustomAuthorizationService	SC=(IMyCustomAuthorizationService) Proxy;

								SC.Method1();
								Console.WriteLine(string.Format("User [{0}] was ALLOWED to enter: [{1}] !",UserName,MethodName));
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("3 - User: [{0}], Method: [{1}], EXCEPTION: [{2}], INNER EXCEPTION: [{3}] !",UserName,MethodName,E.Message,(E.InnerException!=null) ? E.InnerException.Message : "NULL"));
							}
						}
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("2 - User: {0}, EXCEPTION: {1} !",UserName,E.Message));
					}

					try
					{
						using(IDisposable Proxy=(F.CreateChannel() as IDisposable))
						{
							string					MethodName="Method2";

							try
							{
								IMyCustomAuthorizationService	SC=(IMyCustomAuthorizationService) Proxy;

								SC.Method2();
								Console.WriteLine(string.Format("User [{0}] was ALLOWED to enter: [{1}] !",UserName,MethodName));
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("3 - User: [{0}], Method: [{1}], EXCEPTION: [{2}], INNER EXCEPTION: [{3}] !",UserName,MethodName,E.Message,(E.InnerException!=null) ? E.InnerException.Message : "NULL"));
							}
						}
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("2 - User: {0}, EXCEPTION: {1} !",UserName,E.Message));
					}

					try
					{
						using(IDisposable Proxy=(F.CreateChannel() as IDisposable))
						{
							string					MethodName="Method3";

							try
							{
								IMyCustomAuthorizationService	SC=(IMyCustomAuthorizationService) Proxy;

								SC.Method3();
								Console.WriteLine(string.Format("User [{0}] was ALLOWED to enter: [{1}] !",UserName,MethodName));
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("3 - User: [{0}], Method: [{1}], EXCEPTION: [{2}], INNER EXCEPTION: [{3}] !",UserName,MethodName,E.Message,(E.InnerException!=null) ? E.InnerException.Message : "NULL"));
							}
						}
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("2 - User: {0}, EXCEPTION: {1} !",UserName,E.Message));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("3 - User: {0}, EXCEPTION: {1} !",UserName,E.Message));
			}
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		private static void TestTimmy()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			UserNameTestForUser("Timmy","XXX",B);
		}
//-----------------------------------------------------------------------------
		private static void TestAtreyu()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			UserNameTestForUser("Atreyu","XXX",B);
		}
//-----------------------------------------------------------------------------
		private static void TestJenny()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			UserNameTestForUser("Jenny","XXX",B);
		}
//-----------------------------------------------------------------------------
		private static void TestBadCredentials()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			// Bad password.
			UserNameTestForUser("Jenny","XXX",B);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			try
			{
				TestTimmy();
				//TestAtreyu();
				//TestJenny();
				//TestBadCredentials();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------