using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using System.ServiceModel.Channels;
using EHExtensionHostLibrary;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionHostService
{
//-------------------------------------------------------------------------------------------------------
	public class CMyHost : ServiceHost
	{
//-------------------------------------------------------------------------------------------------------
		public CMyHost(Type ServiceType)
			: base(ServiceType)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpening()
		{
			Console.WriteLine("CMyHost.OnOpening() called !");

			// !!! Tu prihodim vlastny EH.
			IServiceBehavior		MyErrorHandlerBehaviorAttribute=new CMyErrorHandlerBehaviorAttribute();

			Description.Behaviors.Add(MyErrorHandlerBehaviorAttribute);

			base.OnOpening();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------