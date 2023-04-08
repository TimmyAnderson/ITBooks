using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Security;
using WindowsCredentialsHost;
//-------------------------------------------------------------------------------------------------------
namespace WindowsCredentialsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static void WindowsTestForUser(string UserName, string Password, Binding B)
		{
			try
			{
				// 1. Nemusim zadefinovat IDENTITY.
				//using(ChannelFactory<ISecureContract> F=new ChannelFactory<ISecureContract>(B,"net.tcp://localhost:8001/Service"))
				// 2. Mozem zadefinovat UpnIdentity - UserName pod ktorym je spusteny HOST.
				//using(ChannelFactory<ISecureContract> F=new ChannelFactory<ISecureContract>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new UpnEndpointIdentity(string.Format("{0}\\Administrator",Environment.MachineName)),new AddressHeaderCollection())))
				// 3. Mozem definovat DnsIdentity - DNS meno stroja, ktory hostuje Service.
				//using(ChannelFactory<ISecureContract> F=new ChannelFactory<ISecureContract>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new DnsEndpointIdentity("localhost"),new AddressHeaderCollection())))
				using(ChannelFactory<ISecureContract> F=new ChannelFactory<ISecureContract>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new DnsEndpointIdentity(Environment.MachineName),new AddressHeaderCollection())))
				// 4. Mozem definovat SpnEndpointIdentity.
				//using(ChannelFactory<ISecureContract> F=new ChannelFactory<ISecureContract>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new SpnEndpointIdentity(Environment.MachineName),new AddressHeaderCollection())))
				{
					try
					{
						using(IDisposable Proxy=(F.CreateChannel() as IDisposable))
						{
							string					MethodName="JustAdministrators";

							try
							{
								ISecureContract		SC=(ISecureContract) Proxy;

								SC.JustAdministrators();
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
							string					MethodName="JustBoys";

							try
							{
								ISecureContract		SC=(ISecureContract) Proxy;

								SC.JustBoys();
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
								ISecureContract		SC=(ISecureContract) Proxy;

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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void TestWindows()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.Windows;

			// !!! Musi tu byt KOREKTNE HESLO.
			WindowsTestForUser("Administrator","",B);
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
				TestWindows();
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