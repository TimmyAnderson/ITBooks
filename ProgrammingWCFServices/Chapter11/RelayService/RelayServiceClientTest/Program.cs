using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using Microsoft.ServiceBus;
using RelayServiceSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace RelayServiceClientTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
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

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------