using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace ClientTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CClientTransactionService : IClientTransactionContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CClientTransactionService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFNotAllowed(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFMandatory(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------