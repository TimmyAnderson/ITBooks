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
	public class InterceptorClientBase<T> : ClientBase<T> where T : class
	{
//-------------------------------------------------------------------------------------------------------
		public InterceptorClientBase() 
		{
			Endpoint.Behaviors.Add(new ClientInterceptor<T>(this));
		}
//-------------------------------------------------------------------------------------------------------
		public InterceptorClientBase(string EndpointName)
			: base(EndpointName)
		{
			Endpoint.Behaviors.Add(new ClientInterceptor<T>(this));
		}
//-------------------------------------------------------------------------------------------------------
		public InterceptorClientBase(string EndpointName, string RemoteAddress)
			: base(EndpointName,RemoteAddress)
		{
			Endpoint.Behaviors.Add(new ClientInterceptor<T>(this));
		}
//-------------------------------------------------------------------------------------------------------
		public InterceptorClientBase(string EndpointName, EndpointAddress RemoteAddress)
			: base(EndpointName,RemoteAddress)
		{
			Endpoint.Behaviors.Add(new ClientInterceptor<T>(this));
		}
//-------------------------------------------------------------------------------------------------------
		public InterceptorClientBase(Binding Binding, EndpointAddress RemoteAddress)
			: base(Binding,RemoteAddress)
		{
			Endpoint.Behaviors.Add(new ClientInterceptor<T>(this));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal protected virtual void PreInvoke(ref Message Request)
		{
		}
//-------------------------------------------------------------------------------------------------------
		internal protected virtual void PostInvoke(ref Message Reply)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------