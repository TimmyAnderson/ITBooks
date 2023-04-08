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
namespace PerCallMSMQLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CPerCallMSMQService : IPerCallMSMQContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		static private int										MCounter;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CPerCallMSMQService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void PrintText(string Message)
		{
			MCounter=0;

			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=false)]
        public void ThrowException(string Message)
		{
			MCounter=0;

			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));

			throw(new Exception("SOME ERROR !"));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
        public void PrintTextWithTransaction(string Message)
		{
			MCounter=0;

			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Transaction					T=Transaction.Current;

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Message,T);

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
        public void ThrowExceptionWithTransaction(string Message)
		{
			MCounter++;

			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			Transaction					T=Transaction.Current;

			Console.WriteLine(string.Format("{0}: {1} !",CDebugHelper.GetMethodCallString(),Message));
			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Message,T);

			// !!! Sprava sa opakuje 6 krat. Potom sa sice vlozi spet do frony, ale znova ak sa spusti service tak sa pokusi ju vykonat.
			if (MCounter<=3)
				throw(new Exception("SOME ERROR !"));

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