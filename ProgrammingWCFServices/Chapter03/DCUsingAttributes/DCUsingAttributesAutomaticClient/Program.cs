using System;
using System.Collections.Generic;
using System.Text;
using  DCUsingAttributesAutomaticClient.CDCUsingAttributesProxy;
//-------------------------------------------------------------------------------------------------------
namespace DCUsingAttributesAutomaticClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static string CNameDCToString(CNameDC NameDC)
		{
			return(string.Format("CNameDC - FirstName: {0}, LastName: {1}, Age: {2} !",NameDC.MFirstName, NameDC.LastName, NameDC.Age));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			DCUsingAttributesContractClient		Client=null;
			CNameDC								NameDC=new CNameDC();

			// V skutocnosti su vsetky properties aj ked na servri je MFirstName ako member premenna.
			NameDC.MFirstName="Jenny";
			NameDC.LastName="Secret";
			NameDC.Age=13;

			try
			{
				Client=new DCUsingAttributesContractClient("NetTcpBinding_IDCUsingAttributesContract");

				Client.ThisIsMyName(NameDC);
				Console.WriteLine(String.Format("Client send its name: {0} !",CNameDCToString(NameDC)));
				Console.WriteLine(String.Format("Server returns name: {0} !",CNameDCToString(Client.SayYourName())));
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