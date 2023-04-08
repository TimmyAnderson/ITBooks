using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AsynchronousCallsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void OnSlowMethodCompletion(IAsyncResult Result)
		{
			CAsynchronousCallsProxy			Proxy=(CAsynchronousCallsProxy) Result.AsyncState;

			Console.WriteLine("OnSlowMethodCompletion() CALLED !");

			Thread.Sleep(100);

			try
			{
				string						RefMessage="XXX";
				string						OutMessage;
				string						RetMessage;

				Console.WriteLine(string.Format("OnSlowMethodCompletion(): AsyncState - {0} !",Proxy.ToString()));
				Console.WriteLine(string.Format("OnSlowMethodCompletion(): IsCompleted - {0} !",Result.IsCompleted));
				Console.WriteLine(string.Format("OnSlowMethodCompletion(): RefMessage - {0} !",RefMessage));

				RetMessage=Proxy.EndSlowMethod(ref RefMessage, out OutMessage, Result);

				Console.WriteLine(string.Format("OnSlowMethodCompletion(): AsyncState - {0} !",Proxy.ToString()));
				Console.WriteLine(string.Format("OnSlowMethodCompletion(): IsCompleted - {0} !",Result.IsCompleted));
				Console.WriteLine(string.Format("OnSlowMethodCompletion(): RefMessage - {0} !",RefMessage));
				Console.WriteLine(string.Format("OnSlowMethodCompletion(): OutMessage - {0} !",OutMessage));
				Console.WriteLine(string.Format("OnSlowMethodCompletion(): RetMessage - {0} !",RetMessage));

				// Je treba vzdy zatvarat WaitHandle.
				Result.AsyncWaitHandle.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
			}

			// !!! MUSIM UZAVRIET PROXY.
			try
			{
				if (Proxy!=null && Proxy.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Proxy.Close();
					Console.WriteLine("AFTER CLOSE !");
					Proxy=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Proxy.Abort();
					Console.WriteLine("AFTER ABORT !");
					Proxy=null;
				}

				// !!! MUSIM UZAVRIET i WAIT HANDLE.
				Result.AsyncWaitHandle.Dispose();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void OnAsynchroSlowMethodCompletion(IAsyncResult AR)
		{
			CAsynchronousCallsProxy				Proxy=(CAsynchronousCallsProxy) AR.AsyncState;

			Console.WriteLine("OnAsynchroSlowMethodCompletion() CALLED !");

			try
			{
				string							Ret=Proxy.EndServerAsynchroSlowMethod(AR);
	
				Console.WriteLine(string.Format("OnAsynchroSlowMethodCompletion() - EndServerAsynchroSlowMethod() RETURNED [{0}] !",Ret));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
			}

			// !!! MUSIM UZAVRIET PROXY.
			try
			{
				if (Proxy!=null && Proxy.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Proxy.Close();
					Console.WriteLine("AFTER CLOSE !");
					Proxy=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Proxy.Abort();
					Console.WriteLine("AFTER ABORT !");
					Proxy=null;
				}

				// !!! MUSIM UZAVRIET i WAIT HANDLE.
				AR.AsyncWaitHandle.Dispose();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void OnSlowMethodWithExceptionCompletion(IAsyncResult Result)
		{
			CAsynchronousCallsProxy		Proxy=(CAsynchronousCallsProxy) Result.AsyncState;

			Console.WriteLine(string.Format("OnSlowMethodWithExceptionCompletion(): AsyncState - {0} !",Proxy.ToString()));

			try
			{
				Proxy.EndSlowMethodWithException(Result);
			}
			catch(FaultException<Exception> E)
			{
				Console.WriteLine(string.Format("FaultException<Exception>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
			}
			catch(FaultException E)
			{
				Console.WriteLine(string.Format("OnSlowMethodWithExceptionCompletion: Msg: {0} !",E.Message));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
			}

			Console.WriteLine(string.Format("OnSlowMethodCompletion(): AsyncState - {0} !",Proxy.ToString()));

			// Je treba vzdy zatvarat WaitHandle.
			Result.AsyncWaitHandle.Close();

			// !!! MUSIM UZAVRIET PROXY.
			if (Proxy!=null && Proxy.State!=CommunicationState.Faulted)
			{
				Console.WriteLine("BEFORE CLOSE !");
				Proxy.Close();
				Console.WriteLine("AFTER CLOSE !");
				Proxy=null;
			}
			else
			{
				Console.WriteLine("BEFORE ABORT !");
				Proxy.Abort();
				Console.WriteLine("AFTER ABORT !");
				Proxy=null;
			}

			// !!! MUSIM UZAVRIET i WAIT HANDLE.
			Result.AsyncWaitHandle.Dispose();
		}
//-------------------------------------------------------------------------------------------------------
		static void OnSlowMethodWithUnexpectedExceptionCompletion(IAsyncResult Result)
		{
			CAsynchronousCallsProxy		Proxy=(CAsynchronousCallsProxy) Result.AsyncState;

			Console.WriteLine(string.Format("OnSlowMethodWithUnexpectedExceptionCompletion(): AsyncState - {0} !",Proxy.ToString()));

			try
			{
				Proxy.EndSlowMethodWithUnexpectedException(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
			}

			Console.WriteLine(string.Format("OnSlowMethodWithUnexpectedExceptionCompletion(): AsyncState - {0} !",Proxy.ToString()));

			// Je treba vzdy zatvarat WaitHandle.
			Result.AsyncWaitHandle.Close();

			// !!! MUSIM UZAVRIET PROXY.
			if (Proxy!=null && Proxy.State!=CommunicationState.Faulted)
			{
				Console.WriteLine("BEFORE CLOSE !");
				Proxy.Close();
				Console.WriteLine("AFTER CLOSE !");
				Proxy=null;
			}
			else
			{
				Console.WriteLine("BEFORE ABORT !");
				Proxy.Abort();
				Console.WriteLine("AFTER ABORT !");
				Proxy=null;
			}

			// !!! MUSIM UZAVRIET i WAIT HANDLE.
			Result.AsyncWaitHandle.Dispose();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Test1()
		{
			CAsynchronousCallsProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				try
				{
					Client.BeginSlowMethodWithUnexpectedException("HELLO",OnSlowMethodWithUnexpectedExceptionCompletion,Client);
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));

				// !!!!! MUSIM volat Close(), kedze KED ZLYHA BeginXXX(), tak ASYNCHRONNA OPERACIE sa NESPUSTI a CALLBACK sa UZ NEVYVOLA.
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
			finally
			{
				// !!!!! NESMIEM volat Close(), kedze UZAVRETIM PROXY PRED UKONCENIM CALLBACK by sposobilo GENEROVANIE EXCEPTION v CALLBACK, kedze CHANNEL uz NEBUDE PLATNY. Toto vsak plati IBA AK JE ZAPNUTA TRANSPORT SESSION. Ak je VYPNUTA, kludne MOZEM ZATVORIT PROXY a EndXXX() stale BUDEM MOCT ZAVOLAT.

				/*
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
				*/
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test2()
		{
			CAsynchronousCallsProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				try
				{
					Client.BeginSlowMethodWithException("HELLO",OnSlowMethodWithExceptionCompletion,Client);
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(string.Format("FaultException<ObjectDisposedException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));

				// !!!!! MUSIM volat Close(), kedze KED ZLYHA BeginXXX(), tak ASYNCHRONNA OPERACIE sa NESPUSTI a CALLBACK sa UZ NEVYVOLA.
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
			finally
			{
				// !!!!! NESMIEM volat Close(), kedze UZAVRETIM PROXY PRED UKONCENIM CALLBACK by sposobilo GENEROVANIE EXCEPTION v CALLBACK, kedze CHANNEL uz NEBUDE PLATNY. Toto vsak plati IBA AK JE ZAPNUTA TRANSPORT SESSION. Ak je VYPNUTA, kludne MOZEM ZATVORIT PROXY a EndXXX() stale BUDEM MOCT ZAVOLAT.

				/*
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
				*/
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test3()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";
			string								RefMessage="HELLO";

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				try
				{
					Client.BeginSlowMethod(Message, ref RefMessage,OnSlowMethodCompletion,Client);
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(string.Format("FaultException<ObjectDisposedException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));

				// !!!!! MUSIM volat Close(), kedze KED ZLYHA BeginXXX(), tak ASYNCHRONNA OPERACIE sa NESPUSTI a CALLBACK sa UZ NEVYVOLA.
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
			finally
			{
				// !!!!! NESMIEM volat Close(), kedze UZAVRETIM PROXY PRED UKONCENIM CALLBACK by sposobilo GENEROVANIE EXCEPTION v CALLBACK, kedze CHANNEL uz NEBUDE PLATNY. Toto vsak plati IBA AK JE ZAPNUTA TRANSPORT SESSION. Ak je VYPNUTA, kludne MOZEM ZATVORIT PROXY a EndXXX() stale BUDEM MOCT ZAVOLAT.

				/*
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
				*/
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test4()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";
			string								RefMessage="HELLO";
			IAsyncResult						AsyncResult;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				AsyncResult=Client.BeginSlowMethodWithException(Message,null,null);

				Console.WriteLine(string.Format("Test4(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test4(): RefMessage - {0} !",RefMessage));

				while(true)
				{
					// Cakam na nastavenie handle.
					if (AsyncResult.AsyncWaitHandle.WaitOne(1000,false)==true)
						break;

					Console.WriteLine(string.Format("Test4(): WAITING !"));
				}

				try
				{
					Client.EndSlowMethodWithException(AsyncResult);
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(string.Format("FaultException<Exception>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("OnSlowMethodWithExceptionCompletion: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine(string.Format("Test4(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test4(): RefMessage - {0} !",RefMessage));

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
				// Kedze ASYNCHRONNA OPERACIA SKONCILA, mozem volat Close().
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test5()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";
			string								RefMessage="HELLO";
			string								OutMessage="HELLO";
			string								RetMessage="HELLO";
			IAsyncResult						AsyncResult;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				AsyncResult=Client.BeginSlowMethod(Message, ref RefMessage,null,null);

				Console.WriteLine(string.Format("Test5(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test5(): RefMessage - {0} !",RefMessage));

				while(true)
				{
					// Cakam na nastavenie handle.
					if (AsyncResult.AsyncWaitHandle.WaitOne(1000,false)==true)
						break;

					Console.WriteLine(string.Format("Test5(): WAITING !"));
				}

				RetMessage=Client.EndSlowMethod(ref RefMessage, out OutMessage, AsyncResult);

				Console.WriteLine(string.Format("Test5(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test5(): RefMessage - {0} !",RefMessage));
				Console.WriteLine(string.Format("Test5(): OutMessage - {0} !",OutMessage));
				Console.WriteLine(string.Format("Test5(): RetMessage - {0} !",RetMessage));

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
				// Kedze ASYNCHRONNA OPERACIA SKONCILA, mozem volat Close().
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test6()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";
			string								RefMessage="HELLO";
			IAsyncResult						AsyncResult;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				AsyncResult=Client.BeginSlowMethodWithException(Message,null,null);

				Console.WriteLine(string.Format("Test6(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test6(): RefMessage - {0} !",RefMessage));

				while(true)
				{
					// Cakam na nastavenie handle.
					if (AsyncResult.IsCompleted==true)
						break;

					Console.WriteLine(string.Format("Test6(): WAITING !"));
					Thread.Sleep(1000);
				}

				try
				{
					Client.EndSlowMethodWithException(AsyncResult);
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(string.Format("FaultException<Exception>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("OnSlowMethodWithExceptionCompletion: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}

				Console.WriteLine(string.Format("Test6(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test6(): RefMessage - {0} !",RefMessage));

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
				// Kedze ASYNCHRONNA OPERACIA SKONCILA, mozem volat Close().
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test7()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";
			string								RefMessage="HELLO";
			string								OutMessage="HELLO";
			string								RetMessage="HELLO";
			IAsyncResult						AsyncResult;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				AsyncResult=Client.BeginSlowMethod(Message, ref RefMessage,null,null);

				Console.WriteLine(string.Format("Test7(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test7(): RefMessage - {0} !",RefMessage));

				while(true)
				{
					// Cakam na nastavenie handle.
					if (AsyncResult.IsCompleted==true)
						break;

					Console.WriteLine(string.Format("Test7(): WAITING !"));
					Thread.Sleep(1000);
				}

				RetMessage=Client.EndSlowMethod(ref RefMessage, out OutMessage, AsyncResult);

				Console.WriteLine(string.Format("Test7(): IsCompleted - {0} !",AsyncResult.IsCompleted));
				Console.WriteLine(string.Format("Test7(): RefMessage - {0} !",RefMessage));
				Console.WriteLine(string.Format("Test7(): OutMessage - {0} !",OutMessage));
				Console.WriteLine(string.Format("Test7(): RetMessage - {0} !",RetMessage));

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
				// Kedze ASYNCHRONNA OPERACIA SKONCILA, mozem volat Close().
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!! Metoda demonstruje co sa stane, ked spravim Proxy.Close() SKOR ako sa ASYNCHRONNA OPERACIA UKONCI.
		// !!! Metoda Test3() ukazuje ako sa ma SPRAVNE UZATVARAT PROXY AZ v CALLBACK METODE.
		static void Test8()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";
			string								RefMessage="HELLO";

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				try
				{
					Client.BeginSlowMethod(Message, ref RefMessage,OnSlowMethodCompletion,Client);
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(string.Format("FaultException<ObjectDisposedException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));

				// !!!!! MUSIM volat Close(), kedze KED ZLYHA BeginXXX(), tak ASYNCHRONNA OPERACIE sa NESPUSTI a CALLBACK sa UZ NEVYVOLA.
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
			finally
			{
				// !!!!! UMYSELNE PRED SKONCENIM ASYNCHRONNEJ OPERACIE UZAVRIEM PROXY volanim Close().
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Volanie ASYNCHRONNEJ OPERACIE na strane SERVICE. PEKNE MI FUNGUJE.
		static void Test9()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				try
				{
					Client.BeginServerAsynchroSlowMethod(Message,OnAsynchroSlowMethodCompletion,Client);

					Console.WriteLine("BeginServerAsynchroSlowMethod() SUCCESSFULLY CALLED !");
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(string.Format("FaultException<ObjectDisposedException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));

				// !!!!! MUSIM volat Close(), kedze KED ZLYHA BeginXXX(), tak ASYNCHRONNA OPERACIE sa NESPUSTI a CALLBACK sa UZ NEVYVOLA.
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
			finally
			{
				// !!!!! NESMIEM volat Close(), kedze UZAVRETIM PROXY PRED UKONCENIM CALLBACK by sposobilo GENEROVANIE EXCEPTION v CALLBACK, kedze CHANNEL uz NEBUDE PLATNY. Toto vsak plati IBA AK JE ZAPNUTA TRANSPORT SESSION. Ak je VYPNUTA, kludne MOZEM ZATVORIT PROXY a EndXXX() stale BUDEM MOCT ZAVOLAT.

				/*
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
				*/
			}
		}
//-------------------------------------------------------------------------------------------------------
		static void Test10()
		{
			CAsynchronousCallsProxy				Client=null;
			string								Message="HELLO";
			string								RefMessage="HELLO";
			IAsyncResult						Result=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// VYPNEM SESSION, aby som mohol otestovat co BUDEM MOCT UZATVORIT PROXY SKOR ako SKONCI ASYNCHRONNE VOLANIE.
			TCPBinding.ReliableSession.Enabled=false;

			try
			{
				Client=new CAsynchronousCallsProxy(TCPBinding,"net.tcp://localhost:9001/IAsynchronousCallsContract");

				Client.Open();

				try
				{
					Result=Client.BeginSlowMethod(Message, ref RefMessage,OnSlowMethodCompletion,Client);
				}
				catch(FaultException<Exception> E)
				{
					Console.WriteLine(string.Format("FaultException<ObjectDisposedException>: Msg: {0}, Detail: {1} !",E.Message,E.Detail));
				}
				catch(FaultException E)
				{
					Console.WriteLine(string.Format("FaultException: Msg: {0} !",E.Message));
				}
				catch(Exception E)
				{
					Console.WriteLine(string.Format("Exception: Msg: {0} !",E.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));

				// !!!!! MUSIM volat Close(), kedze KED ZLYHA BeginXXX(), tak ASYNCHRONNA OPERACIE sa NESPUSTI a CALLBACK sa UZ NEVYVOLA.
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}
			}
			finally
			{
				// !!!!! Zavolam Close(), kedze NEPOUZIVAM TRANSPORT SESSION.
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
				else
				{
					Console.WriteLine("BEFORE ABORT !");
					Client.Abort();
					Console.WriteLine("AFTER ABORT !");
					Client=null;
				}

				if (Result!=null)
				{
					// !!! MUSIM UZAVRIET i WAIT HANDLE.
					Result.AsyncWaitHandle.Dispose();
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
			//Test4();
			//Test5();
			//Test6();
			//Test7();
			//Test8();
			//Test9();
			Test10();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------