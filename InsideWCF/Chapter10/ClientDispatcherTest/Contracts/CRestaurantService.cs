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
	internal sealed class CRestaurantService : IRestaurantService2
	{
//-------------------------------------------------------------------------------------------------------
		public Int32? RequestReservation(CRequestReservationParams ResParams)
		{
			// Do the work to request reservation.
			// Return a reservation ID.
			return(5);
		}
//-------------------------------------------------------------------------------------------------------
		public void ChangeReservation(int? ReservationID, DateTime? ResDateTime)
		{
			// Try to change the reservation date and time from the ID.
			// Return true for changed, fault otherwise.
		}
//-------------------------------------------------------------------------------------------------------
		public void CancelReservation(int? ReservationID)
		{
			// Use the reservation ID to cancel that reservation.
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------