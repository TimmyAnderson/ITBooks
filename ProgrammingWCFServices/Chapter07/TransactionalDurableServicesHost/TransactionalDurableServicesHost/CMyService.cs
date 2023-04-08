using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.Transactions;
//-------------------------------------------------------------------------------------------------------
namespace TransactionalDurableServicesHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	// Nastavim aby sa State ukladal do TRANSACTIONAL PS.
	[DurableService(SaveStateInOperationTransaction=true)]
	[DataContract]
	public class CMyService : IMyService
	{
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		private string											MSomePersistentValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Zacina WF - NESMIE BYT TRANSAKCNA, inak by chyba transakcie zlikvidovala i STAV WF.
		[OperationBehavior(TransactionScopeRequired=true)]
		[TransactionFlow(TransactionFlowOption.NotAllowed)]
		public void StartWorkflow(string SomePersistentValue)
		{
			MSomePersistentValue=SomePersistentValue;

			Console.WriteLine(string.Format("StartWorkflow() - SomePersistentValue: [{0}] !",MSomePersistentValue));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true)]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		public void DoTransaction(string SomePersistentValue, bool CommitTransaction)
		{
			Console.WriteLine(string.Format("BEFORE SET - DoTransaction() - SomePersistentValue: [{0}] !",MSomePersistentValue));

			MSomePersistentValue=SomePersistentValue;

			Console.WriteLine(string.Format("AFTER SET - DoTransaction() - SomePersistentValue: [{0}] !",MSomePersistentValue));

			using(WCFPersistentStoreForWFEntities CO=new WCFPersistentStoreForWFEntities())
			{
				CustomTable			NewRecord=new CustomTable();

				NewRecord.SomeData=string.Format("[{0}] [{1}] !",MSomePersistentValue,DateTime.Now);

				CO.AddToCustomTable(NewRecord);

				if (CommitTransaction==true)
				{
					Console.WriteLine(string.Format("Data: [{0}] WILL be written to DB !",NewRecord.SomeData));

					CO.SaveChanges();
				}
				else
				{
					Console.WriteLine(string.Format("Data: [{0}] - TRANSACTION WILL BE ROLLBACKED !",NewRecord.SomeData));

					// Hodim EXCEPTION, aby TRANSAKCIA ZLYHALA.
					// !!!!! Kedze sa transakcia ROLLBACKNE, tak i STAV MSomePersistentValue sa VRATI NA HODNOTU PRED VOLANIM TEJTO OPERACIE.
					throw(new FaultException("SOME ERROR !"));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Konci WF - NESMIE BYT TRANSAKCNA, inak by chyba transakcie VRATILA STAV WF na HODNOTU PRED VOLANIM OPERACIE - a WF Instance, ktora je v DB by sa NEODSTRANILA z DB.
		[OperationBehavior(TransactionScopeRequired=true)]
		[TransactionFlow(TransactionFlowOption.NotAllowed)]
		public void FinishWorkflow()
		{
			Console.WriteLine(string.Format("FinishWorkflow() - SomePersistentValue: [{0}] !",MSomePersistentValue));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------