using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace OperationOverloadingClient
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

			CAddProxy							AddProxy=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				AddProxy=new CAddProxy(TCPBinding,"net.tcp://localhost:9001/IAddContract");

				Console.WriteLine(String.Format("AddProxy.Add(): {0} !",AddProxy.Add(10,33)));
				Console.WriteLine(String.Format("AddProxy.Add(): {0} !",AddProxy.Add("Hello","World")));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (AddProxy!=null)
				{
					AddProxy.Close();
					AddProxy=null;
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