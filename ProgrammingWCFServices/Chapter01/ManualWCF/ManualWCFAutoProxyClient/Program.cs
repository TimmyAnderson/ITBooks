using System;
using System.Collections.Generic;
using System.Text;
using ManualWCFAutoProxyClient.CGetSetProxy;
using ManualWCFAutoProxyClient.CHelloWorldProxy;
//-------------------------------------------------------------------------------------------------------
namespace ManualWCFAutoProxyClient
{
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			HelloWorldContractClient			HelloWorldContract=null;
			ThrowExceptionContractClient		ThrowExceptionContract=null;
			IntGetSetContractClient				IntGetSetContract=null;
			StringGetSetContractClient			StringGetSetContract=null;

			try
			{
				IntGetSetContract=new IntGetSetContractClient("NetTcpBinding_IIntGetSetContract");
				StringGetSetContract=new StringGetSetContractClient("NetTcpBinding_IStringGetSetContract");
				HelloWorldContract=new HelloWorldContractClient("NetTcpBinding_IHelloWorldContract");
				ThrowExceptionContract=new ThrowExceptionContractClient("NetTcpBinding_IThrowExceptionContract");

				// Vyzera, ze stav sa zacohvava v ramci volania metod jedneho contract.
				// Ale samzorejme nie ak volam metody dvoch contract aj ked su obe implementovane jedinym objektom. Pretoze jednak to nie je mozne - contacty nezdielaju jednu rozhranie takze nemozem cez proxy jednoho volat metodu ineho a jednak WCF vytvori 2 isntancie. Teda pre azdy contract jednu instanciu objektu na servri.
				// O jeho zivotvnosti ani to ci stav je perzistetny zatia nic neviem, takze sa nato neda spolahnut.
				IntGetSetContract.SetIntValue(100);
				Console.WriteLine(String.Format("GetIntValue(): {0} !",IntGetSetContract.GetIntValue()));

				StringGetSetContract.SetStringValue("XYZ");
				Console.WriteLine(String.Format("GetStringValue(): {0} !",StringGetSetContract.GetStringValue()));

				HelloWorldContract.SayHelloWorld("ABC");

				try
				{
					ThrowExceptionContract.ThrowException();
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
				if (IntGetSetContract!=null)
				{
					IntGetSetContract.Close();
					IntGetSetContract=null;
				}

				if (StringGetSetContract!=null)
				{
					StringGetSetContract.Close();
					StringGetSetContract=null;
				}

				if (HelloWorldContract!=null)
				{
					HelloWorldContract.Close();
					HelloWorldContract=null;
				}

				try
				{
					// Vyzera, ze ked hodi server Exception tak sa dostane proxy do Faulted state a uz nejde ani zatvorit.
					if (ThrowExceptionContract!=null)
					{
						ThrowExceptionContract.Close();
						ThrowExceptionContract=null;
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