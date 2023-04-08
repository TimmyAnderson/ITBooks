using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel.Dispatcher;
using System.Diagnostics;
//--------------------------------------------------------------------------------------------------------
namespace InterceptorShared
{
//--------------------------------------------------------------------------------------------------------
	public abstract class GenericInvoker : IOperationInvoker
	{
//--------------------------------------------------------------------------------------------------------
		// Ulozim si povodny interceptor, ktory vyvolava samotnu operaciu.
		private readonly IOperationInvoker						MOldInvoker;
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
		public GenericInvoker(IOperationInvoker OldInvoker)
		{
			Debug.Assert(OldInvoker!=null);

			MOldInvoker=OldInvoker;
		}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
		public bool												IsSynchronous
		{
			get
			{
				return(MOldInvoker.IsSynchronous);
			}
		}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
		public virtual object[] AllocateInputs()
		{
			return(MOldInvoker.AllocateInputs());
		}
//--------------------------------------------------------------------------------------------------------
		protected virtual void PreInvoke(object Instance, object[] Inputs)
		{
		}
//--------------------------------------------------------------------------------------------------------
		protected virtual void PostInvoke(object instance,object ReturnedValue, object[] Outputs, Exception Exception)
		{
		}
//--------------------------------------------------------------------------------------------------------
		public object Invoke(object Instance, object[] Inputs, out object[] Outputs)
		{
			PreInvoke(Instance,Inputs);
		 
			object				ReturnedValue=null;
			object[]			OutputParams=new object[]{};
			Exception			Exception=null;
		 
			try
			{
				ReturnedValue=MOldInvoker.Invoke(Instance,Inputs,out OutputParams);
				Outputs=OutputParams;
				return(ReturnedValue);
			}
			catch(Exception OperationException)
			{
				Exception=OperationException;
				throw; 
			}
			finally
			{
				PostInvoke(Instance,ReturnedValue,OutputParams,Exception);
			}
		}
//--------------------------------------------------------------------------------------------------------
		public IAsyncResult InvokeBegin(object Instance, object[] Inputs, AsyncCallback Callback, object State)
		{
			PreInvoke(Instance,Inputs);
			return(MOldInvoker.InvokeBegin(Instance,Inputs,Callback,State));
		}
//--------------------------------------------------------------------------------------------------------
		public object InvokeEnd(object Instance, out object[] Outputs, IAsyncResult Result)
		{
			object				ReturnedValue=null;
			object[]			OutputParams={};
			Exception			Exception=null;

			try
			{
				ReturnedValue=MOldInvoker.InvokeEnd(Instance,out Outputs,Result);
				Outputs=OutputParams;
				return(ReturnedValue);
			}
			catch(Exception OperationException)
			{
				Exception=OperationException;
				throw; 
			}
			finally
			{
				PostInvoke(Instance,ReturnedValue,OutputParams,Exception);
			}
		}
//--------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------