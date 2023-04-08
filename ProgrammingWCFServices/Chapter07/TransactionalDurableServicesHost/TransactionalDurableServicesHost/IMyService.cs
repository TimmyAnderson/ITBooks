using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace TransactionalDurableServicesHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IMyService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[DurableOperation(CanCreateInstance=true,CompletesInstance=false)]
		void StartWorkflow(string SomePersistentValue);
		[OperationContract]
		[DurableOperation(CanCreateInstance=false,CompletesInstance=false)]
		void DoTransaction(string SomePersistentValue, bool CommitTransaction);
		[OperationContract]
		[DurableOperation(CanCreateInstance=false,CompletesInstance=true)]
		void FinishWorkflow();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------