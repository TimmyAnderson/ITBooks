using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace TransactionFlowLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CTransactionFlowBService : ITransactionFlowBContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CTransactionFlowBService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dummy()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
		}
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
			// Pisem do 2. DB.
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_2,ETableID.E_TI_TABLE_2,Value,T);
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
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFImplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TFImplicitVotingWithException(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			throw(new FaultException<Exception>(new Exception("BUG !!!"),new FaultReason("BUG")));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			OperationContext.Current.SetTransactionComplete();
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVotingWithEnd(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			throw(new FaultException<Exception>(new Exception("BUG !!!"),new FaultReason("BUG")));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVotingStartTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_2,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TFExplicitVotingEndTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_2,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			OperationContext.Current.SetTransactionComplete();
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