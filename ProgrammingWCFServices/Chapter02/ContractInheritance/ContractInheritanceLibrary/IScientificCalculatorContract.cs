using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
// Contract zdedeny z ISimpleCalculatorContract.
// Demonstruje dedicnost contracts.
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceLibrary
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