using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.Net;
using System.Configuration.Provider;
using System.Security.Cryptography.X509Certificates;
using System.ServiceModel.Description;
using System.ServiceModel.Security;
using System.Web.Security;
using MessageSecurityLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MessageSecurityClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			CMessageSecurityProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim Message security.
			TCPBinding.Security.Mode=SecurityMode.Message;
			TCPBinding.Security.Message.ClientCredentialType=MessageCredentialType.UserName;

			try
			{
				Client=new CMessageSecurityProxy(TCPBinding,"net.tcp://localhost:9001/IMessageSecurityContract");

				// Nastavim rezim overovania certifikatu.
				Client.ClientCredentials.ServiceCertificate.Authentication.CertificateValidationMode=X509CertificateValidationMode.PeerOrChainTrust;

				// Nastavim service certifikat.
				Client.ClientCredentials.ServiceCertificate.SetDefaultCertificate(StoreLocation.LocalMachine,StoreName.TrustedPeople,X509FindType.FindBySubjectName,"TestMS");

				// Nasatvim credentials.
				Client.ClientCredentials.UserName.UserName="administrator";
				// !!!!! Tu musim nastavit VALIDNY PASSWORD.
				Client.ClientCredentials.UserName.Password="";

				Client.AutoAuthorization();
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------