using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
using LCChannel;
using Log;
//-------------------------------------------------------------------------------------------------------
// 1. NET.TCP bezi iba na Duplex Session. Na ostatnych Shapes nebezi.
// 2. WS-HTTP bezi iba na Duplex Session a Datagram Session. Na ostatnych Shapes nebezi.
// 3. NET.PIPE bezi iba na Duplex Session. Na ostatnych Shapes nebezi.
// 4. BASIC-HTTP bezi iba na Request & Response. Na ostatnych Shapes nebezi.
// 5. !!!!! Ak pri Duplex MEP ak RAZ HODI Receive(TimeSpan) TimeoutException TAK JE CH FAULTED A NEDA SA VIAC POUZIT. !!!!! ??? Podla na je to preto, lebo Duplex znamena objosmernu komunikaciu a ked ta na jednej strane lahne tak sa spojenie rozpadne.
// 6. V Request-Reply MEP to NEVADI a TimeoutException neznamena prechod CH do FAULTED stavu.
// 7. ??? !!! Vyzera to, ze ked uzatvaram Duplex CH tak nesmiem mat ZIADNU NESPRACOVANU M. Teda M, ktora uz dosla ale ja som ju cez Receive() este nespracoval. Inak Close() hodi Exception.
// 8. ??? !!! Vyzera to, ze ked sa uzatvara na strane Sender Duplex CH tak na strane Receiver() sa vrati M s hodnotou null aby sa mohla korektne Receive() skoncit. Verzia Receive s TimeSpan sa neda pouzit, lebo po preteceni TimeSpan sa dostane CH do FAULTED state.
//-------------------------------------------------------------------------------------------------------
namespace BindingTest
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void TestBasicHTTPBinding1()
		{
//			Uri									A=new Uri("net.pipe://MyListener");
//			Uri									A=new Uri("http://localhost:4000/MyListener");
			Uri									A=new Uri("net.tcp://localhost:4000/MyListener");
//			NetNamedPipeBinding					B1=new NetNamedPipeBinding();
//			NetNamedPipeBinding					B2=new NetNamedPipeBinding();
//			BasicHttpBinding					B1=new BasicHttpBinding();
//			BasicHttpBinding					B2=new BasicHttpBinding();
			NetTcpBinding						B1=new NetTcpBinding();
			NetTcpBinding						B2=new NetTcpBinding();
//			WSDualHttpBinding					B1=new WSDualHttpBinding();
//			WSDualHttpBinding					B2=new WSDualHttpBinding();


//			CMessageReceiver<IDuplexChannel>		MR=new CMessageReceiver<IDuplexChannel>(A,B1);
//			CMessageSender<IDuplexChannel>			MS=new CMessageSender<IDuplexChannel>(A,B2);
//			CMessageReceiver<IReplyChannel>			MR=new CMessageReceiver<IReplyChannel>(A,B1);
//			CMessageSender<IRequestChannel>			MS=new CMessageSender<IRequestChannel>(A,B2);
//			CMessageReceiver<IInputChannel>			MR=new CMessageReceiver<IInputChannel>(A,B1);
//			CMessageSender<IOutputChannel>			MS=new CMessageSender<IOutputChannel>(A,B2);

			CMessageReceiver<IDuplexSessionChannel>	MR=new CMessageReceiver<IDuplexSessionChannel>(A,B1);
			CMessageSender<IDuplexSessionChannel>	MS=new CMessageSender<IDuplexSessionChannel>(A,B2);
//			CMessageReceiver<IReplySessionChannel>	MR=new CMessageReceiver<IReplySessionChannel>(A,B1);
//			CMessageSender<IRequestSessionChannel>	MS=new CMessageSender<IRequestSessionChannel>(A,B2);
//			CMessageReceiver<IInputSessionChannel>	MR=new CMessageReceiver<IInputSessionChannel>(A,B1);
//			CMessageSender<IOutputSessionChannel>	MS=new CMessageSender<IOutputSessionChannel>(A,B2);

			// Pri Dupex MEP je toto zle, kedze urobim hned Close().
			// Hodilo mi to vynikmu v tom zmysle, ze nemsiem urobit Close(), ked este cakam prijem dalsich M.
			// ??? Vyzera to, ze pri Duplex musim zatvarat az ked mam istotu konca komunikacie, co sa nestalo, lebo sa este posielala Repsonse. Pri Request-Response MEP to nevadilo, tu ano. ??? Je to asi dane povahou CH, kde pri Duplex su viac menej nezavisle.
			/*
			MR.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.Start();

			MS.SendMessage("Hello WCF !");

			MS.Stop();

			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MR.Stop();
			*/


			MR.Start();
			MS.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.SendMessage("Hello WCF !");

			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MS.Stop();
			MR.Stop();


			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void TestBasicHTTPBinding2()
		{
			Uri									A=new Uri("http://localhost:4000/MyListener");
			BasicHttpBinding					B1=new BasicHttpBinding();
			BasicHttpBinding					B2=new BasicHttpBinding();

			CMessageReceiver<IReplyChannel>			MR=new CMessageReceiver<IReplyChannel>(A,B1);
			CMessageSender<IRequestChannel>			MS=new CMessageSender<IRequestChannel>(A,B2);

			// Pri Dupex MEP je toto zle, kedze urobim hned Close().
			// Hodilo mi to vynimku v tom zmysle, ze nemsiem urobit Close(), ked este cakam prijem dalsich M.
			// ??? Vyzera to, ze pri Duplex musim zatvarat az ked mam istotu konca komunikacie, co sa nestalo, lebo sa este posielala Repsonse. Pri Request-Response MEP to nevadilo, tu ano. ??? Je to asi dane povahou CH, kde pri Duplex su viac menej nezavisle.
			/*
			MR.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.Start();

			MS.SendMessage("Hello WCF !");

			MS.Stop();

			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MR.Stop();
			*/


			MR.Start();
			MS.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.SendMessage("Hello WCF !");

			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MS.Stop();
			MR.Stop();


			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void TestNETTCPBinding()
		{
			Uri									A=new Uri("net.tcp://localhost:4000/MyListener");
			NetTcpBinding						B1=new NetTcpBinding();
			NetTcpBinding						B2=new NetTcpBinding();

			CMessageReceiver<IDuplexSessionChannel>	MR=new CMessageReceiver<IDuplexSessionChannel>(A,B1);
			CMessageSender<IDuplexSessionChannel>	MS=new CMessageSender<IDuplexSessionChannel>(A,B2);


			MR.Start();
			MS.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.SendMessage("Hello WCF !");

			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MS.Stop();
			MR.Stop();


			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void TestCLBinding()
		{
			CLogData							LogData1=new CLogData(new CLog(true,"XXX 1",@"..\..\..\..\Logs\Test.txt"),"Receiver",true);
			CLogData							LogData2=new CLogData(new CLog(true,"XXX 2",@"..\..\..\..\Logs\Test.txt"),"Sender",true);
			Uri									A=new Uri("http://localhost:4000/MyListener");
			Uri									CBA=new Uri("http://localhost:4000");
			CLCBinding							B1=new CLCBinding(LogData1,EBindingMode.BasicHttp,0,CBA);
			CLCBinding							B2=new CLCBinding(LogData2,EBindingMode.BasicHttp,0,CBA);
			CMessageReceiver<IReplyChannel>		MR=new CMessageReceiver<IReplyChannel>(A,B1);
			CMessageSender<IRequestChannel>		MS=new CMessageSender<IRequestChannel>(A,B2);

			MR.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.Start();

			MS.SendMessage("Hello WCF !");

			MS.Stop();

			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MR.Stop();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void TestCLBindingDatagramShape()
		{
			CLogData							LogData1=new CLogData(new CLog(true,"XXX 1",@"..\..\..\..\Logs\Test.txt"),"Receiver",true);
			CLogData							LogData2=new CLogData(new CLog(true,"XXX 2",@"..\..\..\..\Logs\Test.txt"),"Sender",true);
			Uri									A=new Uri("http://localhost:4000/MyListener");
			Uri									CBA=new Uri("http://localhost:4000");
			CLCBinding							B1=new CLCBinding(LogData1,EBindingMode.WSHttp,0,CBA);
			CLCBinding							B2=new CLCBinding(LogData2,EBindingMode.WSHttp,0,CBA);
			CMessageReceiver<IInputChannel>		MR=new CMessageReceiver<IInputChannel>(A,B1);
			CMessageSender<IOutputChannel>		MS=new CMessageSender<IOutputChannel>(A,B2);

			MR.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.Start();

			MS.SendMessage("Hello WCF !");

			MS.Stop();

			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MR.Stop();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void TestCLBindingDuplexShape()
		{
			CLogData									LogData1=new CLogData(new CLog(true,"XXX 1",@"..\..\..\..\Logs\Test.txt"),"Receiver",true);
			CLogData									LogData2=new CLogData(new CLog(true,"XXX 2",@"..\..\..\..\Logs\Test.txt"),"Sender",true);
			Uri											A=new Uri("net.tcp://localhost:4000/MyListener");
			Uri											CBA=new Uri("net.tcp://localhost:4000");
			CLCBinding									B1=new CLCBinding(LogData1,EBindingMode.Tcp,1,CBA);
			CLCBinding									B2=new CLCBinding(LogData2,EBindingMode.Tcp,1,CBA);
			CMessageReceiver<IDuplexSessionChannel>		MR=new CMessageReceiver<IDuplexSessionChannel>(A,B1);
			CMessageSender<IDuplexSessionChannel>		MS=new CMessageSender<IDuplexSessionChannel>(A,B2);

			MR.Start();
			MS.Start();

			Console.WriteLine("Press any key to SEND MESSAGE !");
			Console.ReadLine();

			MS.SendMessage("Hello WCF !");


			Console.WriteLine("Press any key to stop service !");
			Console.ReadLine();

			MS.Stop();
			MR.Stop();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//TestBasicHTTPBinding1();
			//TestBasicHTTPBinding2();
			//TestNETTCPBinding();
			//TestCLBinding();
			//TestCLBindingDatagramShape();
			TestCLBindingDuplexShape();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------