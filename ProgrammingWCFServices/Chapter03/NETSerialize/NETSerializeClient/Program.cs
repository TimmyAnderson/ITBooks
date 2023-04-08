using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using NETSerializeLibrary;
//-------------------------------------------------------------------------------------------------------
namespace NETSerializeClient
{
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CNETSerializeProxy					NETSerializeProxy=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				NETSerializeProxy=new CNETSerializeProxy(TCPBinding,"net.tcp://localhost:9001/INETSerializeContract");

				NETSerializeProxy.PrintSimpleName(new CSimpleName("Jenny","Unknown"));
				Console.WriteLine(String.Format("NETSerializeProxy.GetSimpleName(): {0} !",NETSerializeProxy.GetSimpleName().ToString()));
				NETSerializeProxy.PrintNameWithAddress(new CNameWithAddress("Jenny","Unknown","Main street",862,"1-B"));
				Console.WriteLine(String.Format("NETSerializeProxy.GetNameWithAddress(): {0} !",NETSerializeProxy.GetNameWithAddress().ToString()));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (NETSerializeProxy!=null)
				{
					NETSerializeProxy.Close();
					NETSerializeProxy=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------------------------------