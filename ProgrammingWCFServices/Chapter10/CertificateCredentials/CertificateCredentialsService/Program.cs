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
using CertificateCredentialsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CertificateCredentialsService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection						ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CCertificateCredentialsService>	Service=new CServiceHostWrapper<CCertificateCredentialsService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.Certificate;

			// Nastavim autentifikaciu certifikatu na PeerTrust.
			Service.Host.Credentials.ClientCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerTrust;

			// Nastavim autentifikaciu na ASP.NET.
			Service.Host.Authorization.PrincipalPermissionMode=PrincipalPermissionMode.UseAspNetRoles;

			// Nastavim sevice certifikat.
			// !!! Uz musi byt vytvoreny cez makecert.exe.
			Service.Host.Credentials.ServiceCertificate.SetCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestCC");

			Service.AddServiceEndpoint<ICertificateCredentialsContract>(TCPBinding,"net.tcp://localhost:9001/ICertificateCredentialsContract");

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