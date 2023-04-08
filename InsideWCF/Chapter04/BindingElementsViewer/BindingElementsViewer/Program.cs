using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.MsmqIntegration;
//-------------------------------------------------------------------------------------------------------
namespace BindingElementsViewer
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void ShowBindingElements(List<Binding> Bindings)
		{
			foreach (Binding B in Bindings)
			{
				Console.WriteLine("Showing Binding Elements for {0} !", B.GetType().Name);

				// Vytvori zoznam elementov.
				foreach (BindingElement Element in B.CreateBindingElements())
					Console.WriteLine("\t{0}", Element.GetType().Name);

				Console.WriteLine();
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			List<Binding>		Bindings = new List<Binding>();

			Bindings.Add(new BasicHttpBinding());
			Bindings.Add(new NetNamedPipeBinding());
			Bindings.Add(new NetTcpBinding());
			Bindings.Add(new WSDualHttpBinding());
			Bindings.Add(new WSHttpBinding());
			Bindings.Add(new NetMsmqBinding());
			Bindings.Add(new MsmqIntegrationBinding());
			Bindings.Add(new WSFederationHttpBinding());

			// Hodi Excpetion ak Peer Networking nie je instalovany.
			//Bindings.Add(new NetPeerTcpBinding());

			ShowBindingElements(Bindings);

			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------