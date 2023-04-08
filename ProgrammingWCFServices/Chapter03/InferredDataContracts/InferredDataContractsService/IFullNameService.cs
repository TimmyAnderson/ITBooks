using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace InferredDataContractsService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IFullNameService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CInferredFullName GetFullName(string FirstName, string LastName, int Age);
		[OperationContract]
		CInferredFullNameDerived GetFullNameDerived(string FirstName, string LastName, int Age, string SomeInfo);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------