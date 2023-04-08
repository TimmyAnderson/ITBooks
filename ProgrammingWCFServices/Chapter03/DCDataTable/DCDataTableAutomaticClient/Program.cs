using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Data;
using DCDataTableAutomaticClient.CDCDataTableProxy;
//-------------------------------------------------------------------------------------------------------
namespace DCDataTableAutomaticClient
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

			/*
			DCDataTableContractClient			Client=null;
			DataTable							TableIn=CDBHelper.GetDataTable();
			DataTable							TableOut=null;

			try
			{
				Client=new DCDataTableContractClient("NetTcpBinding_IDCDataTableContract");

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
			*/

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------