using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ServiceKnownTypesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ServiceKnownTypesClient
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

			CServiceKnownTypesProxy				Client=null;
			CName								NameIn=new CName("Jenny");
			CFullName							FullNameIn1=new CFullName("Jenny","Thompson");
			CName								FullNameIn2=new CFullName("Atreyu","???0");
			CName								NameOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CServiceKnownTypesProxy(TCPBinding,"net.tcp://localhost:9001/IServiceKnownTypesContract");

				try
				{
					// Hodi chybu ak nie je oznacenie [ServiceKnownType].
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
					// Hodi chybu ak nie je oznacenie [ServiceKnownType].
					Client.SendAllNameTypes(FullNameIn1);
					Console.WriteLine(String.Format("SendAllNameTypes(FullNameIn1): Client send FullNameIn1: {0}",FullNameIn1.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Hodi chybu ak nie je oznacenie [ServiceKnownType].
					Client.SendAllNameTypes(FullNameIn2);
					Console.WriteLine(String.Format("SendAllNameTypes(FullNameIn2): Client send FullNameIn2: {0}",FullNameIn2.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Prejde kedze CName je v parameter SendJustName().
					Client.SendJustName(NameIn);
					Console.WriteLine(String.Format("SendJustName(NameIn): Client send FullNameIn1: {0}",NameIn.ToString()));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Hdoi vynimku, lena na SendJustName() nebol apklikovany atribut [ServiceKnownType].
					Client.SendJustName(FullNameIn1);
					Console.WriteLine(String.Format("SendJustName(FullNameIn1): Client send FullNameIn2: {0}",FullNameIn1.ToString()));
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