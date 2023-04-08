using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.Configuration.Provider;
using System.Security.Cryptography.X509Certificates;
using System.ServiceModel.Description;
using System.ServiceModel.Security;
using System.Web.Security;
using MessageSecurityLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MessageSecurityService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CMessageSecurityService>	Service=new CServiceHostWrapper<CMessageSecurityService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			// Nastavim autentifikaciu na Windows.
			Service.Host.Credentials.UserNameAuthentication.UserNamePasswordValidationMode=UserNamePasswordValidationMode.Windows;

			// Nastavim autorizaciu.
			Service.Host.Authorization.PrincipalPermissionMode=PrincipalPermissionMode.UseWindowsGroups;

			// Nastavim sevice certifikat.
			// !!! Uz musi byt vytvoreny cez makecert.exe.
			Service.Host.Credentials.ServiceCertificate.SetCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestMS");

			Service.AddServiceEndpoint<IMessageSecurityContract>(TCPBinding,"net.tcp://localhost:9001/IMessageSecurityContract");

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