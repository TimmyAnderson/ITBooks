using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DCGenericsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCGenericsManualClient
{
//-------------------------------------------------------------------------------------------------------
	public class CDCGenericsProxy<T> : ClientBase<IDCGenericsContract<T>>, IDCGenericsContract<T>
	{
//-------------------------------------------------------------------------------------------------------
		public CDCGenericsProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SendInt(CGenericClass1<int> Value)
		{
 			Channel.SendInt(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendGenerics(CGenericClass1<T> Value)
		{
 			Channel.SendGenerics(Value);
		}
//-------------------------------------------------------------------------------------------------------
		/*
		public void SendGenericsMethod<M>(CGenericClass1<M> Value)
		{
			Channel.SendGenericsMethod<M>(Value);
		}
		*/
//-------------------------------------------------------------------------------------------------------
		public void SendCName1(CGenericClass1<CName> Value)
		{
 			Channel.SendCName1(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCName2(CGenericClass2<CName> Value)
		{
 			Channel.SendCName2(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCName3(CGenericClass3<CName> Value)
		{
 			Channel.SendCName3(Value);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendCName4(CGenericClass4<CName> Value)
		{
 			Channel.SendCName4(Value);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------