using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.ServiceModel.Description;
using AuthorizationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AuthorizationService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CAuthorizationService>		Service=new CServiceHostWrapper<CAuthorizationService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim security.
			TCPBinding.Security.Mode=SecurityMode.Transport;
			TCPBinding.Security.Transport.ProtectionLevel=ProtectionLevel.EncryptAndSign;
			TCPBinding.Security.Transport.ClientCredentialType=TcpClientCredentialType.Windows;

			// Nastavim autorizaciu.
			Service.Host.Authorization.PrincipalPermissionMode=PrincipalPermissionMode.UseWindowsGroups;

			Service.AddServiceEndpoint<IAuthorizationContract>(TCPBinding,"net.tcp://localhost:9001/IAuthorizationContract");

			Service.AddTCPMEXEndpoint("net.tcp://localhost:9001/MEX");

			ServiceHostWrapperCollection.StartServices();

			Console.WriteLine("Press any key to STOP services !");
			Console.ReadLine();

			ServiceHostWrapperCollection.StopServices();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------