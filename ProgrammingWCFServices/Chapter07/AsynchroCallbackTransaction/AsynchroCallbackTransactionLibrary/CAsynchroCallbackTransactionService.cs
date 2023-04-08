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
namespace AsynchroCallbackTransactionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CAsynchroCallbackTransactionService : IAsynchroCallbackTransactionContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static CClientList<IAsynchroCallbackTransactionCallback>	MClientList=new CClientList<IAsynchroCallbackTransactionCallback>();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CAsynchroCallbackTransactionService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void LaunchEvent(object Param)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			CPair<string, int>		Pair=(CPair<string, int>) Param;

			Thread.Sleep(Pair.Second);

			using(TransactionScope S=new TransactionScope())
			{
				// Start transaction.
				Transaction					T=Transaction.Current;

				CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Pair.First,T);

				T=Transaction.Current;
				Console.WriteLine(CDebugHelper.GetTransactionString(T));

				// Callback finishes transaction.
				MClientList.OnCallback(Pair.First);

				T=Transaction.Current;
				Console.WriteLine(CDebugHelper.GetTransactionString(T));

				S.Complete();
			}

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Connect(string ClientName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			MClientList.Add(new CClientListItem<IAsynchroCallbackTransactionCallback>(OperationContext.Current.GetCallbackChannel<IAsynchroCallbackTransactionCallback>(),ClientName));
		}
//-------------------------------------------------------------------------------------------------------
        public void Disconnect()
        {
			Console.WriteLine(CDebugHelper.GetMethodCallString());
            MClientList.Remove(OperationContext.Current.GetCallbackChannel<IAsynchroCallbackTransactionCallback>());
        }
//-------------------------------------------------------------------------------------------------------
        public void DoTransaction(string Message, int Timeout)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			// Spusti sa NOVY THREAD, ktory realizuje DB OPERATION ASYNCHRONNE.
			Thread		T=new Thread(new ParameterizedThreadStart(LaunchEvent));

			T.Start(new CPair<string, int>(Message, Timeout));

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