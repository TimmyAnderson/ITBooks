using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerCallLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerCallClient
{
//-------------------------------------------------------------------------------------------------------
	public class CPerCall2Proxy : ClientBase<IPerCallContract2>, IPerCallContract2
	{
//-------------------------------------------------------------------------------------------------------
		public CPerCall2Proxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState GetState2()
		{
			Console.WriteLine(string.Format("CPerCall2Proxy.GetState2() called (ID: {0}) !",base.InnerChannel.SessionId));
			return(Channel.GetState2());
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState2(CState State)
		{
			Console.WriteLine(string.Format("CPerCall2Proxy.SetState2() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.SetState2(State);
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState2()
		{
			Console.WriteLine(string.Format("CPerCall2Proxy.PrintActualState2() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.PrintActualState2();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------