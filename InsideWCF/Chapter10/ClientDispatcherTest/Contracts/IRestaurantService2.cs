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
	[ServiceContract()]
	public interface IRestaurantService2
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int? RequestReservation(CRequestReservationParams ResParams);
		[OperationContract]
		void ChangeReservation(int? ReservationID, DateTime? ResDateTime);
		[OperationContract(IsOneWay=true, Action="*")]
		void CancelReservation(int? ReservationId);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------