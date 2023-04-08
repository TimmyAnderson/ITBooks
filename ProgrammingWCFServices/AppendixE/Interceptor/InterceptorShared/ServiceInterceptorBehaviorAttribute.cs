using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Dispatcher;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
using System.Collections.ObjectModel;
//--------------------------------------------------------------------------------------------------------
namespace InterceptorShared
{
//--------------------------------------------------------------------------------------------------------
	// Implementacie Invoker ako SERVICE BEHAVIOR.
	[AttributeUsage(AttributeTargets.Class)]
	public abstract class ServiceInterceptorBehaviorAttribute : Attribute,IServiceBehavior
	{
//--------------------------------------------------------------------------------------------------------
		protected abstract OperationInterceptorBehaviorAttribute CreateOperationInterceptor();
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
		public void ApplyDispatchBehavior(ServiceDescription ServiceDescription, ServiceHostBase Host)
		{
			// Prechadzam KAZDY ENDPOINT.
			foreach(ServiceEndpoint Endpoint in ServiceDescription.Endpoints)
			{
				// Prechadzam KAZDU OPERATION.
				foreach(OperationDescription Operation in Endpoint.Contract.Operations)
				{
					// Ak UZ NA OPERATION JE APLIKOVANY behavior, tak ho NEAPLIKUJEM ZNOVA.
					if(Operation.Behaviors.Find<OperationInterceptorBehaviorAttribute>()!=null)
						continue;

					// Inak aplikujem OPERATION BEHAVIOR na danu OPERATION.
					Operation.Behaviors.Add(CreateOperationInterceptor());

					Console.WriteLine(string.Format("SERVICE Behavior applied to: {0}",Operation.Name));
				}
			}
		}
//--------------------------------------------------------------------------------------------------------
	  public void AddBindingParameters(ServiceDescription ServiceDescription, ServiceHostBase ServiceHostBase, Collection<ServiceEndpoint> Endpoints, BindingParameterCollection BindingParameters)
	  {
	  }
//--------------------------------------------------------------------------------------------------------
	  public void Validate(ServiceDescription ServiceDescription, ServiceHostBase ServiceHostBase)
	  {
	  }
//--------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------