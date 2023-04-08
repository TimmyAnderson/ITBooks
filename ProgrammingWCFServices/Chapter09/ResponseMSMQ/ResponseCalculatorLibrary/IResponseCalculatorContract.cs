using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Messaging;
//-------------------------------------------------------------------------------------------------------
namespace ResponseCalculatorLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface IResponseCalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract(IsOneWay=true)]
		void OnAdd1Completed(int ReturnValue, ExceptionDetail Error);
        [OperationContract(IsOneWay=true)]
		void OnAdd2Completed(int ReturnValue, ExceptionDetail Error);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------