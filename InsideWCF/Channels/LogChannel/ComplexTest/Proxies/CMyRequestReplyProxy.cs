using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using LCChannel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace ComplexTest
{
//-------------------------------------------------------------------------------------------------------
	internal sealed class CMyRequestReplyProxy : ClientBase<ISomeContractRequestReply>, ISomeContractRequestReply
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyRequestReplyProxy(Binding Binding, EndpointAddress Address)
			: base(Binding, Address)
		{     
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractRequestReply CreateChannel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			string			RetVal=base.Channel.SomeOperation(Input);

			Console.WriteLine(CDebugHelper.GetMethodCallString() + " RetVal: " + RetVal);

			return(RetVal);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------