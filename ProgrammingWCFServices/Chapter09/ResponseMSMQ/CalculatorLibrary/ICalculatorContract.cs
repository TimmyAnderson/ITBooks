using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Messaging;
//-------------------------------------------------------------------------------------------------------
namespace CalculatorLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface ICalculatorContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract(IsOneWay=true)]
		void Add1(int Param1, int Param2);
        [OperationContract(IsOneWay=true)]
		void Add2(int Param1, int Param2);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------