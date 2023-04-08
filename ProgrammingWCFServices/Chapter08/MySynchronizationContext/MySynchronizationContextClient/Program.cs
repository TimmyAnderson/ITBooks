using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MySynchronizationContextLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MySynchronizationContextClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void ExecutionThread(object Param)
		{
			CPair<CMySynchronizationContextProxy,string>	Pair=(CPair<CMySynchronizationContextProxy,string>) Param;

			Console.WriteLine("ExecutionThread() 1 !");

			Pair.First.ShowText(Pair.Second + "_1");
			Thread.Sleep(2*1000);
			Pair.First.ShowText(Pair.Second + "_2");
			Thread.Sleep(2*1000);
			Pair.First.ShowText(Pair.Second + "_3");

			Console.WriteLine("ExecutionThread() 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Dve proxy - 2 objekty - spracovanie prebieha paralelne.
		static void Test1()
		{
			CMySynchronizationContextProxy		Client1=null;
			CMySynchronizationContextProxy		Client2=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;

			try
			{
				Client1=new CMySynchronizationContextProxy(TCPBinding1,"net.tcp://localhost:9001/IMySynchronizationContextContract");
				Client2=new CMySynchronizationContextProxy(TCPBinding2,"net.tcp://localhost:9001/IMySynchronizationContextContract");

				Thread									T1=new Thread(Program.ExecutionThread);
				Thread									T2=new Thread(Program.ExecutionThread);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client1.Open();
				Client2.Open();

				CPair<CMySynchronizationContextProxy,string>	Pair1=new CPair<CMySynchronizationContextProxy,string>(Client1,"Hi 1 !!!");
				CPair<CMySynchronizationContextProxy,string>	Pair2=new CPair<CMySynchronizationContextProxy,string>(Client1,"Hi 2 !!!");

				T1.Start(Pair1);
				T2.Start(Pair2);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client1!=null && Client1.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client1.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client1=null;
				}

				if (Client2!=null && Client2.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client2.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client2=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Jedno proxy - 1 objekty - spracovanie prebieha sekvencne.
		static void Test2()
		{
			CMySynchronizationContextProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CMySynchronizationContextProxy(TCPBinding,"net.tcp://localhost:9001/IMySynchronizationContextContract");

				Thread										T1=new Thread(Program.ExecutionThread);
				Thread										T2=new Thread(Program.ExecutionThread);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				CPair<CMySynchronizationContextProxy,string>	Pair1=new CPair<CMySynchronizationContextProxy,string>(Client,"Hi 1 !!!");
				CPair<CMySynchronizationContextProxy,string>	Pair2=new CPair<CMySynchronizationContextProxy,string>(Client,"Hi 2 !!!");

				T1.Start(Pair1);
				T2.Start(Pair2);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//Test1();
			Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------