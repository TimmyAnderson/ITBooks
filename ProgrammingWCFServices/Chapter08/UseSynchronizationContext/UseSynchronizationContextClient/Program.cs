using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using UseSynchronizationContextLibrary;
//-------------------------------------------------------------------------------------------------------
namespace UseSynchronizationContextClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void ExecutionThreadIncrement(object Param)
		{
			CUseSynchronizationContextProxy		Proxy=(CUseSynchronizationContextProxy) Param;

			Console.WriteLine("ExecutionThreadIncrement() 1 !");

			for (int i=0;i<5;i++)
			{
				Proxy.IncrementLabel();
				Thread.Sleep(3*1000);
			}

			Console.WriteLine("ExecutionThreadIncrement() 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		static void ExecutionThreadDecrement(object Param)
		{
			CUseSynchronizationContextProxy		Proxy=(CUseSynchronizationContextProxy) Param;

			Console.WriteLine("ExecutionThreadDecrement() 1 !");

			Thread.Sleep(1*1000);
			
			for (int i=0;i<5;i++)
			{
				Proxy.DecrementLabel();
				Thread.Sleep(3*1000);
			}

			Console.WriteLine("ExecutionThreadDecrement() 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Dve proxy - 2 objekty - spracovanie prebieha paralelne.
		static void Test1()
		{
			CUseSynchronizationContextProxy		Client1=null;
			CUseSynchronizationContextProxy		Client2=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;

			try
			{
				Client1=new CUseSynchronizationContextProxy(TCPBinding1,"net.tcp://localhost:9001/IUseSynchronizationContextContract");
				Client2=new CUseSynchronizationContextProxy(TCPBinding2,"net.tcp://localhost:9001/IUseSynchronizationContextContract");

				Thread									T1=new Thread(Program.ExecutionThreadIncrement);
				Thread									T2=new Thread(Program.ExecutionThreadDecrement);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client1.Open();
				Client2.Open();

				T1.Start(Client1);
				T2.Start(Client2);

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
			CUseSynchronizationContextProxy		Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CUseSynchronizationContextProxy(TCPBinding,"net.tcp://localhost:9001/IUseSynchronizationContextContract");

				Thread										T1=new Thread(Program.ExecutionThreadIncrement);
				Thread										T2=new Thread(Program.ExecutionThreadDecrement);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				T1.Start(Client);
				T2.Start(Client);

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