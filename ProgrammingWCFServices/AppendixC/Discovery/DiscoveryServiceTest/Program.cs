using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Discovery;
using DiscoverySharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DiscoveryService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Metoda vracia cislo volneho portu.
		private static int GetPortNumber()
		{
			IPEndPoint			AnyEndPoint=new IPEndPoint(IPAddress.Any,0);

			using(Socket S=new Socket(AddressFamily.InterNetwork,SocketType.Stream,ProtocolType.Tcp))
			{
				S.Bind(AnyEndPoint);

				// Ziskam adresu volneho portu.
				IPEndPoint		FreeEndPoint=(IPEndPoint) S.LocalEndPoint;

				return(FreeEndPoint.Port);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Pred pouzitim musim VYKOMENTOVAT App.config.
		private static void Test1()
		{
			try
			{
				using (ServiceHost SH=new ServiceHost(typeof(CToUpperService)))
				{
					DiscoveryEndpoint			DE=new UdpDiscoveryEndpoint();

					SH.AddServiceEndpoint(DE);

					string						Address=string.Format("net.tcp://{0}:{1}/",Environment.MachineName,GetPortNumber());
					NetTcpBinding				TCPBinding=new NetTcpBinding();
					ServiceDiscoveryBehavior	SDB=new ServiceDiscoveryBehavior();

					SH.Description.Behaviors.Add(SDB);

					ServiceEndpoint				SE=SH.AddServiceEndpoint(typeof(IToUpperContract),TCPBinding,Address);
					EndpointDiscoveryBehavior	EDB=new EndpointDiscoveryBehavior();

					EDB.Scopes.Add(new Uri("net.tcp://Scope1"));
					EDB.Scopes.Add(new Uri("net.tcp://Scope2"));

					SE.Behaviors.Add(EDB);

					SH.Open();

					Console.WriteLine("Press any key to STOP SERVICE !");
					Console.ReadLine();
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
				using (ServiceHost SH=new ServiceHost(typeof(CToUpperService)))
				{
					SH.Open();

					Console.WriteLine("Press any key to STOP SERVICE !");
					Console.ReadLine();
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
			try
			{
				using (ServiceHost SH1=new ServiceHost(typeof(CToUpperService)))
				{
					using (ServiceHost SH2=new ServiceHost(typeof(CToLowerService)))
					{
						SH1.Open();
						SH2.Open();

						Console.WriteLine("Press any key to STOP SERVICES !");
						Console.ReadLine();
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			//Test1();
			//Test2();
			Test3();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------