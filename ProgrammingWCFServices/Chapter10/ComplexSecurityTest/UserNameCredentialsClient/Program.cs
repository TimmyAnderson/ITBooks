using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Security;
using UserNameCredentialsHost;
//-----------------------------------------------------------------------------
namespace UserNameCredentialsClient
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static void UserNameTestForUser(string UserName, string Password, Binding B)
		{
			try
			{
				using(ChannelFactory<ISecureContract> F=new ChannelFactory<ISecureContract>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"),new DnsEndpointIdentity("MyTestCert"),new AddressHeaderCollection())))
				{
					// !!!!! Service certifikat vsak NENASTAVUJEM. Ten sa ziska AUTOMATICKY pri zacati komunikacie a porovna s ci mu doveruje Client. Ak ano, tak pristup k Service povoli.
					F.Credentials.UserName.UserName=UserName;
					F.Credentials.UserName.Password=Password;

					// !!!!! Musim nastavit V KODE, pretoze BINDING vytvaram v KODE a tym padom sa NEPOUZIVA .CONFIG.
					F.Credentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerTrust;

					try
					{
						using(IDisposable Proxy=(F.CreateChannel() as IDisposable))
						{
							string					MethodName="JustForBoysByAttribute";

							try
							{
								ISecureContract		SC=(ISecureContract) Proxy;

								SC.JustForBoysByAttribute();
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
							string					MethodName="JustForGirlsByAttribute";

							try
							{
								ISecureContract		SC=(ISecureContract) Proxy;

								SC.JustForGirlsByAttribute();
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
							string					MethodName="JustForBoyTimmyByCode";

							try
							{
								ISecureContract		SC=(ISecureContract) Proxy;

								SC.JustForBoyTimmyByCode();
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
							string					MethodName="ForAllAuthentificatedByAttribute";

							try
							{
								ISecureContract		SC=(ISecureContract) Proxy;

								SC.ForAllAuthentificatedByAttribute();
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
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		private static void TestTimmy()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			UserNameTestForUser("Timmy","aaaaaa1+",B);
		}
//-----------------------------------------------------------------------------
		private static void TestAtreyu()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			UserNameTestForUser("Atreyu","aaaaaa2+",B);
		}
//-----------------------------------------------------------------------------
		private static void TestJenny()
		{
			NetTcpBinding			B=new NetTcpBinding(SecurityMode.Message);

			B.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			UserNameTestForUser("Jenny","aaaaaa3+",B);
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
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
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------