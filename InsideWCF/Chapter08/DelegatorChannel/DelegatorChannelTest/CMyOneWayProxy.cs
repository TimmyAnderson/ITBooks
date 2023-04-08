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
	internal sealed class CMyOneWayProxy : ClientBase<ISomeContractOneWay>, ISomeContractOneWay
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyOneWayProxy(Binding Binding, EndpointAddress Address)
			: base(Binding, Address)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractOneWay CreateChannel()
		{
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation(string Input)
		{
			CPrintHelper.Print("SENDER: ISomeContractOneWay !", "SomeOperation");

			base.Channel.SomeOperation(Input);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------