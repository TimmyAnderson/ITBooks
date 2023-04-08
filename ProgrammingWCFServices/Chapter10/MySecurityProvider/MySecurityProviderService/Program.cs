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
using System.IdentityModel.Selectors;
using MySecurityProviderLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MySecurityProviderService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void CreateUser()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			try
			{
				MembershipCreateStatus	CMS;

				// Vytvorenie usera.
				Membership.Provider.CreateUser("MySQLTest1","aaaaaa1+","someemail1@xxx.sk","Some question !","Some answer !",true,null,out CMS);

				Console.WriteLine(string.Format("User: {0} !",CMS.ToString()));

				// Vytvorenie usera.
				Membership.Provider.CreateUser("MySQLTest2","aaaaaa2+","someemail2@xxx.sk","Some question !","Some answer !",true,null,out CMS);

				Console.WriteLine(string.Format("User: {0} !",CMS.ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void CreateRole()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			try
			{
				// Vytvorenie roly.
				Roles.Provider.CreateRole("MySQLRole1");

				// Pridanie usera do roly.
				Roles.Provider.AddUsersToRoles(new string[]{"MySQLTest1"},new string[]{"MySQLRole1"});

				// Vytvorenie roly.
				Roles.Provider.CreateRole("MySQLRole2");

				// Pridanie usera do roly.
				Roles.Provider.AddUsersToRoles(new string[]{"MySQLTest2"},new string[]{"MySQLRole2"});
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void DeleteUser()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			try
			{
				// Zmazanie usera.
				if (Membership.Provider.DeleteUser("MySQLTest1",true)==true)
					Console.WriteLine("User DELETED !");
				else
					Console.WriteLine("User NOT DELETED - ERROR !");

				// Zmazanie usera.
				if (Membership.Provider.DeleteUser("MySQLTest2",true)==true)
					Console.WriteLine("User DELETED !");
				else
					Console.WriteLine("User NOT DELETED - ERROR !");
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void DeleteRole()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			try
			{
				// Zmazanie roly.
				if (Roles.Provider.DeleteRole("MySQLRole1",false)==true)
					Console.WriteLine("Role DELETED !");
				else
					Console.WriteLine("Role NOT DELETED - ERROR !");

				// Zmazanie roly.
				if (Roles.Provider.DeleteRole("MySQLRole2",false)==true)
					Console.WriteLine("Role DELETED !");
				else
					Console.WriteLine("Role NOT DELETED - ERROR !");
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVER";

			CServiceHostWrapperCollection					ServiceHostWrapperCollection=new CServiceHostWrapperCollection();
			CServiceHostWrapper<CMySecurityProviderService>	Service=new CServiceHostWrapper<CMySecurityProviderService>();

			ServiceHostWrapperCollection.AddServiceHostWrapper(Service);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding									TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			// Nastavim autentifikaciu na Membership provider.
			Service.Host.Credentials.UserNameAuthentication.UserNamePasswordValidationMode=UserNamePasswordValidationMode.MembershipProvider;

			// Nastavim autentifikaciu na ASP.NET.
			Service.Host.Authorization.PrincipalPermissionMode=PrincipalPermissionMode.UseAspNetRoles;

			// Nastavim sevice certifikat.
			// !!! Uz musi byt vytvoreny cez makecert.exe.
			Service.Host.Credentials.ServiceCertificate.SetCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestMYProvider");

			Service.AddServiceEndpoint<IMySecurityProviderContract>(TCPBinding,"net.tcp://localhost:9001/IMySecurityProviderContract");

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