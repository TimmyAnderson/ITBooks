using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
// Priklad demonstruje ako si mozem vytvorit vlastne proxy respektujuc dedicsku hierarchiu contracts.
// Vyuizva techniku hierarchie, kde implementuje 2 proxy, kde kazde je proxy voci danemu contracts.
// Na rozdiel od techniky chain, vsak proxy nie su vzajomne dedene.
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceHierarchyProxyClient
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

			// Mam 2 contracty a 2 proxy. Obe mzem pouzivat separatne.
			CSimpleCalculatorProxy				SimpleCalculatorProxy=null;
			CScientificCalculatorProxy			ScientificCalculatorProxy=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding1=new NetTcpBinding();
			Binding								TCPBinding2=new NetTcpBinding();

			try
			{
				// !!! Mozno na adresu. Kedze server vystavuje iba jeden endpoint tak je ROVNAKA.
				SimpleCalculatorProxy=new CSimpleCalculatorProxy(TCPBinding1,"net.tcp://localhost:9001/IScientificCalculatorContract");
				ScientificCalculatorProxy=new CScientificCalculatorProxy(TCPBinding2,"net.tcp://localhost:9001/IScientificCalculatorContract");

				Console.WriteLine(String.Format("SimpleCalculatorProxy.Add(): {0} !",SimpleCalculatorProxy.Add(10,33)));
				Console.WriteLine(String.Format("ScientificCalculatorProxy.Add(): {0} !",ScientificCalculatorProxy.Add(10,33)));
				Console.WriteLine(String.Format("ScientificCalculatorProxy.Multiply(): {0} !",ScientificCalculatorProxy.Multiply(10,33)));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (SimpleCalculatorProxy!=null)
				{
					SimpleCalculatorProxy.Close();
					SimpleCalculatorProxy=null;
				}

				if (ScientificCalculatorProxy!=null)
				{
					ScientificCalculatorProxy.Close();
					ScientificCalculatorProxy=null;
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