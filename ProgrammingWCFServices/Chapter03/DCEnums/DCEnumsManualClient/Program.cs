using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCEnumsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCEnumsManualClient
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

			CDCEnumsProxy						Client=null;
			CName								NameIn1=new CName("Timmy","Anderson",ESex.E_S_MALE,ERace.E_R_HUMAN);
			CName								NameIn2=new CName("Quazy","XB179",ESex.E_S_MALE,ERace.E_R_NON_HUMAN);
			CName								NameIn3=new CName("Tina","Ming",ESex.E_S_FEMALE,ERace.E_R_ROBOT);
			CName								NameOut1=null;
			CName								NameOut2=null;
			//CName								NameOut3=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCEnumsProxy(TCPBinding,"net.tcp://localhost:9001/IDCEnumsContract");

				NameOut1=Client.GetName1();
				Console.WriteLine(String.Format("Server returned GetName1(): {0}",NameOut1.ToString()));
				Console.WriteLine();

				NameOut2=Client.GetName2();
				Console.WriteLine(String.Format("Server returned GetName2(): {0}",NameOut2.ToString()));
				Console.WriteLine();

				// Hodi excpetion, lebo ERace.E_R_ROBOT ne neserializovatelny.

				/*
				NameOut3=Client.GetName3();
				Console.WriteLine(String.Format("Server returned GetName3(): {0}",NameOut3.ToString()));
				Console.WriteLine();
				*/

				Client.SendName(NameIn1);
				Console.WriteLine(String.Format("Client send NameIn1: {0}",NameIn1.ToString()));
				Console.WriteLine();

				Client.SendName(NameIn2);
				Console.WriteLine(String.Format("Client send NameIn2: {0}",NameIn2.ToString()));
				Console.WriteLine();

				// Hodi excpetion, lebo ERace.E_R_ROBOT ne neserializovatelny.

				/*
				Client.SendName(NameIn3);
				Console.WriteLine(String.Format("Client send NameIn3: {0}",NameIn3.ToString()));
				Console.WriteLine();
				*/
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