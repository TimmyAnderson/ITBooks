using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DemarcatingOperationsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Required)]
	public interface IDemarcatingOperationsContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(IsInitiating=true,IsTerminating=false)]
		void Start1();
		[OperationContract(IsInitiating=true,IsTerminating=false)]
		void Start2();
		[OperationContract(IsInitiating=false,IsTerminating=false)]
		void Inside1();
		[OperationContract(IsInitiating=false,IsTerminating=false)]
		void Inside2();
		[OperationContract(IsInitiating=false,IsTerminating=false)]
		void Inside3();
		[OperationContract(IsInitiating=false,IsTerminating=true)]
		void Terminate1();
		[OperationContract(IsInitiating=false,IsTerminating=true)]
		void Terminate2();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------