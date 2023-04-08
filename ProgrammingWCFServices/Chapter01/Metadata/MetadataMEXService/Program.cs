using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace MetadataMEXService
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				using (ServiceHost SH=new ServiceHost(typeof(CToUpperService)))
				{
					ServiceMetadataBehavior		SMB=new ServiceMetadataBehavior();

					// Pridam do Behaviors ServiceMetadataBehavior.
					SH.Description.Behaviors.Add(SMB);

					/*
					// Vytvorim CustomBinding s TcpTransportBindingElement.
					// !!!!! CustomBinding MUSI mat TRANSPORT BINDING ELEMENT prislusnej Schema, cez ktoru chcem MEX vystavit.
					// Tu som sa rozhodol pre TCP a tak som zvolil TcpTransportBindingElement.
					// !!!!! Ziadne ine BINDING ELEMENTS NIE SU POTREBNE - staci TRANSPORT.
					BindingElement				BE=new TcpTransportBindingElement();
					CustomBinding				B=new CustomBinding(BE);
					*/

					// !!! Alternativa voci EXPLICITNEMU VYTVARANIU CustomBinding je pouzitie HELPER metoda CreateMexTcpBinding() vytvori TCP MEX CUSTOM BINDING.
					Binding						B=MetadataExchangeBindings.CreateMexTcpBinding();

					// Vytvorim MEX Endpoint - pouzijem relativnu adresu.
					SH.AddServiceEndpoint(typeof(IMetadataExchange),B,"MEX");

					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
					
					SH.Close();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------