using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Dispatcher;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
//--------------------------------------------------------------------------------------------------------
namespace InterceptorSharedHost
{
//--------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface INameService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		// Aplikujem Operation Behavior.
		[OperationParameterTracerAttribute]
		CFullName GetFullName(string FirstName, string LastName, int Age);
		[OperationContract]
		// !!!!! TU NEAPLIKUJEM Operation Behavior, ale aplikuje sa nan Service Behavior.
		string GetFirstName(CFullName FullName);
		[OperationContract]
		string JustThrowException(string Name);
//--------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------