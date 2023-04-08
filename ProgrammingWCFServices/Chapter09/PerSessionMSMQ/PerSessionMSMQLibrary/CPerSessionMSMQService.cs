using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionMSMQLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CPerSessionMSMQService : IPerSessionMSMQContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static int										MCounter;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CPerSessionMSMQService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
        public void TransactionStart(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Transaction					T=Transaction.Current;

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Message,T);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
        public void TransactionFinishAuto(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Transaction					T=Transaction.Current;

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Message,T);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
        public void TransactionFinishManual(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Transaction					T=Transaction.Current;

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_2,Message,T);

			// Urobim COMMIT.
			OperationContext.Current.SetTransactionComplete();

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=false)]
        public void FailTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Transaction					T=Transaction.Current;

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Message,T);

			if (MCounter++<3)
				throw(new Exception("ERROR !!!"));

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void NonTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
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