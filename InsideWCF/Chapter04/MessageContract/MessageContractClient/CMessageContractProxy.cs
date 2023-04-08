using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MessageContractLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MessageContractClient
{
//-------------------------------------------------------------------------------------------------------
	public class CMessageContractProxy : ClientBase<IMessageContractContract>, IMessageContractContract
	{
//-------------------------------------------------------------------------------------------------------
		public CMessageContractProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeDCOperation(CMyDataContract MyDataContract)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SomeDCOperation(MyDataContract);
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeMCOperation(CMyMessageContract MyMessageContract)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.SomeMCOperation(MyMessageContract);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------