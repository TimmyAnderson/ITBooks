using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Threading;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace TestLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(CallbackContract=typeof(ITestFTCCallback), SessionMode=SessionMode.Required)]
	public interface ITestFTCContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(IsInitiating=true)]
		string SomeOperation_BEGIN(string Input);
		[OperationContract]
		string SomeOperation_MIDDLE(string Input);
		[OperationContract(IsTerminating=true)]
		string SomeOperation_END(string Input);
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
        [FaultContract(typeof(InvalidOperationException))]
		void ThrowException(string Input);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------