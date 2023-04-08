using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using InstanceDeactivationLibrary;
//-------------------------------------------------------------------------------------------------------
namespace InstanceDeactivationClient
{
//-------------------------------------------------------------------------------------------------------
	public class CInstanceDeactivationProxy : ClientBase<IInstanceDeactivationContract>, IInstanceDeactivationContract
	{
//-------------------------------------------------------------------------------------------------------
		public CInstanceDeactivationProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
		public void StartSession(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationProxy.StartSession() called (Value: {0}) !",Value));
			Channel.StartSession(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void BeforeCall(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationProxy.BeforeCall() called (Value: {0}) !",Value));
			Channel.BeforeCall(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void AfterCall(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationProxy.AfterCall() called (Value: {0}) !",Value));
			Channel.AfterCall(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void BeforeAndAfterCall(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationProxy.BeforeAndAfterCall() called (Value: {0}) !",Value));
			Channel.BeforeAndAfterCall(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualRelease(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationProxy.ManualRelease() called (Value: {0}) !",Value));
			Channel.ManualRelease(Value);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------