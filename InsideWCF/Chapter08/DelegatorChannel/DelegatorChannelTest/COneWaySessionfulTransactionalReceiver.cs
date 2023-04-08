using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using DelegatorChannel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannelTest
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	internal sealed class COneWaySessionfulTransactionalReceiver : ISomeContractOneWaySession
	{
//-------------------------------------------------------------------------------------------------------
		internal COneWaySessionfulTransactionalReceiver()
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWaySessionfulTransactionalReceiver !", "ctor");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true, TransactionAutoComplete=false)]
		public void SomeOperation(string Input)
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWaySessionfulTransactionalReceiver !", string.Format("SomeOperation: {0}", Input));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(TransactionScopeRequired=true, TransactionAutoComplete=true)]
		public void SomeOtherOperation(string Input)
		{
			CPrintHelper.Print("RECEIVER OBJECT: OneWaySessionfulTransactionalReceiver !", String.Format("SomeOtherOperation: {0}", Input));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------