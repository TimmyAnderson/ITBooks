using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.ServiceModel;
using ClientHelper;
using TransactionHelper;
//-------------------------------------------------------------------------------------------------------
namespace SynchroCallbackTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall, ConcurrencyMode=ConcurrencyMode.Reentrant, ReleaseServiceInstanceOnTransactionComplete=false)]
	public class CSynchroCallbackTransactionService : ISynchroCallbackTransactionContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static CClientList<ISynchroCallbackTransactionCallback>	MClientList=new CClientList<ISynchroCallbackTransactionCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSynchroCallbackTransactionService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			MClientList.Add(new CClientListItem<ISynchroCallbackTransactionCallback>(OperationContext.Current.GetCallbackChannel<ISynchroCallbackTransactionCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine(CDebugHelper.GetMethodCallString());
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<ISynchroCallbackTransactionCallback>());
        }
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true)]
        public void DoTransaction(string Message)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			// Start transaction.
			Transaction					T=Transaction.Current;

			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Message,T);

			T=Transaction.Current;
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

			// Callback finishes transaction.
			MClientList.OnCallback(Message);

			T=Transaction.Current;
			Console.WriteLine(CDebugHelper.GetTransactionString(T));

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