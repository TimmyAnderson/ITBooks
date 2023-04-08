using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using LCChannel;
using Log;
//-------------------------------------------------------------------------------------------------------
/*
	Vyskytol sa mi nasledujuci problem, ktory som sice vyriesil, ale nie som si jeho riesenim 100 percent isty.

	Pri uzatvarani ServiceHost hodi za istych okolnosti FIRST CHANCE EXCEPTION: CommunicationObjectAbortedException.
	Tento problem sa vyskytol aj na testovacom priklade z knihy.
	Vyskytuje sa iba ak aktivujem aj svoj CH. Pri pouziti B bez mojho CH chyba nenastava.
	Avsak chyba sa vyskytuje aj vtedy ked CH vykomentujem a pouzivam iba moje CL a CF.
	Chyba sa nevyskytla ked CL mal moj CH, ale CF ho nemal.
	Naopak vyskytla sa vtedy ked CL nemal moj CH, ale CF ho mal.
	Ked som ukoncil program bez toho aby som zavrel ServiceHost tak chyba nevyskocila.
	??? Na pocitaci v robote sa mi chyba nevyskytla, takze ozaj neviem kde je problem.

	Chyba ma nasledujuce znenie:

	A first chance exception of type 'System.ServiceModel.CommunicationObjectAbortedException' occurred in System.ServiceModel.dll
	Additional information: A TCP error (995: The I/O operation has been aborted because of either a thread exit or an application request) occurred while transmitting data.

	Riesenie:

	Spocivalo v pretazeni abstraknych metod CF (Close() + asynchronne verize a Abort()).
	To som mal aj predtym, ale volali iba svoju base verziu.
	Vyhodil som toto volanie a nahradil ho volanim asociovanej metody svojho parent CF - OnClose() vola MInnerFactory.Close(Timeout) namiesto base.Close(Timeout).
*/
//-------------------------------------------------------------------------------------------------------
namespace ComplexTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingDuplexDemo(int Position, EBindingMode BindingMode)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));
	        
			CLogData				LogData=new CLogData(new CLog(true,"TCP",@"..\..\..\..\Logs\Test.txt"),"TCP",true);
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractDuplex");
			Uri						CBA=new Uri("net.tcp://localhost:4000");
			CLCBinding				Binding=new CLCBinding(LogData,BindingMode,Position,CBA);

			using(ServiceHost Svc=new ServiceHost(typeof(CDuplexReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractDuplex), Binding, Address);
				Svc.Open();

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				// Kvoli callback.
				InstanceContext		InstanceContext=new InstanceContext(new CCallbackType());

				using(CMyDuplexProxy Proxy=new CMyDuplexProxy(InstanceContext, Binding, new EndpointAddress(Address)))
				{
					string	Text;

					Console.WriteLine("Write MESSAGE BODY, or EMPTY LINE for EXIT and CLOSE PROXY !");

					while((Text=Console.ReadLine())!="")
						Proxy.SomeOperation(Text);

					Proxy.Close();
				}

				Console.WriteLine("Press any key to CLOSE SERVICE !");
				Console.ReadLine();

				Svc.Close();
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingDuplexSessionDemo(int Position, EBindingMode BindingMode)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));
	        
			CLogData				LogData=new CLogData(new CLog(true,"TCP",@"..\..\..\..\Logs\Test.txt"),"TCP",true);
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractDuplexSession");
			Uri						CBA=new Uri("net.tcp://localhost:4000");
			CLCBinding				Binding=new CLCBinding(LogData,BindingMode,Position,CBA);

			using(ServiceHost Svc=new ServiceHost(typeof(CDuplexSessionReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractDuplexSession), Binding, Address);
				Svc.Open();

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				while(true)
				{
					// Kvoli callback.
					InstanceContext		InstanceContext=new InstanceContext(new CCallbackType());

					using(CMyDuplexSessionProxy Proxy=new CMyDuplexSessionProxy(InstanceContext, Binding, new EndpointAddress(Address)))
					{
						string	Text;

						Console.WriteLine("Write MESSAGE BODY, or EMPTY LINE for EXIT and CLOSE PROXY !");

						while((Text=Console.ReadLine())!="")
						{
							Proxy.SomeOperation(Text);
							Proxy.SomeOtherOperation(Text);
						}

						Proxy.Close();
					}

					string	Line;

					Console.WriteLine("Dy you want to CONTINUE (Y\\N) ?");
					Line=Console.ReadLine();

					if (Line.Length==0 || Line.ToUpper()[0]!='Y')
						break;
				}

				Console.WriteLine("Press any key to CLOSE SERVICE !");
				Console.ReadLine();

				Svc.Close();
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingRequestResponseDemo(int Position, EBindingMode BindingMode)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));
	        
			CLogData				LogData=new CLogData(new CLog(true,"TCP",@"..\..\..\..\Logs\Test.txt"),"TCP",true);
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractRequestResponse");
			Uri						CBA=new Uri("net.tcp://localhost:4000");
			CLCBinding				Binding=new CLCBinding(LogData,BindingMode,Position,CBA);

			using(ServiceHost Svc=new ServiceHost(typeof(CRequestReplyReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractRequestReply), Binding, Address);
				Svc.Open();

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				using(CMyRequestReplyProxy Proxy=new CMyRequestReplyProxy(Binding, new EndpointAddress(Address)))
				{
					string	Text;

					Console.WriteLine("Write MESSAGE BODY, or EMPTY LINE for EXIT and CLOSE PROXY !");

					while((Text=Console.ReadLine())!="")
						Proxy.SomeOperation(Text);
				}

				Console.WriteLine("Press any key to CLOSE SERVICE !");
				Console.ReadLine();

				Svc.Close();
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingRequestResponseSessionDemo(int Position, EBindingMode BindingMode)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));
	        
			CLogData				LogData=new CLogData(new CLog(true,"TCP",@"..\..\..\..\Logs\Test.txt"),"TCP",true);
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractRequestResponseSession");
			Uri						CBA=new Uri("net.tcp://localhost:4000");
			CLCBinding				Binding=new CLCBinding(LogData,BindingMode,Position,CBA);

			using(ServiceHost Svc=new ServiceHost(typeof(CRequestReplySessionReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractRequestReplySession), Binding, Address);
				Svc.Open();

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				using(CMyRequestReplySessionProxy Proxy=new CMyRequestReplySessionProxy(Binding, new EndpointAddress(Address)))
				{
					string	Text;

					Console.WriteLine("Write MESSAGE BODY, or EMPTY LINE for EXIT and CLOSE PROXY !");

					while((Text=Console.ReadLine())!="")
					{
						Proxy.SomeOperation(Text);
						Proxy.SomeOtherOperation(Text);
					}
				}

				Console.WriteLine("Press any key to CLOSE SERVICE !");
				Console.ReadLine();

				Svc.Close();
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingOneWayDemo(int Position, EBindingMode BindingMode)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));
	        
			CLogData				LogData=new CLogData(new CLog(true,"TCP",@"..\..\..\..\Logs\Test.txt"),"TCP",true);
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractOneWay");
			Uri						CBA=new Uri("net.tcp://localhost:4000");
			CLCBinding				Binding1=new CLCBinding(LogData,BindingMode,Position,CBA);
			CLCBinding				Binding2=new CLCBinding(LogData,BindingMode,Position,CBA);

			using(ServiceHost Svc=new ServiceHost(typeof(COneWayReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWay), Binding1, Address);
				Svc.Open();

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				using(CMyOneWayProxy Proxy=new CMyOneWayProxy(Binding2, new EndpointAddress(Address)))
				{
					Proxy.Open();

					string	Text;

					Console.WriteLine("Write MESSAGE BODY, or EMPTY LINE for EXIT and CLOSE PROXY !");

					while((Text=Console.ReadLine())!="")
						Proxy.SomeOperation(Text);
				}

				Console.WriteLine("Press any key to CLOSE SERVICE !");
				Console.ReadLine();

				Svc.Close();
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		private static void NetTcpBindingOneWaySessionDemo(int Position, EBindingMode BindingMode)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));
	        
			CLogData				LogData=new CLogData(new CLog(true,"TCP",@"..\..\..\..\Logs\Test.txt"),"TCP",true);
			Uri						Address=new Uri("net.tcp://localhost:4000/ISomeContractOneWaySession");
			Uri						CBA=new Uri("net.tcp://localhost:4000");
			CLCBinding				Binding=new CLCBinding(LogData,BindingMode,Position,CBA);

			using(ServiceHost Svc=new ServiceHost(typeof(COneWaySessionReceiver)))
			{
				Svc.AddServiceEndpoint(typeof(ISomeContractOneWaySession), Binding, Address);
				Svc.Open();

				Console.WriteLine("Press any key to RUN PROXY !");
				Console.ReadLine();

				using(CMyOneWaySessionProxy Proxy=new CMyOneWaySessionProxy(Binding, new EndpointAddress(Address)))
				{
					string	Text;

					Console.WriteLine("Write MESSAGE BODY, or EMPTY LINE for EXIT and CLOSE PROXY !");

					while((Text=Console.ReadLine())!="")
					{
						Proxy.SomeOperation(Text);
						Proxy.SomeOtherOperation(Text);
					}
				}

				Console.WriteLine("Press any key to CLOSE SERVICE !");
				Console.ReadLine();

				Svc.Close();
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//NetTcpBindingDuplexDemo(0,EBindingMode.Tcp);
			NetTcpBindingDuplexSessionDemo(0,EBindingMode.Tcp);
			//NetTcpBindingRequestResponseDemo(0,EBindingMode.Tcp);
			//NetTcpBindingRequestResponseSessionDemo(0,EBindingMode.Tcp);
			//NetTcpBindingOneWayDemo(0,EBindingMode.Tcp);
			//NetTcpBindingOneWaySessionDemo(0,EBindingMode.Tcp);

			// Bez reliability.
			//NetTcpBindingOneWayDemo(0,EBindingMode.Tcp);

			// S reliability.
			//NetTcpBindingOneWayDemo(0,EBindingMode.TcpRM);

			// So security.
			//NetTcpBindingOneWayDemo(0,EBindingMode.TcpRMSec);

			// So security - level .
			//NetTcpBindingOneWayDemo(4,EBindingMode.TcpRMSec);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------