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
	public class CPerCall1Proxy : ClientBase<IPerCallContract1>, IPerCallContract1
	{
//-------------------------------------------------------------------------------------------------------
		public CPerCall1Proxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState GetState1()
		{
			Console.WriteLine(string.Format("CPerCall1Proxy.GetState1() called (ID: {0}) !",base.InnerChannel.SessionId));
			return(Channel.GetState1());
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState1(CState State)
		{
			Console.WriteLine(string.Format("CPerCall1Proxy.SetState1() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.SetState1(State);
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState1()
		{
			Console.WriteLine(string.Format("CPerCall1Proxy.PrintActualState1() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.PrintActualState1();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------