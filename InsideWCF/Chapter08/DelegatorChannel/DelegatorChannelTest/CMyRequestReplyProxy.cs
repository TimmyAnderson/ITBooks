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
	internal sealed class CMyRequestReplyProxy : ClientBase<ISomeContractRequestReply>, ISomeContractRequestReply
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyRequestReplyProxy(Binding Binding, EndpointAddress Address)
			: base(Binding, Address)
		{     
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractRequestReply CreateChannel()
		{
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation(string Input)
		{
			CPrintHelper.Print("SENDER: MyRequestReplyProxy !", "SomeOperation");

			string			RetVal=base.Channel.SomeOperation(Input);

			CPrintHelper.Print("SENDER: MyRequestReplyProxy !", string.Format("SomeOperation returned \"{0}\"", RetVal));

			return(RetVal);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------