using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Data;
using DCDataTableLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCDataTableManualClient
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

			CDCDataTableManualProxy				Client=null;
			DataTable							TableIn=CDBHelper.GetDataTable();
			DataTable							TableOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCDataTableManualProxy(TCPBinding,"net.tcp://localhost:9001/IDCDataTableContract");

				TableOut=Client.GetDataTable();
				Console.WriteLine(String.Format("Server returned:\n{0}",CDBHelper.DataTableToString(TableOut)));
				Console.WriteLine();

				Client.SendDataTable(TableIn);
				Console.WriteLine(String.Format("Client send:\n{0}",CDBHelper.DataTableToString(TableIn)));
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