using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ServiceModel;
using System.ServiceModel.Activation;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace IISHostingFactoryService
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! Trieda HOST FACTORY je OZAJ VYUZIVANA - je to vidiet, ked vratim NULL, ze hned vyhlasi klient chybu, BOHUZIAL VSAK NEVIDIET DEBUG VYPISY, kedze tie asi bezia v Built-In Web Serveri a nepisu sa ??? do DEBUG OKNA.
	public class CCustomHostFactory : ServiceHostFactory
	{
//-------------------------------------------------------------------------------------------------------
		public override ServiceHostBase CreateServiceHost(string ConstructorString, Uri[] BaseAddresses)
		{
			System.Diagnostics.Debug.WriteLine("!!!!! CreateServiceHost() version 1 CALLED !");

			return(base.CreateServiceHost(ConstructorString,BaseAddresses));
		}
//-------------------------------------------------------------------------------------------------------
		protected override ServiceHost CreateServiceHost(Type ServiceType, Uri[] BaseAddresses)
		{
			System.Diagnostics.Debug.WriteLine("!!!!! CreateServiceHost() version 2 CALLED !");

			return(base.CreateServiceHost(ServiceType,BaseAddresses));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------