using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace Contracts
{
//-------------------------------------------------------------------------------------------------------
	public interface IRestaurantService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int? RequestReservation(DateTime? ResDateTime, string RestaurantName, string PartyName);
		[OperationContract]
		bool ChangeReservation(Int32? ReservationID, DateTime? ResDateTime);
		[OperationContract(IsOneWay=true)]
		void CancelReservation(int? ReservationID);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------