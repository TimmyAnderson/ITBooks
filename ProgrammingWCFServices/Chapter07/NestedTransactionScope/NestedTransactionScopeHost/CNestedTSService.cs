using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace NestedTransactionScopeHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CNestedTSService : INestedTSService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void DoTransaction(string SomeValue, bool ShouldVote)
		{
			using(WCFPersistentStoreForWFEntities CO=new WCFPersistentStoreForWFEntities())
			{
				CustomTable			NewRecord=new CustomTable();

				NewRecord.SomeData=string.Format("[{0}] [{1}] !",SomeValue, DateTime.Now);

				CO.AddToCustomTable(NewRecord);

				if (ShouldVote==true)
				{
					Console.WriteLine(string.Format("Data: [{0}] WILL be written to DB !",NewRecord.SomeData));

					CO.SaveChanges();
				}
				// NEPOTRVDIM TRANSAKCIU - skonci ROLLBACK.
				else
					Console.WriteLine(string.Format("Data: [{0}] - TRANSACTION WILL BE ROLLBACKED !",NewRecord.SomeData));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------