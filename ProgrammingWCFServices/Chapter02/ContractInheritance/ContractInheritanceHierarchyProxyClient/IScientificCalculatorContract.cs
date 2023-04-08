using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
// Regenerovany derived contract pre potreby proxy.
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceHierarchyProxyClient
{
//-------------------------------------------------------------------------------------------------------
	// Aj zdedeny interface musi mat [ServiceContract], kedze ten nema aplikovanu automaticku dedicnost.
	[ServiceContract]
	public interface IScientificCalculatorContract : ISimpleCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int Multiply(int Param1, int Param2);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------