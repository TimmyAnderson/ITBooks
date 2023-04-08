using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Discovery;
using AnnouncementsSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AnnouncementsClientTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// Vyvola SERVICE.
		private static void CallToUpper(EndpointAddress Address)
		{
			try
			{
				NetTcpBinding				TCPBinding=new NetTcpBinding();

				using(ChannelFactory<IToUpperContract> CF=new ChannelFactory<IToUpperContract>(TCPBinding,Address))
				{
					ICommunicationObject	CO=(ICommunicationObject) CF.CreateChannel();

					CO.Open();

					IToUpperContract		Proxy=CF.CreateChannel();
					string					Ret=Proxy.ToUpper("Timmy");

					Console.WriteLine(string.Format("Response: [{0}] !",Ret));

					CO.Close();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void AS_OnlineAnnouncementReceived(object Sender, AnnouncementEventArgs E)
		{
			EndpointAddress			EA=E.EndpointDiscoveryMetadata.Address;

			Console.WriteLine(string.Format("ONLINE ANNOUNCEMENT: [{0}] !",EA.Uri));

			foreach(Uri Scope in E.EndpointDiscoveryMetadata.Scopes)
				Console.WriteLine(string.Format("\tSCOPE: [{0}] !",Scope));
			
			CallToUpper(EA);
		}
//-------------------------------------------------------------------------------------------------------
		private static void AS_OfflineAnnouncementReceived(object Sender, AnnouncementEventArgs E)
		{
			EndpointAddress			EA=E.EndpointDiscoveryMetadata.Address;

			Console.WriteLine(string.Format("OFFLINE ANNOUNCEMENT: [{0}] !",EA.Uri));

			foreach(Uri Scope in E.EndpointDiscoveryMetadata.Scopes)
				Console.WriteLine(string.Format("\tSCOPE: [{0}] !",Scope));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				// Vytvorim SINGLETON objekt.
				AnnouncementService			AS=new AnnouncementService();

				// Zaregistrujem prijem ANNOUNCEMENTS EVENTS.
				AS.OnlineAnnouncementReceived+=new EventHandler<AnnouncementEventArgs>(AS_OnlineAnnouncementReceived);
				AS.OfflineAnnouncementReceived+=new EventHandler<AnnouncementEventArgs>(AS_OfflineAnnouncementReceived);

				// Vytvorim ANNOUNCEMENT ENDPOINT.
				UdpAnnouncementEndpoint		AE=new UdpAnnouncementEndpoint();

				// Vytvorim HOST so SINGLETON objektom.
				using (ServiceHost SH=new ServiceHost(AS))
				{
					// Pridam ANNOUNCEMENT ENDPOINT do HOST.
					SH.AddServiceEndpoint(AE);

					SH.Open();

					Console.WriteLine("Press any key to STOP ANNOUNCEMENT HOST !");
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
			Console.Title="CLIENT";

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------