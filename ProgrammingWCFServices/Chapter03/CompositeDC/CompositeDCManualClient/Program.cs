using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CompositeDCLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CompositeDCManualClient
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

			CCompositeDCProxy					Client=null;
			CName								Jenny=new CName("Jenny","Thompson");
			CName								Atreyu=new CName("Atreyu","No Name");
			CName								Timmy=new CName("Timmy","Anderson");
			CName[]								Friends=new CName[2]{Atreyu,Timmy};
			CFriend								Friend=new CFriend(Jenny,Friends);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CCompositeDCProxy(TCPBinding,"net.tcp://localhost:9001/ICompositeDCContract");

				Client.SendFriend(Friend);
				Console.WriteLine(String.Format("Client send this friendship: {0}",Friend.ToString()));
				Console.WriteLine(String.Format("Server returned this friendship: {0}",Client.GetFriend().ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null)
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