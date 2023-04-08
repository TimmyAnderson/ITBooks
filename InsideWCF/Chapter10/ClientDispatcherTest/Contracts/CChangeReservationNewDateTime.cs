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
	[MessageContract(WrapperName="CChangeReservationNewDateTime", WrapperNamespace="http://contoso.com/Restaurant")]
	public sealed class CChangeReservationNewDateTime
	{
//-------------------------------------------------------------------------------------------------------
		[MessageHeader(Name="ReservationID", MustUnderstand=true)]
		private int?											MReservationID;
		[MessageBodyMember(Name="NewReservationDate")]
		private DateTime?										MNewDateTime;
		//[MessageBodyMember(Name="NewDateTime?")]
		//private DateTime?										MNewDateTime;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationNewDateTime()
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationNewDateTime(Int32? ReservationID, DateTime? NewDateTime)
		{
			MNewDateTime=NewDateTime;
			MReservationID=ReservationID;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int?												ReservationID
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