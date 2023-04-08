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
	internal sealed class CMyDuplexProxy : ClientBase<ISomeContractDuplex>, ISomeContractDuplex
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyDuplexProxy(InstanceContext InstanceContext, Binding Binding, EndpointAddress Address)
			: base(InstanceContext, Binding, Address)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractDuplex CreateChannel()
		{
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation(string Input)
		{
			CPrintHelper.Print("SENDER: ISomeContractDuplex !", "SomeOperation");

			base.Channel.SomeOperation(Input);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------