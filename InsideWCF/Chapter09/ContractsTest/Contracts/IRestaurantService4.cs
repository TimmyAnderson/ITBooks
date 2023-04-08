using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace Contracts
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(Namespace="http://contoso.com/Restaurant")]
	public interface IRestaurantService4
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int? RequestReservation(CRequestReservationParams ResParams, int? SomeNumber);
		[OperationContract]
		void ChangeReservation(CChangeReservationNewDateTime2 NewDateTime);
		[OperationContract(IsOneWay=true)]
		void CancelReservation(int? ReservationID);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------