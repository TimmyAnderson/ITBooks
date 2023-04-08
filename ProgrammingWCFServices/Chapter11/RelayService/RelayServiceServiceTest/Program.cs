﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using Microsoft.ServiceBus;
using RelayServiceSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace RelayServiceServiceTest
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
				// Sluzi ako BASE ADDRESS.
				Uri									Address=ServiceBusEnvironment.CreateServiceUri("sb", ServiceNamespace, "ToUpperService");

				// MEX rozhranie.
				Uri									MEXAddress=ServiceBusEnvironment.CreateServiceUri("sb", ServiceNamespace, "ToUpperService/MEX");

				// Vytvorim triedu pre SERVICE BUS CREDENTIALS.
				TransportClientEndpointBehavior		SharedSecretServiceBusCredential=new TransportClientEndpointBehavior();

				// Naplnim SERVICE BUS CREDENTIALS hodnotami.
				SharedSecretServiceBusCredential.CredentialType=TransportClientCredentialType.SharedSecret;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerName=IssuerName;
				SharedSecretServiceBusCredential.Credentials.SharedSecret.IssuerSecret=IssuerSecret;

				// BEHAVIOR sluziaci na zverejnie SERVICE v SERVICE BUS REGISTRY.
				IEndpointBehavior					ServiceRegistrySettings=new ServiceRegistrySettings(DiscoveryType.Public);

				ServiceHost							Host=new ServiceHost(typeof(CToUpperService), Address);

				// Ak chcem pridat MEX ENDPOINT, tak ESTE PREDTYM MUSIM pridat ServiceMetadataBehavior, inak AddServiceEndpoint() hodi EXCEPTION.
				ServiceMetadataBehavior				SMB=new ServiceMetadataBehavior();

				Host.Description.Behaviors.Add(SMB);

				// Pridam MEX rozhranie.
				Host.AddServiceEndpoint(typeof(IMetadataExchange),new NetTcpRelayBinding(),MEXAddress);

				foreach (ServiceEndpoint Endpoint in Host.Description.Endpoints)
				{
					// Pridam BEHAVIOR zverejnujuci SERVICE v SERVICE BUS REGISTRY do ENDPOINT BEHAVIORS.
					Endpoint.Behaviors.Add(ServiceRegistrySettings);

					// Pridam BEHAVIOR obsahujuci SERVICE BUS CREDENTIALS.
					Endpoint.Behaviors.Add(SharedSecretServiceBusCredential);
				}
            
				Host.Open();

				Console.WriteLine(string.Format("Service address: [{0}] !",Address));
				Console.WriteLine("Press any key to STOP SERVICE !");
				Console.ReadLine();

				Host.Close();
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
			Console.Title="SERVICE";

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------