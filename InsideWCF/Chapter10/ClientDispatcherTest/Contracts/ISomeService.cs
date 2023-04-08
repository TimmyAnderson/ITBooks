using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace Contracts
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface ISomeService
	{
//-------------------------------------------------------------------------------------------------------
		// BEGIN TYPED MESSAGES.
		[OperationContract]
		void SomeOperation(Message Input);
		[OperationContract]
		Message SomeOperation2(Message Input);
		[OperationContract]
		Message SomeOperation3(CChangeReservationNewDateTime Input);
		[OperationContract]
		void SomeOperation4(CChangeReservationNewDateTime Input);
		// END TYPED MESSAGES.
//-------------------------------------------------------------------------------------------------------
		// BEGIN UNTYPED MESSAGES.
		[OperationContract]
		void SomeOperation5(int? Input);
		[OperationContract]
		int? SomeOperation6(int? Input, string OtherInput);
		[OperationContract]
		int? SomeOperation7(CRequestReservationParams Input);
		[OperationContract]
		int? SomeOperation8(CRequestReservationParams Input, int? Input2);
		// END UNTYPED MESSAGES.
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------