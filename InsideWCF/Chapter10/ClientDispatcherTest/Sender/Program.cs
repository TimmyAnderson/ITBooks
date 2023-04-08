using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Remoting;
using Contracts;
//-------------------------------------------------------------------------------------------------------
namespace Sender
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

			// Instantiate a binding.
			BasicHttpBinding					Binding=new BasicHttpBinding();

			// Create an EndpointAddress.
			EndpointAddress						Address=new EndpointAddress("http://localhost:4000/MyListener");

			// Instantiate a ChannelFactory, passing binding and EndpointAddress.
			ChannelFactory<IRestaurantService3>	Factory=new ChannelFactory<IRestaurantService3>(Binding, Address);
	        
			// Create the client infastructure.
			IRestaurantService3					Client=Factory.CreateChannel();
			bool								Trans=RemotingServices.IsTransparentProxy(Client);

			Console.WriteLine(string.Format("IsTransparentProxy: [{0}] !", Trans));

			// Invoke a method on the client, and retrieve the result.
			int?								Result=Client.RequestReservation(new CRequestReservationParams(DateTime.Now, "Dusty's BBQ", "Justin Smith"));

			Console.WriteLine(string.Format("RETURNED VALUE: [{0}] !",Result));

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------