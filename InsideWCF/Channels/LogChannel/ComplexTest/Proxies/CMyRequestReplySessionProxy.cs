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
	internal sealed class CMyRequestReplySessionProxy : ClientBase<ISomeContractRequestReplySession>, ISomeContractRequestReplySession
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyRequestReplySessionProxy(Binding Binding, EndpointAddress Address)
			: base(Binding, Address)
		{     
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractRequestReplySession CreateChannel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			string			RetVal=base.Channel.SomeOperation(Input);

			Console.WriteLine(CDebugHelper.GetMethodCallString() + "RetVal: " + RetVal);

			return(RetVal);
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOtherOperation(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			string			RetVal=base.Channel.SomeOtherOperation(Input);

			Console.WriteLine(CDebugHelper.GetMethodCallString() + " RetVal: " + RetVal);

			return(RetVal);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------