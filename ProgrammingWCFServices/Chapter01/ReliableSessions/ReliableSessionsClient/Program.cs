using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ReliableSessionsService;
//-------------------------------------------------------------------------------------------------------
namespace ReliableSessionsClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void TestReliableService_SlowClient()
		{
			try
			{
				string								ADDRESS="http://localhost:8001/ReliableService";

				WSHttpBinding						Binding=new WSHttpBinding();

				// Aktivujem Reliable Messaging.
				Binding.ReliableSession.Enabled=true;
				Binding.ReliableSession.Ordered=true;
				Binding.ReliableSession.InactivityTimeout=TimeSpan.FromSeconds(5);

				IToUpperService						Proxy=ChannelFactory<IToUpperService>.CreateChannel(Binding,new EndpointAddress(ADDRESS));
				ICommunicationObject				CO=Proxy as ICommunicationObject;
				IDisposable							D=Proxy as IDisposable;

				using(D)
				{
					CO.Open();

					string			Ret1=Proxy.ToUpper("Timmy 111");

					Console.WriteLine(string.Format("Value: [{0}] !",Ret1));

					Thread.Sleep(10*1000);

					string			Ret2=Proxy.ToUpper("Timmy 222");

					Console.WriteLine(string.Format("Value: [{0}] !",Ret2));

					CO.Close();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestNONReliableService_SlowClient()
		{
			try
			{
				string								ADDRESS="http://localhost:8001/NonReliableService";

				WSHttpBinding						Binding=new WSHttpBinding();

				// Aktivujem NON-Reliable Messaging.
				Binding.ReliableSession.Enabled=false;
				Binding.ReliableSession.Ordered=false;

				IToUpperService						Proxy=ChannelFactory<IToUpperService>.CreateChannel(Binding,new EndpointAddress(ADDRESS));
				ICommunicationObject				CO=Proxy as ICommunicationObject;
				IDisposable							D=Proxy as IDisposable;

				using(D)
				{
					CO.Open();

					string			Ret1=Proxy.ToUpper("Timmy 111");

					Console.WriteLine(string.Format("Value: [{0}] !",Ret1));

					Thread.Sleep(10*1000);

					string			Ret2=Proxy.ToUpper("Timmy 222");

					Console.WriteLine(string.Format("Value: [{0}] !",Ret2));

					CO.Close();
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

			TestReliableService_SlowClient();
			//TestNONReliableService_SlowClient();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------