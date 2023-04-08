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
				using(ChannelFactory<IMSWindowsServiceCA> F=new ChannelFactory<IMSWindowsServiceCA>(B,new EndpointAddress(new Uri("net.tcp://localhost:8001/Service"))))
				{
					try
					{
						using(IDisposable Proxy=(F.CreateChannel() as IDisposable))
						{
							string					MethodName="JustForAdministrators";

							try
							{
								IMSWindowsServiceCA	SC=(IMSWindowsServiceCA) Proxy;

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
								IMSWindowsServiceCA	SC=(IMSWindowsServiceCA) Proxy;

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