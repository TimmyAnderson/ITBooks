using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyReentrantLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyReentrantClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void ExecutionThread1(object Param)
		{
			CPair<CConcurrencyReentrantProxy,string>	Pair=(CPair<CConcurrencyReentrantProxy,string>) Param;

			Console.WriteLine(string.Format("ExecutionThread: {0} 1 !",Pair.Second));
			
			Pair.First.SlowMethod(Pair.Second);

			Console.WriteLine(string.Format("ExecutionThread: {0} 2 !",Pair.Second));
		}
//-------------------------------------------------------------------------------------------------------
		private static void ExecutionThread2(object Param)
		{
			CPair<CConcurrencyReentrantProxy,string>	Pair=(CPair<CConcurrencyReentrantProxy,string>) Param;

			Console.WriteLine(string.Format("ExecutionThread: {0} BEGIN !",Pair.Second));
			
			Pair.First.DoSlowCallback(Pair.Second);

			Console.WriteLine(string.Format("ExecutionThread: {0} END !",Pair.Second));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CConcurrencyReentrantProxy			Client=null;
			string								ClientName;

			Random								RND=new Random();
			int									ID=RND.Next(100,999);
			CConcurrencyReentrantCatcher		CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			ClientName="C_" + ID;

			try
			{
				CallBack=new CConcurrencyReentrantCatcher(ClientName);

				Client=new CConcurrencyReentrantProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/IConcurrencyReentrantContract");

				CallBack.ConcurrencyReentrantProxy=Client;

				Client.Connect(ClientName);

				Client.DoCallback(ClientName);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.Disconnect();

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
		// !!!!! Dve proxy - 2 objekty - spracovanie prebieha paralelne.
		static void Test2()
		{
			CConcurrencyReentrantProxy			Client1=null;
			CConcurrencyReentrantProxy			Client2=null;
			string								ClientName1;
			string								ClientName2;

			Random								RND=new Random();
			int									ID1=RND.Next(100,999);
			int									ID2=RND.Next(100,999);
			CConcurrencyReentrantCatcher		CallBack1=null;
			CConcurrencyReentrantCatcher		CallBack2=null;

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
				CallBack1=new CConcurrencyReentrantCatcher(ClientName1);
				CallBack2=new CConcurrencyReentrantCatcher(ClientName2);

				Client1=new CConcurrencyReentrantProxy(CallBack1,TCPBinding1,"net.tcp://localhost:9001/IConcurrencyReentrantContract");
				Client2=new CConcurrencyReentrantProxy(CallBack2,TCPBinding2,"net.tcp://localhost:9001/IConcurrencyReentrantContract");

				CallBack1.ConcurrencyReentrantProxy=Client1;
				CallBack2.ConcurrencyReentrantProxy=Client2;

				// Kym nie je proxy otvorene potom su vsetky volania implicitne synchornizovane bez ohladu na ConcurrencyMode. Takze najprv ich treba otvorit cez Open() alebo volanim nejakej metody servra.
				Client1.Connect(ClientName1);
				Client2.Connect(ClientName2);

				Thread										T1=new Thread(Program.ExecutionThread1);
				Thread										T2=new Thread(Program.ExecutionThread1);
				CPair<CConcurrencyReentrantProxy,string>	P1=new CPair<CConcurrencyReentrantProxy,string>(Client1,ClientName1);
				CPair<CConcurrencyReentrantProxy,string>	P2=new CPair<CConcurrencyReentrantProxy,string>(Client2,ClientName2);

				T1.Start(P1);
				T2.Start(P2);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client1.Disconnect();
				Client2.Disconnect();

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
		// !!!!! Jedno proxy - 1 objekt - spracovanie prebieha sekvencne.
		static void Test3()
		{
			CConcurrencyReentrantProxy			Client=null;
			string								ClientName1="AAA";
			string								ClientName2="BBB";

			Random								RND=new Random();
			CConcurrencyReentrantCatcher		CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				CallBack=new CConcurrencyReentrantCatcher("CATCHER");

				Client=new CConcurrencyReentrantProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/IConcurrencyReentrantContract");

				CallBack.ConcurrencyReentrantProxy=Client;

				// Kym nie je proxy otvorene potom su vsetky volania implicitne synchornizovane bez ohladu na ConcurrencyMode. Takze najprv ich treba otvorit cez Open() alebo volanim nejakej metody servra.
				Client.Connect(ClientName1);

				Thread										T1=new Thread(Program.ExecutionThread1);
				Thread										T2=new Thread(Program.ExecutionThread1);
				CPair<CConcurrencyReentrantProxy,string>	P1=new CPair<CConcurrencyReentrantProxy,string>(Client,ClientName1);
				CPair<CConcurrencyReentrantProxy,string>	P2=new CPair<CConcurrencyReentrantProxy,string>(Client,ClientName2);

				T1.Start(P1);
				T2.Start(P2);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.Disconnect();

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
		// !!!!! Jedno PROXY - 1 objekt - spracovanie prebieha sekvencne, avsak pri volani CALLBACK je LOCK UVOLNENI a 2. VOLANIE do SERVICE OBJEKTU USPEJE.
		static void Test4()
		{
			CConcurrencyReentrantProxy			Client=null;
			string								ClientName1="[CALL 1]";
			string								ClientName2="[CALL 2]";

			Random								RND=new Random();
			CConcurrencyReentrantCatcher		CallBack=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				CallBack=new CConcurrencyReentrantCatcher("CATCHER");

				Client=new CConcurrencyReentrantProxy(CallBack,TCPBinding,"net.tcp://localhost:9001/IConcurrencyReentrantContract");

				CallBack.ConcurrencyReentrantProxy=Client;

				// Kym nie je proxy otvorene potom su vsetky volania implicitne synchornizovane bez ohladu na ConcurrencyMode. Takze najprv ich treba otvorit cez Open() alebo volanim nejakej metody servra.
				Client.Open();

				Thread										T1=new Thread(Program.ExecutionThread2);
				Thread										T2=new Thread(Program.ExecutionThread2);
				CPair<CConcurrencyReentrantProxy,string>	P1=new CPair<CConcurrencyReentrantProxy,string>(Client,ClientName1);
				CPair<CConcurrencyReentrantProxy,string>	P2=new CPair<CConcurrencyReentrantProxy,string>(Client,ClientName2);

				T1.Start(P1);
				T2.Start(P2);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Client.Disconnect();

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