using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ResponseCalculatorLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CalculatorLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CResponseCalculatorProxy : ClientBase<IResponseCalculatorContract>, IResponseCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
		public CResponseCalculatorProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void OnAdd1Completed(int ReturnValue, ExceptionDetail Error)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.OnAdd1Completed(ReturnValue, Error);
		}
//-------------------------------------------------------------------------------------------------------
		public void OnAdd2Completed(int ReturnValue, ExceptionDetail Error)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			Channel.OnAdd2Completed(ReturnValue, Error);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------