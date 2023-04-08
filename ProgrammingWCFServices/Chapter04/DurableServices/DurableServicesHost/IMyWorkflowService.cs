using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DurableServicesHost
{
//-------------------------------------------------------------------------------------------------------
	// SessionMode NESMIE byt na 'NotAllowed'.
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface IMyWorkflowService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void SetFirstName(string FirstName);
		[OperationContract]
		void SetLastName(string LastName);
		[OperationContract]
		void PrintFullNameAndFinishWFByAttribute();
		[OperationContract]
		void PrintFullNameAndFinishWFByCode();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------