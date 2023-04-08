using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleMSMQClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSimpleMSMQProxy : ClientBase<ISimpleMSMQLibraryContract>, ISimpleMSMQLibraryContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleMSMQProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintText(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.PrintText(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowException(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ThrowException(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------