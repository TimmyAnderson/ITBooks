using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Security.Permissions;
using System.Security;
using System.Net;
using System.Diagnostics;
using System.ServiceModel.Description;
using System.Reflection;
using System.ServiceModel.Dispatcher;
//-------------------------------------------------------------------------------------------------------
namespace InterceptorShared
{
//-------------------------------------------------------------------------------------------------------
	public class ClientInterceptor<T> : IEndpointBehavior,IClientMessageInspector where T : class
	{
//-------------------------------------------------------------------------------------------------------
		 InterceptorClientBase<T>								Proxy
		 {
			 get;
			 set;
		 }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal ClientInterceptor(InterceptorClientBase<T> Proxy)
		{
			this.Proxy=Proxy;
		}
//-------------------------------------------------------------------------------------------------------
		object IClientMessageInspector.BeforeSendRequest(ref Message Request, IClientChannel Channel)
		{
			Proxy.PreInvoke(ref Request);
			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		void IClientMessageInspector.AfterReceiveReply(ref Message Reply,object CorrelationState)
		{
			Proxy.PostInvoke(ref Reply);
		}
//-------------------------------------------------------------------------------------------------------
		void IEndpointBehavior.ApplyClientBehavior(ServiceEndpoint Endpoint, ClientRuntime ClientRuntime)
		{
			ClientRuntime.MessageInspectors.Add(this);
		}
//-------------------------------------------------------------------------------------------------------
		void IEndpointBehavior.AddBindingParameters(ServiceEndpoint Endpoint, BindingParameterCollection BindingParameters)
		{
		}
//-------------------------------------------------------------------------------------------------------
		void IEndpointBehavior.ApplyDispatchBehavior(ServiceEndpoint Endpoint, EndpointDispatcher EndpointDispatcher)
		{
		}
//-------------------------------------------------------------------------------------------------------
		void IEndpointBehavior.Validate(ServiceEndpoint Endpoint)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------