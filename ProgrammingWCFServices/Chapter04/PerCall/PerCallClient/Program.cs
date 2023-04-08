using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerCallLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerCallClient
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

			CPerCall1Proxy						Client1=null;
			CPerCall2Proxy						Client2=null;
			CState								StateIn1=new CState(100,"Timmy");
			CState								StateIn2=new CState(200,"Jenny");
			CState								StateOut1=null;
			CState								StateOut2=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding1=new NetTcpBinding();
			Binding								TCPBinding2=new NetTcpBinding();

			try
			{
				Client1=new CPerCall1Proxy(TCPBinding1,"net.tcp://localhost:9001/IPerCallContract1");
				Client2=new CPerCall2Proxy(TCPBinding2,"net.tcp://localhost:9001/IPerCallContract2");

				Client1.SetState1(StateIn1);
				Console.WriteLine(String.Format("Client send StateIn1: {0}",StateIn1.ToString()));
				Console.WriteLine();

				Client2.SetState2(StateIn2);
				Console.WriteLine(String.Format("Client send StateIn1: {0}",StateIn2.ToString()));
				Console.WriteLine();

				Client1.PrintActualState1();
				Client2.PrintActualState2();

				StateOut1=Client1.GetState1();
				Console.WriteLine(String.Format("Server returned StateOut1(): {0}",StateOut1.ToString()));
				Console.WriteLine();

				StateOut2=Client2.GetState2();
				Console.WriteLine(String.Format("Server returned StateOut2(): {0}",StateOut2.ToString()));
				Console.WriteLine();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client1!=null && Client1.State!=CommunicationState.Faulted)
				{
					Client1.Close();
					Client1=null;
				}

				if (Client2!=null && Client2.State!=CommunicationState.Faulted)
				{
					Client2.Close();
					Client2=null;
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