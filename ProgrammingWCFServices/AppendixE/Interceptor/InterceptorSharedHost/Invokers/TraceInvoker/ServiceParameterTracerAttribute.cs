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
using InterceptorShared;
//--------------------------------------------------------------------------------------------------------
namespace InterceptorSharedHost
{
//--------------------------------------------------------------------------------------------------------
	public class ServiceParameterTracerAttribute : ServiceInterceptorBehaviorAttribute
	{
//--------------------------------------------------------------------------------------------------------
		protected override OperationInterceptorBehaviorAttribute CreateOperationInterceptor()
		{
			return(new OperationParameterTracerAttribute());
		}
//--------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------