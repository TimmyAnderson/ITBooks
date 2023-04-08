using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using HelloWCFAutoClient.CHelloWCFProxy;
//-------------------------------------------------------------------------------------------------------
namespace HelloWCFAutoClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			HelloWCFContractClient				Client=null;

			try
			{
				Client=new HelloWCFContractClient("BasicHttpBinding_IHelloWCFContract");

				Client.Say("Hi there AUTO WCF");

				Console.WriteLine("Say() CALLED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("EXCEPTION: [{0}] !",E.Message));
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