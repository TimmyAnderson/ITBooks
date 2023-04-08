using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransactionFlowLibrary;
//-------------------------------------------------------------------------------------------------------
namespace TransactionFlowClient
{
//-------------------------------------------------------------------------------------------------------
	public class CTransactionFlowAProxy : ClientBase<ITransactionFlowAContract>, ITransactionFlowAContract
	{
//-------------------------------------------------------------------------------------------------------
		public CTransactionFlowAProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dummy()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.Dummy();
		}
//-------------------------------------------------------------------------------------------------------
		public void TFAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFAllowed(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFNotAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFNotAllowed(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFMandatory(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFMandatory(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFImplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFImplicitVoting(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFImplicitVotingWithException(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFImplicitVotingWithException(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFExplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFExplicitVoting(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFExplicitVotingWithEnd(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFExplicitVotingWithEnd(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFExplicitVotingStartTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFExplicitVotingStartTransaction(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TFExplicitVotingEndTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TFExplicitVotingEndTransaction(Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------