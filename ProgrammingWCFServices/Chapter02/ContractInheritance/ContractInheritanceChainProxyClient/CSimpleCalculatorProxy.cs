using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ContractInheritanceChainProxyClient
{
//-------------------------------------------------------------------------------------------------------
	// !!! Pozor ClientBase<> musi mat ako paramter derived rozhranie.
	class CSimpleCalculatorProxy : ClientBase<IScientificCalculatorContract>, ISimpleCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleCalculatorProxy(Binding ProxyBinding, string EndpointAddress)
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
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------