using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using DelegatorChannel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannelTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			// Datagram demos.
			NetTcpBindingOneWayDemo();
			BasicHttpBindingOneWayDemo();
			WsHttpBindingOneWayDemo();

			// Requires a private queue named "DelegatorDemo".
			NetMsmqBindingOneWayDemo();

			// Request / reply demos.
			NetTcpBindingRequestReplyDemo();
			BasicHttpBindingRequestReplyDemo();
			WsHttpBindingRequestReplyDemo();

			// Duplex demos.
			NetTcpBindingDuplexDemo();

			// Sessionful demo
			NetTcpBindingOneWaySessionDemo();

			// Requires a private queue named "DelegatorSessionDemo".
			//NetMsmqBindingSessionDemo();

			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetMsmqBindingSessionDemo()
		{
			CPrintHelper.Print("==== BEGIN One Way NetMSMQBinding Sessionful Demo ==== !");

			Uri						Address=new Uri("net.msmq://localhost/private/DelegatorSessionDemo");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.MSMQSession);

			using(ServiceHost Svc=new ServiceHost(typeof(COneWaySessionfulTransactionalReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWaySession), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(TransactionScope Scope=new TransactionScope())
				{
					using(CMyOneWaySessionfulProxy Proxy=new CMyOneWaySessionfulProxy(Binding, new EndpointAddress(Address)))
					{
						try
						{
							Proxy.SomeOperation("Hi there");
							Proxy.SomeOtherOperation("Hi There Again");
						}
						catch(InvalidOperationException Ex)
						{
							CPrintHelper.Print(String.Format("{0}: {1} !", Ex.GetType().Name, Ex.Message));
						}

						Scope.Complete();
					}
				}

				// Give the receiver some time.
				Thread.Sleep(5000);
			}

			CPrintHelper.Print("==== END One Way NetMSMQBinding Sessionful Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetMsmqBindingOneWayDemo()
		{
			CPrintHelper.Print("==== BEGIN One Way NetMsmqBinding Demo ==== !");

			Uri						Address=new Uri("net.msmq://localhost/private/delegatordemo");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.MSMQ);

			using(ServiceHost Svc=new ServiceHost(typeof(COneWayReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWay), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(CMyOneWayProxy Proxy=new CMyOneWayProxy(Binding, new EndpointAddress(Address)))
				{
					while(Console.ReadLine()!="QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}
			}

			CPrintHelper.Print("==== END One Way NetMsmqBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingOneWaySessionDemo()
		{
			CPrintHelper.Print("==== BEGIN One Way NetTcpBinding Sessionful Demo ==== !");

			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractOneWaySessionful");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.Tcp);

			using (ServiceHost Svc=new ServiceHost(typeof(COneWaySessionfulReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWaySession), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				for (int i=0;i<2;i++)
				{
					using(CMyOneWaySessionfulProxy Proxy=new CMyOneWaySessionfulProxy(Binding, new EndpointAddress(Address)))
					{
						while(Console.ReadLine()!="QUIT")
						{
							try
							{
								Proxy.SomeOperation("Hi there");
								Proxy.SomeOtherOperation("Hi There Again");
							}
							catch (InvalidOperationException Ex)
							{
								CPrintHelper.Print(String.Format("{0}: {1} !", Ex.GetType().Name, Ex.Message));
							}
						}
					}
				}
			}

			CPrintHelper.Print("==== END One Way NetTcpBinding Sessionful Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingDuplexDemo()
		{
			CPrintHelper.Print("==== BEGIN Duplex NetTcpBinding Demo ==== !");
	        
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractDuplex");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.Tcp);

			using(ServiceHost Svc=new ServiceHost(typeof(CDuplexReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractDuplex), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				InstanceContext		InstanceContext=new InstanceContext(new CCallbackType());

				using(CMyDuplexProxy Proxy=new CMyDuplexProxy(InstanceContext, Binding, new EndpointAddress(Address)))
				{
					while(Console.ReadLine()!="QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}

				//Svc.Close();
			}

			CPrintHelper.Print("==== END Duplex NetTcpBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void WsHttpBindingRequestReplyDemo()
		{
			CPrintHelper.Print("==== BEGIN Request / Reply WsHttpBinding Demo ==== !");
	  
			Uri						Address=new Uri("http://localhost:4000/ISomeContractRequestReply");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.WSHttp);

			using(ServiceHost Svc=new ServiceHost(typeof(CRequestReplyReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractRequestReply), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(CMyRequestReplyProxy Proxy=new CMyRequestReplyProxy(Binding, new EndpointAddress(Address)))
				{
					while (Console.ReadLine()!="QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}
			}

			CPrintHelper.Print("==== END Request / Reply WsHttpBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void WsHttpBindingOneWayDemo()
		{
			CPrintHelper.Print("==== BEGIN One Way WsHttpBinding Demo ==== !");
	       
			Uri						Address=new Uri("http://localhost:4000/ISomeContractOneWay");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.WSHttp);

			using(ServiceHost Svc=new ServiceHost(typeof(COneWayReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWay), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(CMyOneWayProxy Proxy=new CMyOneWayProxy(Binding, new EndpointAddress(Address)))
				{
					while(Console.ReadLine() != "QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}
			}

			CPrintHelper.Print("==== END One Way WsHttpBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void BasicHttpBindingRequestReplyDemo()
		{
			CPrintHelper.Print("==== BEGIN Request / Reply BasicHttpBinding Demo ==== !");
	    
			Uri						Address=new Uri("http://localhost:4000/ISomeContractRequestReply");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.BasicHttp);

			using(ServiceHost Svc=new ServiceHost(typeof(CRequestReplyReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractRequestReply), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(CMyRequestReplyProxy Proxy=new CMyRequestReplyProxy(Binding, new EndpointAddress(Address)))
				{
					while(Console.ReadLine()!="QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}
			}

			CPrintHelper.Print("==== END Request / Reply BasicHttpBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void BasicHttpBindingOneWayDemo()
		{
			CPrintHelper.Print("==== BEGIN One Way BasicHttpBinding Demo ==== !");
	    
			Uri						Address=new Uri("http://localhost:4000/ISomeContractOneWay");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.BasicHttp);
	        
			using (ServiceHost Svc=new ServiceHost(typeof(COneWayReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWay), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(CMyOneWayProxy Proxy=new CMyOneWayProxy(Binding, new EndpointAddress(Address)))
				{
					while(Console.ReadLine()!="QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}
			}

			CPrintHelper.Print("==== END One Way BasicHttpBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingOneWayDemo()
		{
			CPrintHelper.Print("==== BEGIN One Way NetTcpBinding Demo ==== !");
	        
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractOneWay");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.Tcp);

			using(ServiceHost Svc=new ServiceHost(typeof(COneWayReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWay), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(CMyOneWayProxy Proxy=new CMyOneWayProxy(Binding, new EndpointAddress(Address)))
				{
					while(Console.ReadLine()!="QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}
			}

			CPrintHelper.Print("==== END One Way NetTcpBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingRequestReplyDemo()
		{
			CPrintHelper.Print("==== BEGIN Request / Reply NetTcpBinding Demo ==== !");
	        
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractRequestReply");
			CDelegatorBinding		Binding=new CDelegatorBinding(EBindingMode.Tcp);

			using(ServiceHost Svc=new ServiceHost(typeof(CRequestReplyReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractRequestReply), Binding, Address);
				Svc.Open();

				ReceiverReadyMessage();

				using(CMyRequestReplyProxy Proxy=new CMyRequestReplyProxy(Binding, new EndpointAddress(Address)))
				{
					while(Console.ReadLine()!="QUIT")
					{
						Proxy.SomeOperation("Hi there");
					}
				}
			}

			CPrintHelper.Print("==== END Request / Reply NetTcpBinding Demo ==== !");
			CPrintHelper.PrintNewLine();
		}
//-------------------------------------------------------------------------------------------------------
		private static void ReceiverReadyMessage()
		{
			string			Message=string.Format("{0}THE RECEIVER IS READY{0}PRESS ENTER TO SEND A MESSAGE, QUIT TO GO TO NEXT DEMO{0} !", Environment.NewLine);

			CPrintHelper.PrintNoThread(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------