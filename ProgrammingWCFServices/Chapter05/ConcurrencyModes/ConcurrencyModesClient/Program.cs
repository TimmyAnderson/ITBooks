using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ConcurrencyModesLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyModesClient
{
//-------------------------------------------------------------------------------------------------------
	public class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static CConcurrencyModesProxy					MClient1=null;
		private static CConcurrencyModesProxy					MClient2=null;
		private static CConcurrencyModesProxy					MClient3=null;
		private static string									MClientName1;
		private static string									MClientName2;
		private static string									MClientName3;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void SlowMethodThread(object Param)
		{
			CThreadData							ThreadData=(CThreadData) Param;

			Console.WriteLine(string.Format("SM THREAD: {0} 1 !",ThreadData.ClientName));

			Thread.Sleep(ThreadData.ClientTimeout);

			try
			{
				ThreadData.Proxy.SlowMethod(ThreadData.Text,ThreadData.ServerTimeout);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("SM THREAD EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine(string.Format("SM THREAD: {0} 2 !",ThreadData.ClientName));
		}
//-------------------------------------------------------------------------------------------------------
		static void CallbackSynchroToJustSenderThread(object Param)
		{
			CThreadData							ThreadData=(CThreadData) Param;

			Console.WriteLine(string.Format("SYNCHRO JUST SENDER THREAD: {0} 1 !",ThreadData.ClientName));

			Thread.Sleep(ThreadData.ClientTimeout);

			try
			{
				ThreadData.Proxy.DoSynchroCallbackToJustSender(ThreadData.Text,ThreadData.ServerTimeout);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("SYNCHRO JUST SENDER THREAD EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine(string.Format("SYNCHRO JUST SENDER THREAD: {0} 2 !",ThreadData.ClientName));
		}
//-------------------------------------------------------------------------------------------------------
		static void CallbackSynchroForAllThread(object Param)
		{
			CThreadData							ThreadData=(CThreadData) Param;

			Console.WriteLine(string.Format("SYNCHRO FOR ALL THREAD: {0} 1 !",ThreadData.ClientName));

			Thread.Sleep(ThreadData.ClientTimeout);

			try
			{
				ThreadData.Proxy.DoSynchroCallbackForAllClients(ThreadData.Text,ThreadData.ServerTimeout);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("SYNCHRO FOR ALL THREAD EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine(string.Format("SYNCHRO FOR ALL THREAD: {0} 2 !",ThreadData.ClientName));
		}
//-------------------------------------------------------------------------------------------------------
		static void CallbackAsynchroThread(object Param)
		{
			CThreadData							ThreadData=(CThreadData) Param;

			Console.WriteLine(string.Format("ASYNCHRO THREAD: {0} STARTED !",ThreadData.ClientName));

			Thread.Sleep(ThreadData.ClientTimeout);

			try
			{
				ThreadData.Proxy.DoAsynchroCallback(ThreadData.Text,ThreadData.ServerTimeout);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("ASYNCHRO THREAD EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine(string.Format("ASYNCHRO THREAD: {0} FINISHED !",ThreadData.ClientName));
		}
//-------------------------------------------------------------------------------------------------------
// Dve volania pomalej metody nad tou istou instanciou.
// 1. Ak je nastaveny Single thread model potom sa volania vykonaju sekvencne. Teda ked sa vykonava jedno volanie tak to z 2. threadu je bloknute.
// 2. Ak je nastaveny Reentrant, alebo Multiple thread model potom sa volania vykonaju paralelne.
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			Thread								T1=new Thread(new ParameterizedThreadStart(Program.SlowMethodThread));
			Thread								T2=new Thread(new ParameterizedThreadStart(Program.SlowMethodThread));
			CThreadData							TD1=new CThreadData(MClientName1+"_IN_1",MClient1,"SLOW METHOD SI 1",1000,10000);
			CThreadData							TD2=new CThreadData(MClientName1+"_IN_2",MClient1,"SLOW METHOD SI 2",1000,10000);

			T1.Start(TD1);
			T2.Start(TD2);

			Console.WriteLine("Press any key to FINISH TEST !");
			Console.ReadLine();
			Console.Clear();
		}
//-------------------------------------------------------------------------------------------------------
// Dve volania pomalej metody nad dvoma rozdielnymi instanciami.
// 1. Bez ohladu na ConcurrencyMode sa volania vykonaju VZDY paralelne, kedze BEZIA NAD 2 INSTANCIAMI PROXY.
// 2. Ak mam SINGLETON potom pri nastaveni ConcurrencyMode an Single/Reentrant znamena, ze iba JEDNA METODA SINGLETON SA MOZE VOLAT PARALELNE. Ake je ConcurrencyMode na Multiple potom sa vykonaju paralelne.
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			Thread								T1=new Thread(new ParameterizedThreadStart(Program.SlowMethodThread));
			Thread								T2=new Thread(new ParameterizedThreadStart(Program.SlowMethodThread));
			CThreadData							TD1=new CThreadData(MClientName1,MClient1,"SLOW METHOD DI 1",1000,10000);
			CThreadData							TD2=new CThreadData(MClientName2,MClient2,"SLOW METHOD DI 2",1000,10000);

			T1.Start(TD1);
			T2.Start(TD2);

			Console.WriteLine("Press any key to FINISH TEST !");
			Console.ReadLine();
			Console.Clear();
		}
//-------------------------------------------------------------------------------------------------------
// Volania synchronneho callback pre sendera synchronne.
// 1. Pri ConcurrencyMode na Single na serveri pri volani Callback dojde k Exception kedze volanie callback by viedlo k deadlock.
// 2. Pri ConcurrencyMode na Reentrant a Multiple prebehne vsetko OK.
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			MClient1.DoSynchroCallbackToJustSender("S-C-S",5*1000);

			Console.WriteLine("Press any key to FINISH TEST !");
			Console.ReadLine();
			Console.Clear();
		}
//-------------------------------------------------------------------------------------------------------
// Volania synchronneho callback pre VSETKYCH KLIENTOV synchronne.
// !!! 1. Pri ConcurrencyMode na Single na serveri dochadza k tomu, ze pri odosielani do Client1 (sender) sa hodi exception s varvanim na deadlock ALE Client2 a Client3 callback bez problemov zachytia.
// 2. Pri ConcurrencyMode na Reentrant a Multiple prebehne vsetko OK a zachytia callback vsetci traja klietni.
// 3. Treba si uvedomit, ze aj ked pouzivam iba Client1 tak Client2 a Client3 ziju a su zaregistrovani na severi.
//-------------------------------------------------------------------------------------------------------
		static void Test4()
		{
			MClient1.DoSynchroCallbackForAllClients("S-C-S",5*1000);

			Console.WriteLine("Press any key to FINISH TEST !");
			Console.ReadLine();
			Console.Clear();
		}
//-------------------------------------------------------------------------------------------------------
// Volania synchronneho callback pre sendera asynchronne.
// 1. Pri ConcurrencyMode na Single na serveri pri volani Callback dojde k Exception kedze volanie callback by viedlo k deadlock.
// 2. Pri ConcurrencyMode na Reentrant a Multiple prebehne vsetko OK.
//-------------------------------------------------------------------------------------------------------
		static void Test5()
		{
			Thread								T=new Thread(new ParameterizedThreadStart(Program.CallbackSynchroToJustSenderThread));
			CThreadData							TD=new CThreadData(MClientName1,MClient1,"S-C-A METHOD",1000,5000);

			T.Start(TD);

			Console.WriteLine("Press any key to FINISH TEST !");
			Console.ReadLine();
			Console.Clear();
		}
//-------------------------------------------------------------------------------------------------------
// Volania asynchronneho callback asynchronne na 3 instanciach.
// 1. Kedze mam 3 instancie tak vsetko bezi paralelne.
// 2. Je pritom uplne jedno aky ConcurrencyMode je zvoleny.
//-------------------------------------------------------------------------------------------------------
		static void Test6()
		{
			Thread								T1=new Thread(new ParameterizedThreadStart(Program.CallbackAsynchroThread));
			Thread								T2=new Thread(new ParameterizedThreadStart(Program.CallbackAsynchroThread));
			Thread								T3=new Thread(new ParameterizedThreadStart(Program.CallbackAsynchroThread));
			CThreadData							TD1=new CThreadData(MClientName1,MClient1,"A-C-A METHOD 1",1000,5000);
			CThreadData							TD2=new CThreadData(MClientName2,MClient2,"A-C-A METHOD 2",1000,5000);
			CThreadData							TD3=new CThreadData(MClientName3,MClient3,"A-C-A METHOD 3",1000,5000);

			T1.Start(TD1);
			T2.Start(TD2);
			T3.Start(TD3);

			Console.WriteLine("Press any key to FINISH TEST !");
			Console.ReadLine();
			Console.Clear();
		}
//-------------------------------------------------------------------------------------------------------
// Volania synchronneho callback pre sendera asynchronne na TEJ ISTEJ instancii.
// 1. Pri ConcurrencyMode na Single vsetky volania zlyhaju kedze mam deadlock.
// 2. Pri ConcurrencyMode na Reentrant a Multiple vsetky volania prejdu a su plne paralene.
// !!!!! 3. Ak by som vsak volal vsetkych klientov potom by neprebehlo iba volanie sendera, teda Client1, ale Client2 a Client3 by zachytili event, kedze tito dvaja klienti existuju a su zaregistrovani.
//-------------------------------------------------------------------------------------------------------
		static void Test7()
		{
			Thread								T1=new Thread(new ParameterizedThreadStart(Program.CallbackSynchroToJustSenderThread));
			Thread								T2=new Thread(new ParameterizedThreadStart(Program.CallbackSynchroToJustSenderThread));
			Thread								T3=new Thread(new ParameterizedThreadStart(Program.CallbackSynchroToJustSenderThread));
			CThreadData							TD1=new CThreadData(MClientName1+"_IN_1",MClient1,"A-C-S METHOD 1 IN 1",1000,5000);
			CThreadData							TD2=new CThreadData(MClientName1+"_IN_2",MClient1,"A-C-S METHOD 1 IN 2",1000,5000);
			CThreadData							TD3=new CThreadData(MClientName1+"_IN_3",MClient1,"A-C-S METHOD 1 IN 3",1000,5000);

			T1.Start(TD1);
			T2.Start(TD2);
			T3.Start(TD3);

			Console.WriteLine("Press any key to FINISH TEST !");
			Console.ReadLine();
			Console.Clear();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Random								RND=new Random();
			int									ID1=RND.Next(100,999);
			int									ID2=RND.Next(100,999);
			int									ID3=RND.Next(100,999);
			CConcurrencyModesCatcher			CallBack1=null;
			CConcurrencyModesCatcher			CallBack2=null;
			CConcurrencyModesCatcher			CallBack3=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();
			NetTcpBinding						TCPBinding3=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;
			TCPBinding3.ReliableSession.Enabled=true;

			MClientName1="C_" + ID1;
			MClientName2="C_" + ID2;
			MClientName3="C_" + ID3;

			try
			{
				CallBack1=new CConcurrencyModesCatcher(MClientName1);
				CallBack2=new CConcurrencyModesCatcher(MClientName2);
				CallBack3=new CConcurrencyModesCatcher(MClientName3);

				MClient1=new CConcurrencyModesProxy(CallBack1,TCPBinding1,"net.tcp://localhost:9001/IConcurrencyModesContract");
				MClient2=new CConcurrencyModesProxy(CallBack2,TCPBinding2,"net.tcp://localhost:9001/IConcurrencyModesContract");
				MClient3=new CConcurrencyModesProxy(CallBack3,TCPBinding3,"net.tcp://localhost:9001/IConcurrencyModesContract");

				MClient1.Connect(MClientName1);
				MClient2.Connect(MClientName2);
				MClient3.Connect(MClientName3);

				//Test1();
				//Test2();
				//Test3();
				Test4();
				//Test5();
				//Test6();
				//Test7();

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				MClient1.Disconnect();
				MClient2.Disconnect();
				MClient3.Disconnect();

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (MClient1!=null && MClient1.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					MClient1.Close();
					Console.WriteLine("AFTER CLOSE !");
					MClient1=null;
				}

				if (MClient2!=null && MClient2.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					MClient2.Close();
					Console.WriteLine("AFTER CLOSE !");
					MClient2=null;
				}

				if (MClient3!=null && MClient3.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					MClient3.Close();
					Console.WriteLine("AFTER CLOSE !");
					MClient3=null;
				}
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------