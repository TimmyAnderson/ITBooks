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
namespace EHExtensionCallbackClient
{
//-------------------------------------------------------------------------------------------------------
	[AttributeUsage(AttributeTargets.Class)]
	public class CMyErrorHandlerBehaviorAttribute : Attribute, IEndpointBehavior, IErrorHandler
	{
//-------------------------------------------------------------------------------------------------------
		public void AddBindingParameters(ServiceEndpoint Endpoint, BindingParameterCollection BindingParameters)
		{
			// Prazdna.
			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.AddBindingParameters() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ApplyClientBehavior(ServiceEndpoint Endpoint, ClientRuntime ClientRuntime)
		{
			ClientRuntime.CallbackDispatchRuntime.ChannelDispatcher.ErrorHandlers.Add(this);

			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.ApplyClientBehavior() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ApplyDispatchBehavior(ServiceEndpoint Endpoint, EndpointDispatcher EndpointDispatcher)
		{
			// Prazdna.
			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.ApplyDispatchBehavior() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void Validate(ServiceEndpoint Endpoint)
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
			// Tento kod zachyti kazdu vyniku a transformuje ju na zabuzdrenu excepion cez FaultException<InvalidOperationException> a tym padom VZDY BUDE NA KLIENT PRENESENA KOREKTNA FaultException<Exception> EXCEPTION A NEDOJDE K UZATOVRENIU CALLBACK PROXY.

			FaultException<InvalidOperationException>	FaultException=new FaultException<InvalidOperationException>(new InvalidOperationException(Error.Message));
			MessageFault								MessageFault=FaultException.CreateMessageFault();

			// Naplnenie ref parametra.
			Fault=Message.CreateMessage(Version, MessageFault, FaultException.Action);

			Console.WriteLine("CMyErrorHandlerBehaviorAttribute.ProvideFault() called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------