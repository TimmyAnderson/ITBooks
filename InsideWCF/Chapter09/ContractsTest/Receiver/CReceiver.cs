using System;
using System.Collections.Generic;
using System.Text;
using Contracts;
//-------------------------------------------------------------------------------------------------------
namespace Receiver
{
//-------------------------------------------------------------------------------------------------------
	class CReceiver : IRestaurantService3
	{
//-------------------------------------------------------------------------------------------------------
		public int? RequestReservation(CRequestReservationParams ResParams, int? SomeNumber)
		{
			Console.WriteLine("RequestReservation called !");

			Console.WriteLine("Reservation requested !");
			return(5);
		}
//-------------------------------------------------------------------------------------------------------
		public void ChangeReservation(CChangeReservationNewDateTime NewDateTime)
		{
			Console.WriteLine("ChangeReservation called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void CancelReservation(int? ReservationID)
		{
			Console.WriteLine("CancelReservation called !");

			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------