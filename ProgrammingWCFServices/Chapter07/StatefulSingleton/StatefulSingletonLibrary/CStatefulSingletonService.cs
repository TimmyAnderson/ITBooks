using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Transactions;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace StatefulSingletonLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single,ReleaseServiceInstanceOnTransactionComplete=false, ConcurrencyMode=ConcurrencyMode.Multiple)]
	public class CStatefulSingletonService : IStatefulSingletonContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private string											MValue="NONE";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CStatefulSingletonService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void DoTransaction(string Value)
		{
			Console.WriteLine(string.Format("BEFORE {0} - Value: {1} !",CDebugHelper.GetMethodCallString(),MValue));

			MValue=Value;

			Console.WriteLine(string.Format("AFTER {0} - Value: {1} !",CDebugHelper.GetMethodCallString(),MValue));

			Transaction					T=Transaction.Current;

			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
		}
//-------------------------------------------------------------------------------------------------------
		public void NonTransaction()
		{
			Console.WriteLine(string.Format("{0} - Value: {1} !",CDebugHelper.GetMethodCallString(),MValue));
			MValue="NON TRANSACTION";
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(string.Format("!!! {0} - Value: {1} !",CDebugHelper.GetDestructorCallString(),MValue));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------