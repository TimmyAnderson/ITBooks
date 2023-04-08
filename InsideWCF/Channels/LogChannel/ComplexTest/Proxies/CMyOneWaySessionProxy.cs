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
	internal sealed class CMyOneWaySessionProxy : ClientBase<ISomeContractOneWaySession>, ISomeContractOneWaySession
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyOneWaySessionProxy(Binding Binding, EndpointAddress Address)
			: base(Binding, Address)
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractOneWaySession CreateChannel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			base.Channel.SomeOperation(Input);
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOtherOperation(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			base.Channel.SomeOtherOperation(Input);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------