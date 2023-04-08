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
using SharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace Client
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void WindowsTestForUser(string UserName, string Password, Binding B)
		{
			try
			{
				X509Certificate2			Cert=new X509Certificate2("..\\..\\..\\..\\..\\..\\!Certificates\\MyTestCert.pfx");

				// Mozem pouzit DnsEndpointIdentity s menom 'localhost', alebo 'WORK'.
				//using(ChannelFactory<IMSWindowsService> F=new ChannelFactory<IMSWindowsService>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new DnsEndpointIdentity("localhost"),new AddressHeaderCollection())))
				//using(ChannelFactory<IMSWindowsService> F=new ChannelFactory<IMSWindowsService>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new DnsEndpointIdentity("WORK"),new AddressHeaderCollection())))

				// Mozem pouzit aj UpnEndpointIdentity s menom Usera ??? pod ktorym bezi Service.
				using(ChannelFactory<IMSWindowsService> F=new ChannelFactory<IMSWindowsService>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new UpnEndpointIdentity("WORK\\Administrator"),new AddressHeaderCollection())))

				// Identity NEMUSIM VOBEC POUZIT.
				//using(ChannelFactory<IMSWindowsService> F=new ChannelFactory<IMSWindowsService>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"))))
				{
					// !!! Ak chcem mozem zadefinovat CUSTOM Windows Credentials. Ak ich nepouzijem zoberie sa AKTUALNE PRIHLASENY USER.
					//F.Credentials.Windows.ClientCredential.UserName=UserName;
					//F.Credentials.Windows.ClientCredential.Password=Password;

					try
					{
						using(IDisposable Proxy=(F.CreateChannel() as IDisposable))
						{
							string					MethodName="JustForAdministrator";

							try
							{
								IMSWindowsService	SC=(IMSWindowsService) Proxy;

								SC.JustForAdministrator();
								Console.WriteLine(string.Format("User [{0}] was ALLOWED to enter: [{1}] !",UserName,MethodName));
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("3 - User: [{0}], Method: [{1}], EXCEPTION: [{2}] !",UserName,MethodName,E.Message));
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
							string					MethodName="JustForAdministrators";

							try
							{
								IMSWindowsService	SC=(IMSWindowsService) Proxy;

								SC.JustForAdministrators();
								Console.WriteLine(string.Format("User [{0}] was ALLOWED to enter: [{1}] !",UserName,MethodName));
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("3 - User: [{0}], Method: [{1}], EXCEPTION: [{2}] !",UserName,MethodName,E.Message));
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
							string					MethodName="ForAll";

							try
							{
								IMSWindowsService	SC=(IMSWindowsService) Proxy;

								SC.ForAll();
								Console.WriteLine(string.Format("User [{0}] was ALLOWED to enter: [{1}] !",UserName,MethodName));
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("3 - User: [{0}], Method: [{1}], EXCEPTION: [{2}] !",UserName,MethodName,E.Message));
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
		private static void TestAdministrator()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.Windows;

			WindowsTestForUser("Administrator","XXX",B);
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
				TestAdministrator();
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