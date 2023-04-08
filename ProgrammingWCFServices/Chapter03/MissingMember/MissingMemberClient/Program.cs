using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MissingMemberClient
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

			CMissingMemberProxy					Client=null;
			CClientName							ClientNameIn=new CClientName("Jenny","Thompson");
			CClientName							ClientNameOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CMissingMemberProxy(TCPBinding,"net.tcp://localhost:9001/IMissingMemberContract");

				Client.SendName(ClientNameIn);
				Console.WriteLine(String.Format("Client send ClientPerson: {0}",ClientNameIn.ToString()));
				Console.WriteLine();

				ClientNameOut=Client.GetName();
				Console.WriteLine(String.Format("Server returned this name: {0}",ClientNameOut.ToString()));
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