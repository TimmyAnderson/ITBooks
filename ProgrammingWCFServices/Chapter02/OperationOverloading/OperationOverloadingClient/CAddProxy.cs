using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using OperationOverloadingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace OperationOverloadingClient
{
//-------------------------------------------------------------------------------------------------------
	class CAddProxy : ClientBase<IAddContract>, IAddContract
	{
//-------------------------------------------------------------------------------------------------------
		public CAddProxy(Binding ProxyBinding, string EndpointAddress)
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
		public string Add(string Param1,string Param2)
		{
			return(Channel.Add(Param1,Param2));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------