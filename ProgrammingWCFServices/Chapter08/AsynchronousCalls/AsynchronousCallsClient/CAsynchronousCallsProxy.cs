using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using AsynchronousCallsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousCallsClient
{
//-------------------------------------------------------------------------------------------------------
	public class CAsynchronousCallsProxy : ClientBase<IAsynchronousCallsContractProxy>, IAsynchronousCallsContractProxy
	{
//-------------------------------------------------------------------------------------------------------
		public CAsynchronousCallsProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.IsAlive();
		}
//-------------------------------------------------------------------------------------------------------
		public string SlowMethod(string Message, ref string RefMessage, out string OutMessage)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(Channel.SlowMethod(Message, ref RefMessage, out OutMessage));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSlowMethod(string Message, ref string RefMessage, AsyncCallback Callback, object AsyncState)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(Channel.BeginSlowMethod(Message, ref RefMessage, Callback, AsyncState));
		}
//-------------------------------------------------------------------------------------------------------
		public string EndSlowMethod(ref string RefMessage, out string OutMessage, IAsyncResult Result)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(Channel.EndSlowMethod(ref RefMessage, out OutMessage, Result));
		}
//-------------------------------------------------------------------------------------------------------
		public void SlowMethodWithException(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SlowMethodWithException(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSlowMethodWithException(string Message,AsyncCallback Callback,object AsyncState)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(Channel.BeginSlowMethodWithException(Message, Callback, AsyncState));
		}
//-------------------------------------------------------------------------------------------------------
		public void EndSlowMethodWithException(IAsyncResult Result)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.EndSlowMethodWithException(Result);
		}
//-------------------------------------------------------------------------------------------------------
		public void SlowMethodWithUnexpectedException(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SlowMethodWithUnexpectedException(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSlowMethodWithUnexpectedException(string Message,AsyncCallback Callback,object AsyncState)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(Channel.BeginSlowMethodWithUnexpectedException(Message, Callback, AsyncState));
		}
//-------------------------------------------------------------------------------------------------------
		public void EndSlowMethodWithUnexpectedException(IAsyncResult Result)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.EndSlowMethodWithUnexpectedException(Result);
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginServerAsynchroSlowMethod(string Message, AsyncCallback CB, object AS)
		{
			return(Channel.BeginServerAsynchroSlowMethod(Message,CB,AS));
		}
//-------------------------------------------------------------------------------------------------------
		public string EndServerAsynchroSlowMethod(IAsyncResult AR)
		{
			return(Channel.EndServerAsynchroSlowMethod(AR));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------