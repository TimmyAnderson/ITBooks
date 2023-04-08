using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.ServiceModel.Description;
//-----------------------------------------------------------------------------
namespace ServiceSharedLibrary
{
//-----------------------------------------------------------------------------
	interface ITestFTCCallback
	{
//-----------------------------------------------------------------------------
		[OperationContract]
		void SomeCallbackOperation(string Input);
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------