using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace RequiredMemberClient
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

			CRequiredMemberProxy				Client=null;
			CClientName							ClientNameIn=new CClientName("Jenny","Thompson");
			CClientName							ClientNameOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CRequiredMemberProxy(TCPBinding,"net.tcp://localhost:9001/IRequiredMemberContract");

				// Prebehne bez problemov, lebo prenasam verizu DC V2 do V1.
				ClientNameOut=Client.GetName();
				Console.WriteLine(String.Format("Server returned this name: {0}",ClientNameOut.ToString()));
				Console.WriteLine();

				// Zlyha to, kedze prenasam verziu DC V1 do V2 a mam aplikovany na [DataMember] Age IsRequired co zmenaa, ze je vyzadovany. Kedze ho verzia V1 neobsahuje skonci to vynimkou.
				Client.SendName(ClientNameIn);
				Console.WriteLine(String.Format("Client send ClientPerson: {0}",ClientNameIn.ToString()));
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