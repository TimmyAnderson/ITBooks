using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace Descriptions
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(Namespace="http://contoso.com/Restaurant")]
	interface IRestaurantService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int? RequestReservation(CRequestReservationParams ResParams, int? SomeNumber);
		[OperationContract]
		void ChangeReservation(CChangeReservationNewDateTime NewDateTime);
		[OperationContract(IsOneWay=true)]
		void CancelReservation(int? ReservationID);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------