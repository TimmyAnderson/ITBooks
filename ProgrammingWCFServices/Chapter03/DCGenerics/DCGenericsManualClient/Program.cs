using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCGenericsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCGenericsManualClient
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

			CDCGenericsProxy<string>			Client=null;
			int									IntIn=987;
			string								GenericsIn="Timmy Anderson";
			CName								NameIn1=new CName("Timmy","Anderson");
			CName								NameIn2=new CName("Jenny","Thompson");
			CName								NameIn3=new CName("Quazy","XB179");
			CName								NameIn4=new CName("Tina","Ming");

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCGenericsProxy<string>(TCPBinding,"net.tcp://localhost:9001/IDCGenericsContract");

				Client.SendInt(new CGenericClass1<int>(IntIn));
				Console.WriteLine(String.Format("Client send IntIn: [{0}] !",IntIn.ToString()));
				Console.WriteLine();

				Client.SendGenerics(new CGenericClass1<string>(GenericsIn));
				Console.WriteLine(String.Format("Client send GenericsIn: [{0}] !",GenericsIn.ToString()));
				Console.WriteLine();

				Client.SendCName1(new CGenericClass1<CName>(NameIn1));
				Console.WriteLine(String.Format("Client send NameIn1: [{0}] !",NameIn1.ToString()));
				Console.WriteLine();

				Client.SendCName2(new CGenericClass2<CName>(NameIn2));
				Console.WriteLine(String.Format("Client send NameIn2: [{0}] !",NameIn2.ToString()));
				Console.WriteLine();

				Client.SendCName3(new CGenericClass3<CName>(NameIn3));
				Console.WriteLine(String.Format("Client send NameIn3: [{0}] !",NameIn3.ToString()));
				Console.WriteLine();

				Client.SendCName4(new CGenericClass4<CName>(NameIn4));
				Console.WriteLine(String.Format("Client send NameIn4: [{0}] !",NameIn4.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception: [{0}] !",E.Message));
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