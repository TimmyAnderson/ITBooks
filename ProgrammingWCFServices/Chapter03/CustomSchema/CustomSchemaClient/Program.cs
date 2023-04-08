using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
using CustomSchemaHost;
//-----------------------------------------------------------------------------
namespace CustomSchemaClient
{
//-----------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				using(ChannelFactory<ITestService> CF=new ChannelFactory<ITestService>("SE"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						try
						{
							ITestService			Proxy=Disp as ITestService;
							OTA_VehResRQ			Req=new OTA_VehResRQ();

							Req.EchoToken="Timmy";

							OTA_VehResRS			Resp=Proxy.ReserveVehicle(Req);

							Console.WriteLine(string.Format("EchoToken: [{0}] !", Resp.EchoToken));
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-----------------------------------------------------------------------------
		private static void Test2()
		{
			try
			{
				using(ChannelFactory<ITestService> CF=new ChannelFactory<ITestService>("SE"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						try
						{
							ITestService			Proxy=Disp as ITestService;
							OTA_VehResRQ			Req1=new OTA_VehResRQ();
							OTA_VehResRS			Req2=new OTA_VehResRS();

							Req1.EchoToken="Timmy";
							Req2.EchoToken="Jenny";

							OTA_VehResRS			Resp=Proxy.MyTest(Req1,Req2);

							Console.WriteLine(string.Format("EchoToken: [{0}] !", Resp.EchoToken));
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------