using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceChainProxyClient
{
//-------------------------------------------------------------------------------------------------------
	// !!! Dedenie z proxy.
	class CScientificCalculatorProxy : CSimpleCalculatorProxy, IScientificCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		public CScientificCalculatorProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, EndpointAddress)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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