using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousWCF
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private async static Task<string> WCFCallAsAsynchronousFunction()
		{
			string												Result="";

			try
			{
				try
				{
					using(ServiceHost Host=new ServiceHost(typeof(CAsynchronousService)))
					{
						Host.Open();

						Console.WriteLine("HOST OPENED !");

						try
						{
							using (ChannelFactory<IAsynchronousService> ChannelFactory=new ChannelFactory<IAsynchronousService>("Proxy"))
							{
								ChannelFactory.Open();

								Console.WriteLine("CHANNEL FACTORY OPENED !");

								try
								{
									using (IDisposable Proxy=(IDisposable) ChannelFactory.CreateChannel())
									{
										ICommunicationObject	CommunicationObject=(ICommunicationObject) Proxy;

										CommunicationObject.Open();

										Console.WriteLine("PROXY OPENED !");

										IAsynchronousService	Interface=(IAsynchronousService) Proxy;

										Console.WriteLine("PROXY STARTING SERVICE METHOD CALL !");

										Task<string>			Task=Interface.AsynchronousSlowOperation("Timmy Anderson");

										// !!! Pouzijem OPERATOR AWAIT, aby som pockal na ukoncenie WCF SERVICE OPERATION CALL.
										await Task;

										Console.WriteLine("PROXY FINISHED SERVICE METHOD CALL !");

										Result=Task.Result;

										Console.WriteLine(string.Format("SERVICE RESULT [{0}]",Task.Result));
									}
								}
								finally
								{
									Console.WriteLine("PROXY CLOSED !");
								}
							}
						}
						finally
						{
							Console.WriteLine("CHANNEL FACTORY CLOSED !");
						}
					}
				}
				finally
				{
					Console.WriteLine("HOST CLOSED !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			return(Result);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				try
				{
					using(ServiceHost Host=new ServiceHost(typeof(CAsynchronousService)))
					{
						Host.Open();

						Console.WriteLine("HOST OPENED !");

						try
						{
							using (ChannelFactory<IAsynchronousService> ChannelFactory=new ChannelFactory<IAsynchronousService>("Proxy"))
							{
								ChannelFactory.Open();

								Console.WriteLine("CHANNEL FACTORY OPENED !");

								try
								{
									using (IDisposable Proxy=(IDisposable) ChannelFactory.CreateChannel())
									{
										ICommunicationObject	CommunicationObject=(ICommunicationObject) Proxy;

										CommunicationObject.Open();

										Console.WriteLine("PROXY OPENED !");

										IAsynchronousService	Interface=(IAsynchronousService) Proxy;

										Console.WriteLine("PROXY STARTING SERVICE METHOD CALL !");

										string					Result=Interface.SlowOperation("Timmy Anderson");

										Console.WriteLine("PROXY FINISHED SERVICE METHOD CALL !");

										Console.WriteLine(string.Format("SERVICE RESULT [{0}]",Result));
									}
								}
								finally
								{
									Console.WriteLine("PROXY CLOSED !");
								}
							}
						}
						finally
						{
							Console.WriteLine("CHANNEL FACTORY CLOSED !");
						}
					}
				}
				finally
				{
					Console.WriteLine("HOST CLOSED !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			try
			{
				try
				{
					using(ServiceHost Host=new ServiceHost(typeof(CAsynchronousService)))
					{
						Host.Open();

						Console.WriteLine("HOST OPENED !");

						try
						{
							using (ChannelFactory<IAsynchronousService> ChannelFactory=new ChannelFactory<IAsynchronousService>("Proxy"))
							{
								ChannelFactory.Open();

								Console.WriteLine("CHANNEL FACTORY OPENED !");

								try
								{
									using (IDisposable Proxy=(IDisposable) ChannelFactory.CreateChannel())
									{
										ICommunicationObject	CommunicationObject=(ICommunicationObject) Proxy;

										CommunicationObject.Open();

										Console.WriteLine("PROXY OPENED !");

										IAsynchronousService	Interface=(IAsynchronousService) Proxy;

										Console.WriteLine("PROXY STARTING SERVICE METHOD CALL !");

										Task<string>			Task=Interface.AsynchronousSlowOperation("Timmy Anderson");

										Console.WriteLine("PROXY WAITING for SERVICE METHOD CALL FINISH !");

										Task.Wait();

										Console.WriteLine("PROXY FINISHED SERVICE METHOD CALL !");

										Console.WriteLine(string.Format("SERVICE RESULT [{0}]",Task.Result));
									}
								}
								finally
								{
									Console.WriteLine("PROXY CLOSED !");
								}
							}
						}
						finally
						{
							Console.WriteLine("CHANNEL FACTORY CLOSED !");
						}
					}
				}
				finally
				{
					Console.WriteLine("HOST CLOSED !");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - BEFORE WCFCallAsAsynchronousFunction() CALLED !",Thread.CurrentThread.ManagedThreadId));

			Task<string>										AsynchronousFunctionTask=WCFCallAsAsynchronousFunction();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER WCFCallAsAsynchronousFunction() FINISHED !",Thread.CurrentThread.ManagedThreadId));

			AsynchronousFunctionTask.Wait();

			Console.WriteLine(string.Format("THREAD: [{0}] - MAIN - AFTER ASYNCHRONOUS FUNCTION TASK FINISHED, RESULT [{1}] !",Thread.CurrentThread.ManagedThreadId,AsynchronousFunctionTask.Result));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//Test1();
			//Test2();
			Test3();

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------