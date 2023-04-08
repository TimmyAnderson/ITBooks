using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace AutoCompleteSessionCloseLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession, TransactionAutoCompleteOnSessionClose=true)]
	public class CAutoCompleteSessionCloseService : IAutoCompleteSessionCloseContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CAutoCompleteSessionCloseService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void DoTransaction(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void ThrowException()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			throw(new FaultException<Exception>(new Exception("BUG !!!"),new FaultReason("SOME BUG !!!")));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void FinishTransaction(string Value)
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
			// Tu uz moze byt aj pomala operacia, kedze k Commit dochadza este pred volanim Dispose().
			//Thread.Sleep(10000);

			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------