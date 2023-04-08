using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ThrottlingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace ThrottlingClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void CallTestThread(object Temp)
		{
			CPair<CThrottlingProxy,int>		Pair=(CPair<CThrottlingProxy,int>) Temp;

			Pair.First.SlowMethod(Pair.Second);
			Console.WriteLine(string.Format("SlowMethod({0}) finished !",Pair.Second));
		}
//-------------------------------------------------------------------------------------------------------
		static void SessionTest()
		{
			CThrottlingProxy					Client1=null;
			CThrottlingProxy					Client2=null;
			CThrottlingProxy					Client3=null;
			CThrottlingProxy					Client4=null;
			CThrottlingProxy					Client5=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();
			NetTcpBinding						TCPBinding3=new NetTcpBinding();
			NetTcpBinding						TCPBinding4=new NetTcpBinding();
			NetTcpBinding						TCPBinding5=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;
			TCPBinding3.ReliableSession.Enabled=true;
			TCPBinding4.ReliableSession.Enabled=true;
			TCPBinding5.ReliableSession.Enabled=true;

			try
			{
				Client1=new CThrottlingProxy(TCPBinding1,"net.tcp://localhost:9001/IThrottlingContract");
				Client2=new CThrottlingProxy(TCPBinding2,"net.tcp://localhost:9001/IThrottlingContract");
				Client3=new CThrottlingProxy(TCPBinding3,"net.tcp://localhost:9001/IThrottlingContract");
				Client4=new CThrottlingProxy(TCPBinding4,"net.tcp://localhost:9001/IThrottlingContract");
				Client5=new CThrottlingProxy(TCPBinding5,"net.tcp://localhost:9001/IThrottlingContract");

				// Na serveri musia byt takto nastavene parametre.
				// MaxConcurrentCalls=2.
				// MaxConcurrentSessions=4.
				// MaxConcurrentInstances=6.

				Client1.StartInstance();
				Client2.StartInstance();
				Client3.StartInstance();
				Client4.StartInstance();

				// Toto volanie uz nezbehne, pretoze je pokus o vytvrenie 5 session.
				Client5.StartInstance();
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

				if (Client3!=null && Client3.State!=CommunicationState.Faulted)
				{
					Client3.Close();
					Client3=null;
				}

				if (Client4!=null && Client4.State!=CommunicationState.Faulted)
				{
					Client4.Close();
					Client4=null;
				}

				if (Client5!=null && (Client5.State==CommunicationState.Opened || Client5.State==CommunicationState.Opening))
				{
					Client5.Close();
					Client5=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void InstanceTest()
		{
			CThrottlingProxy					Client1=null;
			CThrottlingProxy					Client2=null;
			CThrottlingProxy					Client3=null;
			CThrottlingProxy					Client4=null;
			CThrottlingProxy					Client5=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();
			NetTcpBinding						TCPBinding3=new NetTcpBinding();
			NetTcpBinding						TCPBinding4=new NetTcpBinding();
			NetTcpBinding						TCPBinding5=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;
			TCPBinding3.ReliableSession.Enabled=true;
			TCPBinding4.ReliableSession.Enabled=true;
			TCPBinding5.ReliableSession.Enabled=true;

			try
			{
				Client1=new CThrottlingProxy(TCPBinding1,"net.tcp://localhost:9001/IThrottlingContract");
				Client2=new CThrottlingProxy(TCPBinding2,"net.tcp://localhost:9001/IThrottlingContract");
				Client3=new CThrottlingProxy(TCPBinding3,"net.tcp://localhost:9001/IThrottlingContract");
				Client4=new CThrottlingProxy(TCPBinding4,"net.tcp://localhost:9001/IThrottlingContract");
				Client5=new CThrottlingProxy(TCPBinding5,"net.tcp://localhost:9001/IThrottlingContract");

				// Na serveri musia byt takto nastavene parametre.
				// MaxConcurrentCalls=2.
				// MaxConcurrentSessions=6.
				// MaxConcurrentInstances=3.

				Client1.StartInstance();
				Client2.StartInstance();
				Client3.StartInstance();

				Client2.DropInstance();
				Client3.DropInstance();

				if (Client2!=null && Client2.State!=CommunicationState.Faulted)
				{
					Client2.Close();
					Client2=null;
				}

				if (Client3!=null && Client3.State!=CommunicationState.Faulted)
				{
					Client3.Close();
					Client3=null;
				}

				// Toto uz nezbehne ked mam otvorene 3 session - preto som najprv musel zatvorit 2 cez DropInstance() a na Proxy dam Close().
				Client4.StartInstance();
				Client5.StartInstance();
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

				if (Client3!=null && Client3.State!=CommunicationState.Faulted)
				{
					Client3.Close();
					Client3=null;
				}

				if (Client4!=null && Client4.State!=CommunicationState.Faulted)
				{
					Client4.Close();
					Client4=null;
				}

				if (Client5!=null && (Client5.State==CommunicationState.Opened || Client5.State==CommunicationState.Opening))
				{
					Client5.Close();
					Client5=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void CallTest()
		{
			CThrottlingProxy					Client1=null;
			CThrottlingProxy					Client2=null;
			CThrottlingProxy					Client3=null;
			CThrottlingProxy					Client4=null;

			Thread								T1=new Thread(new ParameterizedThreadStart(Program.CallTestThread));
			Thread								T2=new Thread(new ParameterizedThreadStart(Program.CallTestThread));
			Thread								T3=new Thread(new ParameterizedThreadStart(Program.CallTestThread));
			Thread								T4=new Thread(new ParameterizedThreadStart(Program.CallTestThread));

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding1=new NetTcpBinding();
			NetTcpBinding						TCPBinding2=new NetTcpBinding();
			NetTcpBinding						TCPBinding3=new NetTcpBinding();
			NetTcpBinding						TCPBinding4=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding1.ReliableSession.Enabled=true;
			TCPBinding2.ReliableSession.Enabled=true;
			TCPBinding3.ReliableSession.Enabled=true;
			TCPBinding4.ReliableSession.Enabled=true;

			try
			{
				Client1=new CThrottlingProxy(TCPBinding1,"net.tcp://localhost:9001/IThrottlingContract");
				Client2=new CThrottlingProxy(TCPBinding2,"net.tcp://localhost:9001/IThrottlingContract");
				Client3=new CThrottlingProxy(TCPBinding3,"net.tcp://localhost:9001/IThrottlingContract");
				Client4=new CThrottlingProxy(TCPBinding4,"net.tcp://localhost:9001/IThrottlingContract");

				CPair<CThrottlingProxy,int>			P1=new CPair<CThrottlingProxy,int>(Client1,10*1000);
				CPair<CThrottlingProxy,int>			P2=new CPair<CThrottlingProxy,int>(Client2,20*1000);
				CPair<CThrottlingProxy,int>			P3=new CPair<CThrottlingProxy,int>(Client3,30*1000);
				CPair<CThrottlingProxy,int>			P4=new CPair<CThrottlingProxy,int>(Client4,30*1000);

				// Na serveri musia byt takto nastavene parametre.
				// MaxConcurrentCalls=2.
				// MaxConcurrentSessions=6.
				// MaxConcurrentInstances=6.

				T1.Start(P1);
				T2.Start(P2);
				T3.Start(P3);
				T4.Start(P4);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();
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

				if (Client3!=null && Client3.State!=CommunicationState.Faulted)
				{
					Client3.Close();
					Client3=null;
				}

				if (Client4!=null && Client4.State!=CommunicationState.Faulted)
				{
					Client4.Close();
					Client4=null;
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

			SessionTest();
			//InstanceTest();
			//CallTest();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------