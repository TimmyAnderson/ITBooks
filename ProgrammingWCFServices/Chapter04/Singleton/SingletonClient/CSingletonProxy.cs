using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SingletonLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SingletonClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSingletonProxy : ClientBase<ISingletonContract>, ISingletonContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSingletonProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState GetState()
		{
			Console.WriteLine(string.Format("CSingletonProxy.GetState() called (ID: {0}) !",base.InnerChannel.SessionId));
			return(Channel.GetState());
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState(CState State)
		{
			Console.WriteLine(string.Format("CSingletonProxy.SetState() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.SetState(State);
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState()
		{
			Console.WriteLine(string.Format("CSingletonProxy.PrintActualState() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.PrintActualState();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------