using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Security;
using System.Net;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CallbackAuthenticationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CallbackAuthenticationClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			int									ID=new Random().Next(100,999);
			CCallbackAuthenticationProxy		Client=null;
			string								ClientName="C_" + ID;
			ICallbackAuthenticationCallback		CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			// Nastavim security.
			TCPBinding.Security.Mode=SecurityMode.Transport;
			TCPBinding.Security.Transport.ProtectionLevel=ProtectionLevel.EncryptAndSign;
			TCPBinding.Security.Transport.ClientCredentialType=TcpClientCredentialType.Windows;

			try
			{
				CallBack=new CCallbackAuthenticationCatcher();

				Client=new CCallbackAuthenticationProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/ICallbackAuthenticationContract");

				Client.Connect(ClientName);

				NetworkCredential				Credentials=new NetworkCredential();

				// !!! MUSIM NASTAVIT VALIDNE HESLO.
				Client.ClientCredentials.Windows.ClientCredential.UserName="administrator";
				Client.ClientCredentials.Windows.ClientCredential.Password="";

				Client.DoCallback();

				Console.WriteLine("ALL OK !\n");

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.Disconnect();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");

					Client=null;
				}
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------