using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using KnownTypesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace KnownTypesClient
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

			CKnownTypesProxy					Client=null;
			CName								NameIn=new CName("Jenny");
			CFullName							FullNameIn1=new CFullName("Jenny","Thompson");
			CName								FullNameIn2=new CFullName("Atreyu","???0");
			CName								NameOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CKnownTypesProxy(TCPBinding,"net.tcp://localhost:9001/IKnownTypesContract");

				try
				{
					Client.SendName(NameIn);
					Console.WriteLine(String.Format("Client send NameIn: {0}",NameIn.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Hodi chybu ak nie je oznacenie [KnownType].
					Client.SendName(FullNameIn1);
					Console.WriteLine(String.Format("Client send FullNameIn1: {0}",FullNameIn1.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Hodi chybu ak nie je oznacenie [KnownType].
					Client.SendName(FullNameIn2);
					Console.WriteLine(String.Format("Client send FullNameIn2: {0}",FullNameIn2.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Hodi chybu ak nie je oznacenie [KnownType].
					NameOut=Client.GetName();
					Console.WriteLine(String.Format("Server returned this name: {0}",NameOut.ToString()));
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