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
	[ServiceContract(CallbackContract=typeof(ITestFTCCallback), SessionMode=SessionMode.Required)]
	interface ITestFTCContract
	{
//-----------------------------------------------------------------------------
		[OperationContract(IsInitiating=true)]
		void SomeOperation_BEGIN(string Input);
		[OperationContract]
		void SomeOperation_MIDDLE(string Input);
		[OperationContract(IsTerminating=true)]
		void SomeOperation_END(string Input);
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------