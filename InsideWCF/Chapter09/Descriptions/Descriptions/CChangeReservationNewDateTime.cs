using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace Descriptions
{
//-------------------------------------------------------------------------------------------------------
	[MessageContract(WrapperName="CChangeReservationNewDateTime", WrapperNamespace="http://contoso.com/Restaurant")]
	public sealed class CChangeReservationNewDateTime
	{
//-------------------------------------------------------------------------------------------------------
		[MessageHeader(Name="ReservationID", MustUnderstand=true)]
		private int?											MReservationID;
		[MessageBodyMember(Name="NewDateTime")]
		private DateTime?										MNewDateTime;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationNewDateTime()
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationNewDateTime(Int32? ReservationID, DateTime? NewDateTime)
		{
			MNewDateTime=NewDateTime.Value;
			MReservationID=ReservationID;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public Int32?											ReservationID
		{
			get
			{
				return(MReservationID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public DateTime?										NewDateTime
		{
			get
			{
				return(MNewDateTime);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------