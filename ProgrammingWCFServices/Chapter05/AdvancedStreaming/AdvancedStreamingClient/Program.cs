using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
using AdvancedStreamingHost;
//-------------------------------------------------------------------------------------------------------
namespace AdvancedStreamingClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void TestNotFullyFilledStream()
		{
			try
			{
				using(ChannelFactory<IAdvancedStreaming> CF=new ChannelFactory<IAdvancedStreaming>("EC"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						IAdvancedStreaming		Proxy=Disp as IAdvancedStreaming;

						Console.WriteLine("Test() 111 !");

						CMyTestStream			S=Proxy.GetNotFullyFilledStream();

						Console.WriteLine("Test() 222 !");

						Console.WriteLine("Press any key to START STREAM READ !");
						Console.ReadLine();

						CStreamHelper.FastReadStream(S);

						Console.WriteLine("Press any key to CLOSE !");
						Console.ReadLine();

						// Teraz MUSIM UZAVRIET STREAM.
						S.Close();
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestAlreadyFilledStream()
		{
			try
			{
				using(ChannelFactory<IAdvancedStreaming> CF=new ChannelFactory<IAdvancedStreaming>("EC"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						try
						{
							IAdvancedStreaming		Proxy=Disp as IAdvancedStreaming;

							Console.WriteLine("Test() 111 !");

							CMyTestStream			S=Proxy.GetAlreadyFilledStream();

							Console.WriteLine("Test() 222 !");

							Console.WriteLine("Press any key to START STREAM READ !");
							Console.ReadLine();

							CStreamHelper.SlowReadStream(S);

							Console.WriteLine("Press any key to CLOSE !");
							Console.ReadLine();

							// Teraz MUSIM UZAVRIET STREAM.
							S.Close();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
						}
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

			//TestNotFullyFilledStream();
			TestAlreadyFilledStream();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------