using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionReleaseInstanceOnCompleteLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IPerSessionReleaseInstanceOnCompleteContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void PrintSessionID();
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.NotAllowed)]
		void NoTransaction(string Value);
		[OperationContract]
		[TransactionFlow(TransactionFlowOption.Allowed)]
		void DoTransaction(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------