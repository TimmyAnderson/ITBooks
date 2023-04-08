using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCEventsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCEventsClient
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

			CDCEventsProxy						Client=null;
			CName								Name=new CName("Jenny","Thompson",13);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCEventsProxy(TCPBinding,"net.tcp://localhost:9001/IDCEventsContract");

				Client.SendName(Name);
				Console.WriteLine(String.Format("Client send this name: {0}",Name.ToString()));
				Console.WriteLine(String.Format("Server returned this name: {0}",Client.GetName().ToString()));
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