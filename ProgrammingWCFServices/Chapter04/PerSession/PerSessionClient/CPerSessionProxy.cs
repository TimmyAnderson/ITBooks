using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerSessionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionClient
{
//-------------------------------------------------------------------------------------------------------
	public class CPerSessionProxy : ClientBase<IPerSessionContract>, IPerSessionContract
	{
//-------------------------------------------------------------------------------------------------------
		public CPerSessionProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState GetState()
		{
			Console.WriteLine(string.Format("CPerSessionProxy.GetState() called (ID: {0}) !",base.InnerChannel.SessionId));
			return(Channel.GetState());
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState(CState State)
		{
			Console.WriteLine(string.Format("CPerSessionProxy.SetState() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.SetState(State);
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState()
		{
			Console.WriteLine(string.Format("CPerSessionProxy.PrintActualState() called (ID: {0}) !",base.InnerChannel.SessionId));
			Channel.PrintActualState();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------