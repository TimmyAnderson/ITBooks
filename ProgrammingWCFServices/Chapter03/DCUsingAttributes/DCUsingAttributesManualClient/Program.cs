using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCUsingAttributesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCUsingAttributesManualClient
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

			CDCUsingAttributesProxy				Client=null;
			CNameDC								NameDC=new CNameDC("Jenny","Secret",13);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CDCUsingAttributesProxy(TCPBinding,"net.tcp://localhost:9001/IDCUsingAttributesContract");

				Client.ThisIsMyName(NameDC);
				Console.WriteLine(String.Format("Client send its name: {0} !",NameDC.ToString()));
				Console.WriteLine(String.Format("Server returns name: {0} !",Client.SayYourName().ToString()));
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