using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransportSessionPerCallService;
//-------------------------------------------------------------------------------------------------------
namespace TransportSessionPerCallClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void WorkerThreadNoTS(object Param)
		{
			ISlowContractNoTS			Proxy=(ISlowContractNoTS) Param;

			Proxy.SlowOperation("WORKER THREAD NO TS");
		}
//-------------------------------------------------------------------------------------------------------
		private static void WorkerThreadWithTS(object Param)
		{
			ISlowContractWithTS			Proxy=(ISlowContractWithTS) Param;

			Proxy.SlowOperation("WORKER THREAD WITH TS");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void NoTSLongCall()
		{
			try
			{
				using(ChannelFactory<ISlowContractNoTS> CF=new ChannelFactory<ISlowContractNoTS>("NoTS"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						ISlowContractNoTS				Proxy=Disp as ISlowContractNoTS;

						Proxy.SlowOperation("TEST 1 " + DateTime.Now.ToShortTimeString());

						// Transport Session trva 10 minut - cakam dlhsie.
						Thread.Sleep(11*60*1000);

						Proxy.SlowOperation("TEST 2 " + DateTime.Now.ToShortTimeString());
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void WithTSLongCall()
		{
			try
			{
				using(ChannelFactory<ISlowContractNoTS> CF=new ChannelFactory<ISlowContractNoTS>("WithTS"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						ISlowContractNoTS				Proxy=Disp as ISlowContractNoTS;

						Proxy.SlowOperation("TEST 1 " + DateTime.Now.ToShortTimeString());

						// Transport Session trva 10 minut - cakam dlhsie.
						Thread.Sleep(11*60*1000);

						Proxy.SlowOperation("TEST 2 " + DateTime.Now.ToShortTimeString());
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void NoTS()
		{
			try
			{
				using(ChannelFactory<ISlowContractNoTS> CF=new ChannelFactory<ISlowContractNoTS>("NoTS"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						ISlowContractNoTS			Proxy=Disp as ISlowContractNoTS;
						Thread						T=new Thread(WorkerThreadNoTS);

						T.Start(Proxy);

						Proxy.SlowOperation("PRIMARY THREAD NO TS");

						T.Join();
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void WithTS()
		{
			try
			{
				using(ChannelFactory<ISlowContractWithTS> CF=new ChannelFactory<ISlowContractWithTS>("WithTS"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						ISlowContractWithTS			Proxy=Disp as ISlowContractWithTS;
						Thread						T=new Thread(WorkerThreadWithTS);

						T.Start(Proxy);

						Proxy.SlowOperation("PRIMARY THREAD WITH TS");

						T.Join();
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void NoTSTwoCalls()
		{
			try
			{
				using(ChannelFactory<ISlowContractNoTS> CF=new ChannelFactory<ISlowContractNoTS>("NoTS"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						ISlowContractNoTS			Proxy=Disp as ISlowContractNoTS;

						Proxy.SlowOperation("111");
						Proxy.SlowOperation("222");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void WithTSTwoCalls()
		{
			try
			{
				using(ChannelFactory<ISlowContractWithTS> CF=new ChannelFactory<ISlowContractWithTS>("WithTS"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						ISlowContractWithTS			Proxy=Disp as ISlowContractWithTS;

						Proxy.SlowOperation("111");
						Proxy.SlowOperation("222");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
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

			NoTS();
			Thread.Sleep(5*1000);
			WithTS();

			//NoTSLongCall();
			//WithTSLongCall();

			//NoTSTwoCalls();
			//WithTSTwoCalls();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------