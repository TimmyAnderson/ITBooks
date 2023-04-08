using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFChannelProxyClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CHelloWorldProxy					HelloWorldProxy=null;
			CThrowExceptionProxy				ThrowExceptionProxy=null;
			CIntGetSetProxy						IntGetSetProxy=null;
			CStringGetSetProxy					StringGetSetProxy=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBindingS1C1=new NetTcpBinding();
			Binding								TCPBindingS1C2=new NetTcpBinding();
			Binding								TCPBindingS2C1=new NetTcpBinding();
			Binding								TCPBindingS2C2=new NetTcpBinding();

			try
			{
				HelloWorldProxy=new CHelloWorldProxy(TCPBindingS1C1,"net.tcp://localhost:9001/IHelloWorldContract");
				ThrowExceptionProxy=new CThrowExceptionProxy(TCPBindingS1C2,"net.tcp://localhost:9001/IThrowExceptionContract");
				IntGetSetProxy=new CIntGetSetProxy(TCPBindingS2C1,"net.tcp://localhost:9002/IIntGetSetContract");
				StringGetSetProxy=new CStringGetSetProxy(TCPBindingS2C2,"net.tcp://localhost:9002/IStringGetSetContract");

				HelloWorldProxy.Open();
				ThrowExceptionProxy.Open();
				IntGetSetProxy.Open();
				StringGetSetProxy.Open();

				// Vyzera, ze stav sa zacohvava v ramci volania metod jedneho contract.
				// Ale samzorejme nie ak volam metody dvoch contract aj ked su obe implementovane jedinym objektom. Pretoze jednak to nie je mozne - contacty nezdielaju jednu rozhranie takze nemozem cez proxy jednoho volat metodu ineho a jednak WCF vytvori 2 isntancie. Teda pre azdy contract jednu instanciu objektu na servri.
				// O jeho zivotvnosti ani to ci stav je perzistetny zatia nic neviem, takze sa nato neda spolahnut.
				IntGetSetProxy.SetIntValue(100);
				Console.WriteLine(String.Format("GetIntValue(): {0} !",IntGetSetProxy.GetIntValue()));

				StringGetSetProxy.SetStringValue("XYZ");
				Console.WriteLine(String.Format("GetStringValue(): {0} !",StringGetSetProxy.GetStringValue()));

				HelloWorldProxy.SayHelloWorld("ABC");

				try
				{
					ThrowExceptionProxy.ThrowException();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("ThrowException() returns exception: {0} !",E.Message));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (IntGetSetProxy!=null)
				{
					IntGetSetProxy.Close();
					IntGetSetProxy=null;
				}

				if (StringGetSetProxy!=null)
				{
					StringGetSetProxy.Close();
					StringGetSetProxy=null;
				}

				if (HelloWorldProxy!=null)
				{
					HelloWorldProxy.Close();
					HelloWorldProxy=null;
				}

				try
				{
					// Vyzera, ze ked hodi server Exception tak sa dostane proxy do Faulted state a uz nejde ani zatvorit.
					if (ThrowExceptionProxy!=null)
					{
						ThrowExceptionProxy.Close();
						ThrowExceptionProxy=null;
					}
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("Exception: {0} !",E.Message));
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------