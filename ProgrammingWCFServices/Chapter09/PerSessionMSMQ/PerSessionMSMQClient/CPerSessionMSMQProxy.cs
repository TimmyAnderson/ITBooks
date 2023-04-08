using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerSessionMSMQLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionMSMQClient
{
//-------------------------------------------------------------------------------------------------------
	public class CPerSessionMSMQProxy : ClientBase<IPerSessionMSMQContract>, IPerSessionMSMQContract
	{
//-------------------------------------------------------------------------------------------------------
		public CPerSessionMSMQProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void TransactionStart(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TransactionStart(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void TransactionFinishAuto(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TransactionFinishAuto(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void TransactionFinishManual(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TransactionFinishManual(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void FailTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.FailTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public void NonTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.NonTransaction(Message);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------