using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CallbackContractHierarchyLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Klucova podmienka je aby ICallbackContractHierarchyCallback2 bol zdedeney z ICallbackContractHierarchyCallback1. Inak hodi WCF chybu.
	[ServiceContract]
	public interface ICallbackContractHierarchyCallback2 : ICallbackContractHierarchyCallback1
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void OnCallback2(string MessagePart1, string MessagePart2);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------