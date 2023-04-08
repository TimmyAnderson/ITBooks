using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ContractQueriesClient
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

			CContractQueryHelper		ContractQueryHelper=new CContractQueryHelper();
			TcpTransportBindingElement	TCPBindingElement=new TcpTransportBindingElement();

			// Doporucuje sa zvysit maximalnu velkost prenasanej message aby nedoslo k problemom kedze metadata su dost velke.
			TCPBindingElement.MaxReceivedMessageSize*=5;

			ContractQueryHelper.ReadServiceEndpointCollection("net.tcp://localhost:9001/MEX",TCPBindingElement);

			ContractQueryHelper.WriteServiceEndpointCollectionToConsole();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------