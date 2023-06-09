using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace Descriptions
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public sealed class CRequestReservationParams
	{
//-------------------------------------------------------------------------------------------------------
		[DataMember(Name="ResDateTime")]
		private DateTime?										MResDateTime;
		[DataMember(Name="RestaurantName")]
		private string											MRestaurantName;
		[DataMember(Name="PartyName")]
		private string											MPartyName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CRequestReservationParams(DateTime? ResDateTime, string RestaurantName, string PartyName)
		{
			MPartyName=PartyName;
			MResDateTime=ResDateTime;
			MRestaurantName=RestaurantName;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public DateTime?										ResDateTime
		{
			get
			{
				return(MResDateTime);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											RestaurantName
		{
			get
			{
				return(MRestaurantName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											PartyName
		{
			get
			{
				return(MPartyName);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------