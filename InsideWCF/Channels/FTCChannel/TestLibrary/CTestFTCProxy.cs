using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.ServiceModel.Description;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TestLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CTestFTCProxy : ClientBase<ITestFTCContract>, ITestFTCContract
	{
//-------------------------------------------------------------------------------------------------------
		public CTestFTCProxy(InstanceContext InstanceContext, Binding Binding, EndpointAddress Address)
			: base(InstanceContext, Binding, Address)
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override ITestFTCContract CreateChannel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(base.CreateChannel());
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation_BEGIN(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			return(base.Channel.SomeOperation_BEGIN(Input));
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation_MIDDLE(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			return(base.Channel.SomeOperation_MIDDLE(Input));
		}
//-------------------------------------------------------------------------------------------------------
		public string SomeOperation_END(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			return(base.Channel.SomeOperation_END(Input));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowException(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			base.Channel.ThrowException(Input);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------