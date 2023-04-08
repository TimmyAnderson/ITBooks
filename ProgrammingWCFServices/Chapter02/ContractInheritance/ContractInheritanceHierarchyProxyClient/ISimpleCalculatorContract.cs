using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
// Regenerovany base contract pre potreby proxy.
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceHierarchyProxyClient
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ISimpleCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int Add(int Param1, int Param2);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------