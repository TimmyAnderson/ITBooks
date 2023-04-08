using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			CDCEquivalenceProxy					Client=null;
			CClientPerson						ClientPersonIn=new CClientPerson("Jenny","Thompson",13);
			CClientPerson						ClientPersonOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCEquivalenceProxy(TCPBinding,"net.tcp://localhost:9001/IDCEquivalenceContract");

				Client.SendPerson(ClientPersonIn);
				Console.WriteLine(String.Format("Client send ClientPerson: {0}",ClientPersonIn.ToString()));
				Console.WriteLine();

				ClientPersonOut=Client.GetPerson();
				Console.WriteLine(String.Format("Server returned this name: {0}",ClientPersonOut.ToString()));
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
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			CDCEquivalenceProxy					Client=null;
			CClientErrorPerson					ClientPersonIn=new CClientErrorPerson("Jenny","Thompson",13);
			CClientErrorPerson					ClientPersonOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCEquivalenceProxy(TCPBinding,"net.tcp://localhost:9001/IDCEquivalenceContract");

				// !!! Nehodi chybu, ale sposobi CHYBNU SERIALIZACIU.
				Client.SendErrorPerson(ClientPersonIn);
				Console.WriteLine(String.Format("Client send ClientPerson: {0}",ClientPersonIn.ToString()));
				Console.WriteLine();

				// !!! Nehodi chybu, ale sposobi CHYBNU DESERIALIZACIU.
				ClientPersonOut=Client.GetErrorPerson();
				Console.WriteLine(String.Format("Server returned this name: {0}",ClientPersonOut.ToString()));
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
			Test2();

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------