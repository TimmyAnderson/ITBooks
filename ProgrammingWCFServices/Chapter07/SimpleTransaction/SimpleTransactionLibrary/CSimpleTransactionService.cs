using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace SimpleTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CSimpleTransactionService : ISimpleTransactionContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleTransactionService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void OneDBTwoTables(string Value)
		{
			// Aj ked zapisuje sa do tej istej DB tak sa jedna o distrubovanu transakciu.

			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TwoDBOneTableInEach(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_2,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TwoDBOneTableInEachExcplicitVoting(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_2,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			// Vote za Commit().
			OperationContext.Current.SetTransactionComplete();

			// Tu uz nesmie byt ziadna operacia nad transakciou.

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
		public void TwoDBOneTableInEachExcplicitVotingWithException(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			try
			{
				Transaction					T=Transaction.Current;

				Console.WriteLine(CDebugHelper.GetTransactionString(T));
				CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
				Console.WriteLine(CDebugHelper.GetTransactionString(T));
				CTransactionHelper.InsertValue(EDBID.E_DI_DB_2,ETableID.E_TI_TABLE_1,Value,T);
				Console.WriteLine(CDebugHelper.GetTransactionString(T));

				// Hodim vynimku, takze sa SetTransactionComplete() nezavola.
				throw(new FaultException<Exception>(new Exception("BUG !!!")));

				// Vote za Commit().
				//OperationContext.Current.SetTransactionComplete();

				// Tu uz nesmie byt ziadna operacia nad transakciou.

				//Console.WriteLine(CDebugHelper.GetTransactionString(T));
			}
			catch
			{
				// !!!!!! Excpetion musim poslat dalej - NESMIEM JU CHYTIT, inak transakcia OSTANE VYSIET.
				throw;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void TwoDBOneTableInEachWithException(string Value)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Transaction					T=Transaction.Current;

			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_2,ETableID.E_TI_TABLE_1,Value,T);
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			throw(new FaultException<Exception>(new Exception("BUG !!!")));
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