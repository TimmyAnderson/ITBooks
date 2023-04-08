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
using AnnouncementsSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AnnouncementsServiceTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Pred pouzitim musim VYKOMENTOVAT App.config.
		// Manualne posielanie ANNOUNCEMENTS.
		private static void Test1()
		{
			try
			{
				using (ServiceHost SH=new ServiceHost(typeof(CToUpperService)))
				{
					string						Address="net.tcp://localhost:2000/";
					NetTcpBinding				TCPBinding=new NetTcpBinding();
					ServiceEndpoint				SE=SH.AddServiceEndpoint(typeof(IToUpperContract),TCPBinding,Address);

					// Pridam SCOPES.
					EndpointDiscoveryBehavior	EDB=new EndpointDiscoveryBehavior();

					EDB.Scopes.Add(new Uri("net.tcp://Scope1"));
					EDB.Scopes.Add(new Uri("net.tcp://Scope2"));

					SE.Behaviors.Add(EDB);

					SH.Open();

					// Ziskam METADATA pre dany ENDPOINT, ktoreho HELLO a BYE udalosti chcem oznamovat.
					EndpointDiscoveryMetadata	EDM=EndpointDiscoveryMetadata.FromServiceEndpoint(SE);

					// Vytvorim ANNOUNCEMENT ENDPOINT.
					UdpAnnouncementEndpoint		AE=new UdpAnnouncementEndpoint();

					using (AnnouncementClient AC=new AnnouncementClient(AE))
					{
						Console.WriteLine("Press any key to send START ANNOUNCEMENT !");
						Console.ReadLine();

						AC.AnnounceOnline(EDM);

						Console.WriteLine("Press any key to send STOP ANNOUNCEMENT !");
						Console.ReadLine();

						AC.AnnounceOffline(EDM);

						Console.WriteLine("Press any key to send START ANNOUNCEMENT !");
						Console.ReadLine();

						AC.AnnounceOnline(EDM);

						Console.WriteLine("Press any key to send STOP ANNOUNCEMENT !");
						Console.ReadLine();

						AC.AnnounceOffline(EDM);
					}

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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			Test1();
			//Test2();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------