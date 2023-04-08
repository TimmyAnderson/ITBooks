using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransactionalQueueLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TransactionalQueueClient
{
//-------------------------------------------------------------------------------------------------------
	public class CTransactionalQueueProxy : ClientBase<ITransactionalQueueContract>, ITransactionalQueueContract
	{
//-------------------------------------------------------------------------------------------------------
		public CTransactionalQueueProxy(Binding ProxyBinding, string EndpointAddress)
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
		public void PrintTextWithTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.PrintTextWithTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowExceptionWithTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.ThrowExceptionWithTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------