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
	internal sealed class CMyDuplexProxy : ClientBase<ISomeContractDuplex>, ISomeContractDuplex
	{
//-------------------------------------------------------------------------------------------------------
		internal CMyDuplexProxy(InstanceContext InstanceContext, Binding Binding, EndpointAddress Address)
			: base(InstanceContext, Binding, Address)
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ISomeContractDuplex CreateChannel()
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------