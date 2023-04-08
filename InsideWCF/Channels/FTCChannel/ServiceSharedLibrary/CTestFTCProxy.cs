using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.ServiceModel.Description;
using FTCSharedLibrary;
//-----------------------------------------------------------------------------
namespace ServiceSharedLibrary
{
//-----------------------------------------------------------------------------
	internal sealed class CTestFTCProxy : ClientBase<ITestFTCContract>, ITestFTCContract
	{
//-----------------------------------------------------------------------------
		internal CTestFTCProxy(InstanceContext InstanceContext, Binding Binding, EndpointAddress Address)
			: base(InstanceContext, Binding, Address)
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		protected override ITestFTCContract CreateChannel()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			return(base.CreateChannel());
		}
//-----------------------------------------------------------------------------
		public void SomeOperation_BEGIN(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			base.Channel.SomeOperation_BEGIN(Input);
		}
//-----------------------------------------------------------------------------
		public void SomeOperation_MIDDLE(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			base.Channel.SomeOperation_MIDDLE(Input);
		}
//-----------------------------------------------------------------------------
		public void SomeOperation_END(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			base.Channel.SomeOperation_END(Input);
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------