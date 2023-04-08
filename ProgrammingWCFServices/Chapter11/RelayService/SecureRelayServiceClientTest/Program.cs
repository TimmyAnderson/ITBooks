using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using Microsoft.ServiceBus;
using RelayServiceSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SecureRelayServiceClientTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				ServiceBusEnvironment.SystemConnectivity.Mode=ConnectivityMode.Tcp;

				Console.Write("Your Service Namespace: ");

				string								ServiceNamespace=Console.ReadLine();

				Console.Write("Your Issuer Name: ");

				string								IssuerName=Console.ReadLine();

				Console.Write("Your Issuer Secret: ");

				string								IssuerSecret=Console.ReadLine();

				// Pomocou metody CreateServiceUri() vytvorim SERVICE BUS adresu.
				Uri									Address=ServiceBusEnvironment.CreateServiceUri("sb", ServiceNamespace, "ToUpperService");

				// Vytvorim triedu pre SERVICE BUS CREDENTIALS.
				TransportClientEndpointBehavior		SharedSecretServiceBusCredential=new TransportClientEndpointBehavior();

				// Naplnim SERVICE BUS CREDENTIALS hodnotami.
				SharedSecretServiceBusCredential.CredentialType=TransportClientCredentialType.SharedSecret;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerName=IssuerName;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerSecret=IssuerSecret;

				ChannelFactory<IToUpperContract>	ChannelFactory=new ChannelFactory<IToUpperContract>("RelayEndpoint", new EndpointAddress(Address));

				// Pridam BEHAVIOR obsahujuci SERVICE BUS CREDENTIALS.
				ChannelFactory.Endpoint.Behaviors.Add(SharedSecretServiceBusCredential);

				NetTcpRelayBinding					RelayBinding=(NetTcpRelayBinding) ChannelFactory.Endpoint.Binding;

				// Definujem TRANSPORT SECURITY.
				RelayBinding.Security.Mode=EndToEndSecurityMode.Transport;
				RelayBinding.Security.Transport.ProtectionLevel=ProtectionLevel.EncryptAndSign;

				IToUpperContract					Channel=ChannelFactory.CreateChannel();
				IClientChannel						CC=(IClientChannel) Channel;

				CC.Open();

				string								Ret=Channel.ToUpper("Timmy Anderson");

				Console.WriteLine(string.Format("Service returned: [{0}] !",Ret));

				CC.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			try
			{
				ServiceBusEnvironment.SystemConnectivity.Mode=ConnectivityMode.Tcp;

				Console.Write("Your Service Namespace: ");

				string								ServiceNamespace=Console.ReadLine();

				Console.Write("Your Issuer Name: ");

				string								IssuerName=Console.ReadLine();

				Console.Write("Your Issuer Secret: ");

				string								IssuerSecret=Console.ReadLine();

				// Pomocou metody CreateServiceUri() vytvorim SERVICE BUS adresu.
				Uri									Address=ServiceBusEnvironment.CreateServiceUri("sb", ServiceNamespace, "ToUpperService");

				// Vytvorim triedu pre SERVICE BUS CREDENTIALS.
				TransportClientEndpointBehavior		SharedSecretServiceBusCredential=new TransportClientEndpointBehavior();

				// Naplnim SERVICE BUS CREDENTIALS hodnotami.
				SharedSecretServiceBusCredential.CredentialType=TransportClientCredentialType.SharedSecret;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerName=IssuerName;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerSecret=IssuerSecret;

				ChannelFactory<IToUpperContract>	ChannelFactory=new ChannelFactory<IToUpperContract>("RelayEndpoint", new EndpointAddress(Address));

				// Pridam BEHAVIOR obsahujuci SERVICE BUS CREDENTIALS.
				ChannelFactory.Endpoint.Behaviors.Add(SharedSecretServiceBusCredential);

				NetTcpRelayBinding					RelayBinding=(NetTcpRelayBinding) ChannelFactory.Endpoint.Binding;

				// Definujem MESSAGE SECURITY.
				RelayBinding.Security.Mode=EndToEndSecurityMode.Message;
				// Vyzadujem CREDENTIALS vo forme WINDOWS CREDENTIALS.
				RelayBinding.Security.Message.ClientCredentialType=MessageCredentialType.Windows;

				IToUpperContract					Channel=ChannelFactory.CreateChannel();
				IClientChannel						CC=(IClientChannel) Channel;

				CC.Open();

				string								Ret=Channel.ToUpper("Timmy Anderson");

				Console.WriteLine(string.Format("Service returned: [{0}] !",Ret));

				CC.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			try
			{
				ServiceBusEnvironment.SystemConnectivity.Mode=ConnectivityMode.Tcp;

				Console.Write("Your Service Namespace: ");

				string								ServiceNamespace=Console.ReadLine();

				Console.Write("Your Issuer Name: ");

				string								IssuerName=Console.ReadLine();

				Console.Write("Your Issuer Secret: ");

				string								IssuerSecret=Console.ReadLine();

				// Pomocou metody CreateServiceUri() vytvorim SERVICE BUS adresu.
				Uri									Address=ServiceBusEnvironment.CreateServiceUri("sb", ServiceNamespace, "ToUpperService");

				// Vytvorim triedu pre SERVICE BUS CREDENTIALS.
				TransportClientEndpointBehavior		SharedSecretServiceBusCredential=new TransportClientEndpointBehavior();

				// Naplnim SERVICE BUS CREDENTIALS hodnotami.
				SharedSecretServiceBusCredential.CredentialType=TransportClientCredentialType.SharedSecret;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerName=IssuerName;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerSecret=IssuerSecret;

				ChannelFactory<IToUpperContract>	ChannelFactory=new ChannelFactory<IToUpperContract>("RelayEndpoint", new EndpointAddress(Address));

				// Pridam BEHAVIOR obsahujuci SERVICE BUS CREDENTIALS.
				ChannelFactory.Endpoint.Behaviors.Add(SharedSecretServiceBusCredential);

				NetTcpRelayBinding					RelayBinding=(NetTcpRelayBinding) ChannelFactory.Endpoint.Binding;

				// Definujem MESSAGE SECURITY.
				RelayBinding.Security.Mode=EndToEndSecurityMode.TransportWithMessageCredential;
				// Vyzadujem CREDENTIALS vo forme WINDOWS CREDENTIALS.
				RelayBinding.Security.Message.ClientCredentialType=MessageCredentialType.Windows;
				RelayBinding.Security.Transport.ProtectionLevel=ProtectionLevel.EncryptAndSign;

				IToUpperContract					Channel=ChannelFactory.CreateChannel();
				IClientChannel						CC=(IClientChannel) Channel;

				CC.Open();

				string								Ret=Channel.ToUpper("Timmy Anderson");

				Console.WriteLine(string.Format("Service returned: [{0}] !",Ret));

				CC.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//Test1();
			//Test2();
			Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------