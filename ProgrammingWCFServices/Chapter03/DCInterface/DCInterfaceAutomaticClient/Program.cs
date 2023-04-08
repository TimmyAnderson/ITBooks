using System;
using System.Collections.Generic;
using System.Text;
using DCInterfaceAutomaticClient.CDCInterfaceProxy;
//-------------------------------------------------------------------------------------------------------
namespace DCInterfaceAutomaticClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static string CFullNameToString(CFullName FullName)
		{
			return(string.Format("CFullName - FirstName: {0}, LastName: {1} !",FullName.FirstName, FullName.LastName));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			DCInterfaceContractClient			Client=null;
			CFullName							FullNameIn1=new CFullName();
			object								FullNameIn2=new CFullName();
			CFullName							NameOut=null;

			// V skutocnosti su vsetky properties aj ked na servri je MFirstName ako member premenna.
			FullNameIn1.FirstName="Jenny";
			FullNameIn1.LastName="Thompson";

			((CFullName)FullNameIn2).FirstName="Atreyu";
			((CFullName)FullNameIn2).LastName="???0";

			try
			{
				Client=new DCInterfaceContractClient("NetTcpBinding_IDCInterfaceContract");

				try
				{
					// Akceptuje parameter typu 'object'.
					Client.SendName(FullNameIn1);
					Console.WriteLine(String.Format("Client send FullNameIn1: {0}",CFullNameToString(FullNameIn1)));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Akceptuje parameter typu 'object'.
					Client.SendName(FullNameIn2);
					Console.WriteLine(String.Format("Client send FullNameIn2: {0}",CFullNameToString((CFullName)FullNameIn2)));
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}

				Console.WriteLine();

				try
				{
					// Vracia objekt typu 'object' - treba pretypovat.
					NameOut=(CFullName) Client.GetName();
					Console.WriteLine(String.Format("Server returned this name: {0}",CFullNameToString(NameOut)));
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
				if (Client!=null)
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