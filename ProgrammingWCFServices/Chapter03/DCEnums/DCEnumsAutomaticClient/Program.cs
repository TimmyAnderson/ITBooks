using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCEnumsAutomaticClient.CDCEnumsProxy;
//-------------------------------------------------------------------------------------------------------
// Vygenerovane proxy obsahuje enums vratane premenovania members.
//-------------------------------------------------------------------------------------------------------
namespace DCEnumsAutomaticClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static string CFullNameToString(CName Name)
		{
			return(string.Format("CName - FirstName: {0}, LastName: {1}, Sex: {2}, Race: {3} !",Name.FirstName, Name.LastName, Name.Sex, Name.Race));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			DCEnumsContractClient				Client=null;
			CName								NameIn1=new CName();
			CName								NameIn2=new CName();
			CName								NameOut1=null;
			CName								NameOut2=null;
			//CName								NameOut3=null;

			// V skutocnosti su vsetky properties aj ked na servri je MFirstName ako member premenna.
			NameIn1.FirstName="Timmy";
			NameIn1.LastName="Anderson";
			NameIn1.Sex=ESex.E_S_MALE;
			NameIn1.Race=ERace.E_R_HUMAN;

			NameIn2.FirstName="Quazy";
			NameIn2.LastName="XB179";
			NameIn2.Sex=ESex.E_S_MALE;
			// Pouziva sa premenovany clen enum.
			NameIn2.Race=ERace.E_R_ALIEN;

			try
			{
				Client=new DCEnumsContractClient("NetTcpBinding_IDCEnumsContract");

				NameOut1=Client.GetName1();
				Console.WriteLine(String.Format("Server returned GetName1(): {0}",CFullNameToString(NameOut1)));
				Console.WriteLine();

				NameOut2=Client.GetName2();
				Console.WriteLine(String.Format("Server returned GetName2(): {0}",CFullNameToString(NameOut2)));
				Console.WriteLine();

				// Hodi excpetion, lebo ERace.E_R_ROBOT ne neserializovatelny.

				/*
				NameOut3=Client.GetName3();
				Console.WriteLine(String.Format("Server returned GetName3(): {0}",CFullNameToString(NameOut3)));
				Console.WriteLine();
				*/

				Client.SendName(NameIn1);
				Console.WriteLine(String.Format("Client send NameIn1: {0}",CFullNameToString(NameIn1)));
				Console.WriteLine();

				Client.SendName(NameIn2);
				Console.WriteLine(String.Format("Client send NameIn2: {0}",CFullNameToString(NameIn2)));
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