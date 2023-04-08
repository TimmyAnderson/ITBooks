using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Transactions;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace TransactionProtocolService
{
//-------------------------------------------------------------------------------------------------------
	public class CTransactionProtocol : ITransactionProtocol
	{
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		public void DoTransaction(string Value)
		{
			Console.WriteLine("DoTransaction() CALLED !");

			Transaction					T=Transaction.Current;

			CTransactionHelper.InsertValue(EDBID.E_DI_DB_1,ETableID.E_TI_TABLE_1,Value,T);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------