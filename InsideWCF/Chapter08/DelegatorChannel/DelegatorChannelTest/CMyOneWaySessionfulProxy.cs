using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using DelegatorChannel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannelTest
{
//-------------------------------------------------------------------------------------------------------
	internal sealed class CMyOneWaySessionfulProxy : ClientBase<ISomeContractOneWaySession>, ISomeContractOneWaySession
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyOneWaySessionfulProxy(Binding Binding, EndpointAddress Address)
			: base(Binding, Address)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractOneWaySession CreateChannel()
		{
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation(string Input)
		{
			CPrintHelper.Print("SENDER: ISomeContractOneWaySession !", "SomeOperation");

			base.Channel.SomeOperation(Input);
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOtherOperation(string Input)
		{
			CPrintHelper.Print("SENDER: ISomeContractOneWaySession !", "SomeOtherOperation");

			base.Channel.SomeOtherOperation(Input);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------