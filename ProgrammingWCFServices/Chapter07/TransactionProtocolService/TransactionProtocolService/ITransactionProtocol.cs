using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace TransactionProtocolService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ITransactionProtocol
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void DoTransaction(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------