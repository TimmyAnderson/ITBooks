using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.Transactions;
using System.ServiceModel.Description;
using LCChannel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace ComplexTest
{
//-------------------------------------------------------------------------------------------------------
	internal sealed class CCallbackType : ICallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		internal CCallbackType()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeCallbackOperation(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString() + " CALLBACK: " + Input);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------