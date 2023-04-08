using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace Contracts
{
//-------------------------------------------------------------------------------------------------------
	public interface IRestaurantService2
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int? RequestReservation(CRequestReservationParams ResParams);
		[OperationContract]
		void ChangeReservation(int? ReservationID, DateTime? ResDateTime);
		[OperationContract(IsOneWay=true)]
		void CancelReservation(int? ReservationID);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------