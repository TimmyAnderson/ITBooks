using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ReentrancyTestHost;
//-------------------------------------------------------------------------------------------------------
namespace ReentrancyTestClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static IService									MProxy;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void WorkerThread(object Param)
		{
			Thread.Sleep(1*1000);

			Console.WriteLine("WORKER THREAD BEFORE CALL !");

			MProxy.SomeOperation("WORKER THREAD");

			Console.WriteLine("WORKER THREAD AFTER CALL !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void WorkerThreadWithParam1(object Param)
		{
			IService					Proxy=(IService) Param;

			Thread.Sleep(1*1000);

			Console.WriteLine("WORKER THREAD 111 BEFORE CALL !");

			Proxy.SomeOperation("WORKER THREAD 111");

			Console.WriteLine("WORKER THREAD 111 AFTER CALL !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void WorkerThreadWithParam2(object Param)
		{
			IService					Proxy=(IService) Param;

			Thread.Sleep(1*1000);

			Console.WriteLine("WORKER THREAD 222 BEFORE CALL !");

			//Proxy.SomeOperation("WORKER THREAD 222");
			Proxy.SomeOperationWithCallback("WORKER THREAD 222");

			Console.WriteLine("WORKER THREAD 222 AFTER CALL !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				CCallback				Calllback=new CCallback();

				using(DuplexChannelFactory<IService> CF=new DuplexChannelFactory<IService>(new InstanceContext(Calllback),"EP"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						MProxy=Disp as IService;

						// OTVORIM PROXY.
						// !!!!! POKYM NIE JE PROXY OTVORENE, TAK VSETKY VOLANIA SU SYNCHRONNE BEZ OHLADU NATO AKO NASTAVIM CONCURRENCY MOD.
						MProxy.Dummy();

						Thread			T=new Thread(WorkerThread);

						T.Start();

						try
						{
							//MProxy.SomeOperation("PRIMARY THREAD");
							MProxy.SomeOperationWithCallback("PRIMARY THREAD");
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}
	
						Console.WriteLine("Press any key to STOP !");
						Console.ReadLine();
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2Proxies()
		{
			try
			{
				CCallback			Calllback=new CCallback();

				using(DuplexChannelFactory<IService> CF=new DuplexChannelFactory<IService>(new InstanceContext(Calllback),"EP"))
				{
					IDisposable		Disp1=(CF.CreateChannel() as IDisposable);
					IDisposable		Disp2=(CF.CreateChannel() as IDisposable);

					IService		Proxy1=Disp1 as IService;
					IService		Proxy2=Disp2 as IService;

					Thread			T1=new Thread(WorkerThreadWithParam1);
					Thread			T2=new Thread(WorkerThreadWithParam2);

					Proxy1.Dummy();
					Proxy2.Dummy();

					T1.Start(Proxy1);
					T2.Start(Proxy2);

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();

					Disp1.Dispose();
					Disp2.Dispose();
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

			Test();
			//Test2Proxies();

			Console.WriteLine("\nPress any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------