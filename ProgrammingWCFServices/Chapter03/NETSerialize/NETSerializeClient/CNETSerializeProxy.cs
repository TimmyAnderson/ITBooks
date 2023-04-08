using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using NETSerializeLibrary;
//-------------------------------------------------------------------------------------------------------
namespace NETSerializeClient
{
//-------------------------------------------------------------------------------------------------------
	class CNETSerializeProxy : ClientBase<INETSerializeContract>, INETSerializeContract
	{
		public CNETSerializeProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSimpleName GetSimpleName()
		{
 			return(Channel.GetSimpleName());
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintSimpleName(CSimpleName SimpleName)
		{
 			Channel.PrintSimpleName(SimpleName);
		}
//-------------------------------------------------------------------------------------------------------
		public CNameWithAddress GetNameWithAddress()
		{
 			return(Channel.GetNameWithAddress());
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintNameWithAddress(CNameWithAddress NameWithAddress)
		{
 			Channel.PrintNameWithAddress(NameWithAddress);
		}
//-------------------------------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------------------------------