using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceHierarchyProxyClient
{
//-------------------------------------------------------------------------------------------------------
	class CScientificCalculatorProxy : ClientBase<IScientificCalculatorContract>, IScientificCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		public CScientificCalculatorProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int Add(int Param1,int Param2)
		{
			return(Channel.Add(Param1,Param2));
		}
//-------------------------------------------------------------------------------------------------------
		public int Multiply(int Param1,int Param2)
		{
			return(Channel.Multiply(Param1,Param2));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------