using System;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Reflection;
using System.Collections.Generic;
//-------------------------------------------------------------------------------------------------------
namespace ShowBindingElements
{
//-------------------------------------------------------------------------------------------------------
	internal sealed class ShowBindingElements
	{
//-------------------------------------------------------------------------------------------------------
		private static void OutputBindingElements(List<Binding> Bindings)
		{
			foreach(Binding Binding in Bindings)
			{
				Console.WriteLine("Showing Binding Elements for [{0}] !", Binding.GetType().Name);

				// Metoda CreateBindingElements() vytvori SORTOVANU kolekciu BE.
				// !!! Prave poradie BE je KLUCOVE pre vytvaranie stacku.
				foreach(BindingElement Element in Binding.CreateBindingElements())
					Console.WriteLine("\t{0} !", Element.GetType().Name);

				Console.WriteLine();
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main()
		{
			List<Binding>	Bindings=new List<Binding>();

			Bindings.Add(new BasicHttpBinding());
			Bindings.Add(new NetTcpBinding());
			Bindings.Add(new NetTcpBinding(SecurityMode.Message, true));
			Bindings.Add(new WSHttpBinding());
			Bindings.Add(new NetMsmqBinding());
			Bindings.Add(new NetMsmqBinding(NetMsmqSecurityMode.Message));

			// throws if Peer Networking not installed
			//Bindings.Add(new NetPeerTcpBinding());

			OutputBindingElements(Bindings);

			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------