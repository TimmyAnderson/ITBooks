using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCHierarchyLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCHierarchyClient
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

			CDCHierarchyProxy					Client=null;
			CFullName							FullName=new CFullName("Jenny","Thompson");
			CName								Name=new CFullName("Atreuy","Unknown");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCHierarchyProxy(TCPBinding,"net.tcp://localhost:9001/IDCHierarchyContract");

				Client.SendFullName(FullName);
				Console.WriteLine(String.Format("Client send this name: {0}",FullName.ToString()));
				Console.WriteLine(String.Format("Server returned this name: {0}",Client.GetName().ToString()));
				Console.WriteLine();

				try
				{
					// !!! Bez [KnownType] hodi exception.
					Client.SendName(Name);
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}
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