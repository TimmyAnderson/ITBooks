using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCInterfaceLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCInterfaceManualClient
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

			DCInterfaceManualProxy				Client=null;
			CFullName							FullNameIn1=new CFullName("Jenny","Thompson");
			IName								FullNameIn2=new CFullName("Atreyu","???0");
			IName								NameOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new DCInterfaceManualProxy(TCPBinding,"net.tcp://localhost:9001/IDCInterfaceContract");

				try
				{
					NameOut=Client.GetName();
					Console.WriteLine(String.Format("GetName(): Server returned this name: {0}",NameOut.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					Client.SendName(FullNameIn1);
					Console.WriteLine(String.Format("SendName(FullNameIn1): Client send FullNameIn1: {0}",FullNameIn1.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					Client.SendName(FullNameIn2);
					Console.WriteLine(String.Format("SendName(FullNameIn2): Client send FullNameIn2: {0}",FullNameIn2.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

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