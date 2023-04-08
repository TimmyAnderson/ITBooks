using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SimpleTransactionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SimpleTransactionClient
{
//-------------------------------------------------------------------------------------------------------
	public class CSimpleTransactionProxy : ClientBase<ISimpleTransactionContract>, ISimpleTransactionContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleTransactionProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void OneDBTwoTables(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.OneDBTwoTables(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TwoDBOneTableInEach(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TwoDBOneTableInEach(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TwoDBOneTableInEachExcplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TwoDBOneTableInEachExcplicitVoting(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TwoDBOneTableInEachExcplicitVotingWithException(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TwoDBOneTableInEachExcplicitVotingWithException(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void TwoDBOneTableInEachWithException(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.TwoDBOneTableInEachWithException(Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------