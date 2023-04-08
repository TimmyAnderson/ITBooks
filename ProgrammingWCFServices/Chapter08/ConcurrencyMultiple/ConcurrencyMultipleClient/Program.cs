using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyMultipleLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyMultipleClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void ExecutionThread(object Param)
		{
			CPair<CConcurrencyMultipleProxy,string>		Pair=(CPair<CConcurrencyMultipleProxy,string>) Param;

			Console.WriteLine(string.Format("ExecutionThread: {0} 1 !",Pair.Second));
			
			Pair.First.SlowMethod(Pair.Second);

			Console.WriteLine(string.Format("ExecutionThread: {0} 2 !",Pair.Second));
		}
//-------------------------------------------------------------------------------------------------------
		static void ExecutionThreadMethodImpl(object Param)
		{
			CPair<CConcurrencyMultipleProxy,string>		Pair=(CPair<CConcurrencyMultipleProxy,string>) Param;

			Console.WriteLine(string.Format("ExecutionThread: {0} 1 !",Pair.Second));
			
			Pair.First.MethodImplTest(Pair.Second);

			Console.WriteLine(string.Format("ExecutionThread: {0} 2 !",Pair.Second));
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Dve proxy - 2 objekty - spracovanie prebieha paralelne.
		static void Test1()
		{
			CConcurrencyMultipleProxy			Client1=null;
			CConcurrencyMultipleProxy			Client2=null;
			string								ClientName1;
			string								ClientName2;

			Random								RND=new Random();
			int									ID1=RND.Next(100,999);
			int									ID2=RND.Next(100,999);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;

			ClientName1="C_" + ID1;
			ClientName2="C_" + ID2;

			try
			{
				Client1=new CConcurrencyMultipleProxy(TCPBinding1,"net.tcp://localhost:9001/IConcurrencyMultipleContract");
				Client2=new CConcurrencyMultipleProxy(TCPBinding2,"net.tcp://localhost:9001/IConcurrencyMultipleContract");

				Thread									T1=new Thread(Program.ExecutionThread);
				Thread									T2=new Thread(Program.ExecutionThread);
				CPair<CConcurrencyMultipleProxy,string>	P1=new CPair<CConcurrencyMultipleProxy,string>(Client1,ClientName1);
				CPair<CConcurrencyMultipleProxy,string>	P2=new CPair<CConcurrencyMultipleProxy,string>(Client2,ClientName2);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client1.Open();
				Client2.Open();

				T1.Start(P1);
				T2.Start(P2);

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
			CConcurrencyMultipleProxy			Client=null;
			string								ClientName1="AAA";
			string								ClientName2="BBB";

			Random								RND=new Random();

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CConcurrencyMultipleProxy(TCPBinding,"net.tcp://localhost:9001/IConcurrencyMultipleContract");

				Thread										T1=new Thread(Program.ExecutionThread);
				Thread										T2=new Thread(Program.ExecutionThread);
				CPair<CConcurrencyMultipleProxy,string>		P1=new CPair<CConcurrencyMultipleProxy,string>(Client,ClientName1);
				CPair<CConcurrencyMultipleProxy,string>		P2=new CPair<CConcurrencyMultipleProxy,string>(Client,ClientName2);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				T1.Start(P1);
				T2.Start(P2);

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
		static void Test3()
		{
			CConcurrencyMultipleProxy			Client1=null;
			CConcurrencyMultipleProxy			Client2=null;
			string								ClientName1;
			string								ClientName2;

			Random								RND=new Random();
			int									ID1=RND.Next(100,999);
			int									ID2=RND.Next(100,999);

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;

			ClientName1="C_" + ID1;
			ClientName2="C_" + ID2;

			try
			{
				Client1=new CConcurrencyMultipleProxy(TCPBinding1,"net.tcp://localhost:9001/IConcurrencyMultipleContract");
				Client2=new CConcurrencyMultipleProxy(TCPBinding2,"net.tcp://localhost:9001/IConcurrencyMultipleContract");

				Thread									T1=new Thread(Program.ExecutionThreadMethodImpl);
				Thread									T2=new Thread(Program.ExecutionThreadMethodImpl);
				CPair<CConcurrencyMultipleProxy,string>	P1=new CPair<CConcurrencyMultipleProxy,string>(Client1,ClientName1);
				CPair<CConcurrencyMultipleProxy,string>	P2=new CPair<CConcurrencyMultipleProxy,string>(Client2,ClientName2);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client1.Open();
				Client2.Open();

				T1.Start(P1);
				T2.Start(P2);

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
		static void Test4()
		{
			CConcurrencyMultipleProxy			Client=null;
			string								ClientName1="AAA";
			string								ClientName2="BBB";

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CConcurrencyMultipleProxy(TCPBinding,"net.tcp://localhost:9001/IConcurrencyMultipleContract");

				Thread										T1=new Thread(Program.ExecutionThreadMethodImpl);
				Thread										T2=new Thread(Program.ExecutionThreadMethodImpl);
				CPair<CConcurrencyMultipleProxy,string>		P1=new CPair<CConcurrencyMultipleProxy,string>(Client,ClientName1);
				CPair<CConcurrencyMultipleProxy,string>		P2=new CPair<CConcurrencyMultipleProxy,string>(Client,ClientName2);

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				T1.Start(P1);
				T2.Start(P2);

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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//Test1();
			//Test2();
			//Test3();
			Test4();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------