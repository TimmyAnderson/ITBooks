using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CalculatorLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CalculatorClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCalculatorProxy: ClientBase<ICalculatorContract>, ICalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		public CCalculatorProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Add1(int Param1, int Param2)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.Add1(Param1,Param2);
		}
//-------------------------------------------------------------------------------------------------------
		public void Add2(int Param1, int Param2)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.Add2(Param1,Param2);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------