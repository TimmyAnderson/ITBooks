using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using Contracts;
//-------------------------------------------------------------------------------------------------------
namespace Receiver
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="Receiver";

			BasicHttpBinding			Binding2=new BasicHttpBinding();
			BindingElementCollection	Col=Binding2.CreateBindingElements();
			CustomBinding				Binding=new CustomBinding(Col);
			Uri							Address=new Uri("http://localhost:4000/IRestraurantService");
			ServiceHost					Svc=new ServiceHost(typeof(CReceiver));

			Svc.AddServiceEndpoint(typeof(IRestaurantService3), Binding, Address);
			Svc.Open();

			Console.WriteLine("The receiver is ready - press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------