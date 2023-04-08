using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace VersionRoundTripClient
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

			CVersionRoundTripProxy				Client=null;
			CClientName							ClientNameIn=new CClientName("Jenny","Thompson",13);
			CClientName							ClientNameOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CVersionRoundTripProxy(TCPBinding,"net.tcp://localhost:9001/IVersionRoundTripContract");

				Console.WriteLine("DoRoundTripWithoutEDO() test");
				ClientNameOut=Client.DoRoundTripWithoutEDO(ClientNameIn);
				Console.WriteLine(String.Format("Client send: {0}",ClientNameIn.ToString()));
				Console.WriteLine();

				Console.WriteLine(String.Format("Server returned: {0}",ClientNameOut.ToString()));
				Console.WriteLine();


				Console.WriteLine("DoRoundTripWithEDO() test");
				ClientNameOut=Client.DoRoundTripWithEDO(ClientNameIn);
				Console.WriteLine(String.Format("Client send: {0}",ClientNameIn.ToString()));
				Console.WriteLine();

				Console.WriteLine(String.Format("Server returned: {0}",ClientNameOut.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------