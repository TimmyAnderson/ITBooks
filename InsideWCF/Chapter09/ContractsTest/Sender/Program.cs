using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
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
			Console.Title="Sender";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			BasicHttpBinding					Binding2=new BasicHttpBinding();
			BindingElementCollection			Col=Binding2.CreateBindingElements();
			TextMessageEncodingBindingElement	Text=Col.Find<TextMessageEncodingBindingElement>();
			CustomBinding						Binding=new CustomBinding(Col);
			EndpointAddress						Address=new EndpointAddress("http://localhost:4000/IRestraurantService");
			ChannelFactory<IRestaurantService3> Factory=new ChannelFactory<IRestaurantService3>(Binding, Address);
			IRestaurantService3					Proxy=Factory.CreateChannel();

			try
			{
				Console.WriteLine("Sending message to the receiver !");

				Proxy.ChangeReservation(new CChangeReservationNewDateTime(5, DateTime.Now));
			}
			catch(FaultException<CChangeReservationFault> Ex)
			{
				Console.WriteLine(Ex.Message);
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------