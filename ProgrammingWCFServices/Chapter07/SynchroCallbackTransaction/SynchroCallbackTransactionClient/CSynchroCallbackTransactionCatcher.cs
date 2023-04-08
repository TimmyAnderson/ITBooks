using System;
using System.Collections.Generic;
using System.Text;
using System.Transactions;
using System.ServiceModel;
using TransactionHelper;
using SynchroCallbackTransactionLibrary;
//-------------------------------------------------------------------------------------------------------
namespace SynchroCallbackTransactionClient
{
//-------------------------------------------------------------------------------------------------------
	class CSynchroCallbackTransactionCatcher : ISynchroCallbackTransactionCallback
	{
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true)]
		public void OnCallback(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			// Start transaction.
			Transaction					T=Transaction.Current;

			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Message,T);

			T=Transaction.Current;
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------