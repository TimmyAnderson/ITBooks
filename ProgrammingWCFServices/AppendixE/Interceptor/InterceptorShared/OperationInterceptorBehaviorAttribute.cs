using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel.Dispatcher;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
//--------------------------------------------------------------------------------------------------------
namespace InterceptorShared
{
//--------------------------------------------------------------------------------------------------------
	// Implementacie Invoker ako OPERATION BEHAVIOR.
	[AttributeUsage(AttributeTargets.Method)]
	public abstract class OperationInterceptorBehaviorAttribute : Attribute,IOperationBehavior
	{
//--------------------------------------------------------------------------------------------------------
		protected abstract GenericInvoker CreateInvoker(IOperationInvoker OldInvoker);
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
		public void AddBindingParameters(OperationDescription OperationDescription, BindingParameterCollection BindingParameters)
		{
		}
//--------------------------------------------------------------------------------------------------------
		public void ApplyClientBehavior(OperationDescription OperationDescription, ClientOperation ClientOperation)
		{
		}
//--------------------------------------------------------------------------------------------------------
		public void ApplyDispatchBehavior(OperationDescription OperationDescription, DispatchOperation DispatchOperation)
		{
			IOperationInvoker			OldInvoker=DispatchOperation.Invoker;

			DispatchOperation.Invoker=CreateInvoker(OldInvoker);

			Console.WriteLine(string.Format("OPERATION Behavior applied to: {0}",OperationDescription.Name));
		}
//--------------------------------------------------------------------------------------------------------
		public void Validate(OperationDescription OperationDescription)
		{
		}
//--------------------------------------------------------------------------------------------------------
   }
//--------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------