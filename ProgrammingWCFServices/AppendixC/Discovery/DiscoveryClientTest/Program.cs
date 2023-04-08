using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Discovery;
using DiscoverySharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DiscoveryClientTest
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
		// Vyvola SERVICE.
		private static void CallToLower(EndpointAddress Address)
		{
			try
			{
				NetTcpBinding				TCPBinding=new NetTcpBinding();

				using(ChannelFactory<IToLowerContract> CF=new ChannelFactory<IToLowerContract>(TCPBinding,Address))
				{
					ICommunicationObject	CO=(ICommunicationObject) CF.CreateChannel();

					CO.Open();

					IToLowerContract		Proxy=CF.CreateChannel();
					string					Ret=Proxy.ToLower("Timmy");

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
		private static void Client_FindCompleted_ToUpper(object Sender, FindCompletedEventArgs E)
		{
			FindResponse				Response=E.Result;
			
			foreach(EndpointDiscoveryMetadata EDM in Response.Endpoints)
			{
				Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

				foreach(Uri Scope in EDM.Scopes)
					Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));

				CallToUpper(EDM.Address);
			}

			ManualResetEvent			MRE=(ManualResetEvent) E.UserState;

			MRE.Set();
		}
//-------------------------------------------------------------------------------------------------------
		private static void Client_FindCompleted_ToLower(object Sender, FindCompletedEventArgs E)
		{
			FindResponse				Response=E.Result;

			foreach(EndpointDiscoveryMetadata EDM in Response.Endpoints)
			{
				Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

				foreach(Uri Scope in EDM.Scopes)
					Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));

				CallToLower(EDM.Address);
			}

			ManualResetEvent			MRE=(ManualResetEvent) E.UserState;

			MRE.Set();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			try
			{
				UdpDiscoveryEndpoint		DiscoveryEndpoint=new UdpDiscoveryEndpoint();
				DiscoveryClient				Client=new DiscoveryClient(DiscoveryEndpoint);
				FindCriteria				Criteria=new FindCriteria(typeof(IToUpperContract));

				Console.WriteLine("Seraching for ENDPOINTS !");

				FindResponse				Response=Client.Find(Criteria);
			
				foreach(EndpointDiscoveryMetadata EDM in Response.Endpoints)
				{
					Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

					foreach(Uri Scope in EDM.Scopes)
						Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));

					CallToUpper(EDM.Address);
				}

				Console.WriteLine("Serach FINISHED !");
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
				UdpDiscoveryEndpoint		DiscoveryEndpoint=new UdpDiscoveryEndpoint();
				DiscoveryClient				Client=new DiscoveryClient(DiscoveryEndpoint);
				FindCriteria				Criteria1=new FindCriteria(typeof(IToUpperContract));
				FindCriteria				Criteria2=new FindCriteria(typeof(IToLowerContract));

				Console.WriteLine("Seraching for ENDPOINTS !");

				FindResponse				Response1=Client.Find(Criteria1);
			
				foreach(EndpointDiscoveryMetadata EDM in Response1.Endpoints)
				{
					Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

					foreach(Uri Scope in EDM.Scopes)
						Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));

					CallToUpper(EDM.Address);
				}

				FindResponse				Response2=Client.Find(Criteria2);
			
				foreach(EndpointDiscoveryMetadata EDM in Response2.Endpoints)
				{
					Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

					foreach(Uri Scope in EDM.Scopes)
						Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));

					CallToLower(EDM.Address);
				}

				Console.WriteLine("Serach FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Asynchronne hladanie.
		private static void Test3()
		{
			try
			{
				UdpDiscoveryEndpoint		DiscoveryEndpoint=new UdpDiscoveryEndpoint();
				DiscoveryClient				Client1=new DiscoveryClient(DiscoveryEndpoint);
				DiscoveryClient				Client2=new DiscoveryClient(DiscoveryEndpoint);
				FindCriteria				Criteria1=new FindCriteria(typeof(IToUpperContract));
				FindCriteria				Criteria2=new FindCriteria(typeof(IToLowerContract));

				Console.WriteLine("Seraching for ENDPOINTS !");

				ManualResetEvent			Event1=new ManualResetEvent(false);

				Client1.FindCompleted+=new EventHandler<FindCompletedEventArgs>(Client_FindCompleted_ToUpper);
				Client1.FindAsync(Criteria1,Event1);
				Event1.WaitOne();

				ManualResetEvent			Event2=new ManualResetEvent(false);

				Client2.FindCompleted+=new EventHandler<FindCompletedEventArgs>(Client_FindCompleted_ToLower);
				Client2.FindAsync(Criteria2,Event2);
				Event2.WaitOne();

				Console.WriteLine("Serach FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Obmedzenie poctu hladanych ENDPOINTS.
		private static void Test4()
		{
			try
			{
				UdpDiscoveryEndpoint		DiscoveryEndpoint=new UdpDiscoveryEndpoint();
				DiscoveryClient				Client=new DiscoveryClient(DiscoveryEndpoint);
				FindCriteria				Criteria1=new FindCriteria(typeof(IToUpperContract));
				FindCriteria				Criteria2=new FindCriteria(typeof(IToLowerContract));

				// Uz po najdeni 1. ENDPOINT sa ukonci Find().
				Criteria1.MaxResults=1;
				Criteria2.MaxResults=1;

				Console.WriteLine("Seraching for ENDPOINTS !");

				FindResponse				Response1=Client.Find(Criteria1);
			
				foreach(EndpointDiscoveryMetadata EDM in Response1.Endpoints)
				{
					Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

					foreach(Uri Scope in EDM.Scopes)
						Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));

					CallToUpper(EDM.Address);
				}

				FindResponse				Response2=Client.Find(Criteria2);
			
				foreach(EndpointDiscoveryMetadata EDM in Response2.Endpoints)
				{
					Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

					foreach(Uri Scope in EDM.Scopes)
						Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));

					CallToLower(EDM.Address);
				}

				Console.WriteLine("Serach FINISHED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Hladam MEX rozhrania.
		private static void Test5()
		{
			try
			{
				UdpDiscoveryEndpoint		DiscoveryEndpoint=new UdpDiscoveryEndpoint();
				DiscoveryClient				Client=new DiscoveryClient(DiscoveryEndpoint);

				// Vytvorim FindCriteria pre MEX.
				FindCriteria				Criteria=FindCriteria.CreateMetadataExchangeEndpointCriteria();

				// Uz po najdeni 2 ENDPOINT sa ukonci Find().
				Criteria.MaxResults=2;

				Console.WriteLine("Seraching for ENDPOINTS !");

				FindResponse				Response=Client.Find(Criteria);
			
				foreach(EndpointDiscoveryMetadata EDM in Response.Endpoints)
				{
					Console.WriteLine(string.Format("\tAddress: [{0}] !",EDM.Address));

					foreach(Uri Scope in EDM.Scopes)
						Console.WriteLine(string.Format("\t\tScope: [{0}] !",Scope));
				}

				Console.WriteLine("Serach FINISHED !");
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

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			//Test1();
			//Test2();
			//Test3();
			//Test4();
			Test5();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------