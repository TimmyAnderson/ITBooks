using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionHostLibrary
{
//-------------------------------------------------------------------------------------------------------
	[AttributeUsage(AttributeTargets.Class)]
	public class CMyErrorHandlerBehaviorAttribute : Attribute, IServiceBehavior, IErrorHandler
	{
//-------------------------------------------------------------------------------------------------------
		public void AddBindingParameters(ServiceDescription ServiceDescription, ServiceHostBase ServiceHostBase, Collection<ServiceEndpoint> Endpoints, BindingParameterCollection BindingParameters)
		{
			// Prazdna.
			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.AddBindingParameters() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ApplyDispatchBehavior(ServiceDescription ServiceDescription, ServiceHostBase Host)
		{
			foreach(ChannelDispatcher Dispatcher in Host.ChannelDispatchers)
			{
				Dispatcher.ErrorHandlers.Add(this);
			}

			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.ApplyDispatchBehavior() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Validate(ServiceDescription serviceDescription,ServiceHostBase serviceHostBase)
		{
			// Prazdna.
			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.Validate() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public bool HandleError(Exception Error)
		{
			// Iba vypis na konozlu.
			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.HandleError() called !");

			Console.WriteLine(string.Format("HandleError(): {0} !",Error.Message));

			// Navratova hodnota urcuje ci sa aj dalsi IErrorHandler ak ho service obsahuje pouzije, alebo bude tento posledny.
			// true - nepokracuj.
			// false - pokracuj.
			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public void ProvideFault(Exception Error, MessageVersion Version, ref Message Fault)
		{
			// Tento kod zachyti kazdu vyniku a transformuje ju na zabuzdrenu excepion cez FaultException<ObjectDisposedException> a tym padom VZDY BUDE NA KLIENT PRENESENA KOREKTNA FaultException<ObjectDisposedException> EXCEPTION A NEDOJDE K UZATOVRENIU PROXY.

			FaultException<ObjectDisposedException>	FaultException=new FaultException<ObjectDisposedException>(new ObjectDisposedException(Error.Message));
			MessageFault							MessageFault=FaultException.CreateMessageFault();

			// Naplnenie ref paametra.
			Fault=Message.CreateMessage(Version, MessageFault, FaultException.Action);

			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.ProvideFault() called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------