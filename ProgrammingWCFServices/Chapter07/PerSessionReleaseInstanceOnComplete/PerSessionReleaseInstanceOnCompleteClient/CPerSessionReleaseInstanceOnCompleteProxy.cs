using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using PerSessionReleaseInstanceOnCompleteLibrary;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionReleaseInstanceOnCompleteClient
{
//-------------------------------------------------------------------------------------------------------
	public class CPerSessionReleaseInstanceOnCompleteProxy : ClientBase<IPerSessionReleaseInstanceOnCompleteContract>, IPerSessionReleaseInstanceOnCompleteContract
	{
//-------------------------------------------------------------------------------------------------------
		public CPerSessionReleaseInstanceOnCompleteProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintSessionID()
		{
			Channel.PrintSessionID();
		}
//-------------------------------------------------------------------------------------------------------
		public void NoTransaction(string Value)
		{
			Channel.NoTransaction(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void DoTransaction(string Value)
		{
			Channel.DoTransaction(Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------