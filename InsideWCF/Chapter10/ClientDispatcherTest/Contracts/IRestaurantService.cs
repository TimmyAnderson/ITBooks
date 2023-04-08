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
	public interface IRestaurantService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		int? RequestReservation(DateTime? ResDateTime, string RestaurantName, string PartyName);
		[OperationContract]
		bool ChangeReservation(int? ReservationID, DateTime? ResDateTime);
		[OperationContract(IsOneWay=true)]
		void CancelReservation(int? ReservationID);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------