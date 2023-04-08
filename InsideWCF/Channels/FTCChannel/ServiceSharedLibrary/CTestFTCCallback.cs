using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.ServiceModel.Description;
using FTCSharedLibrary;
//-----------------------------------------------------------------------------
namespace ServiceSharedLibrary
{
//-----------------------------------------------------------------------------
	internal sealed class CTestFTCCallback : ITestFTCCallback
	{
//-----------------------------------------------------------------------------
		internal CTestFTCCallback()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		public void SomeCallbackOperation(string Input)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString() + " CALLBACK: " + Input);
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------