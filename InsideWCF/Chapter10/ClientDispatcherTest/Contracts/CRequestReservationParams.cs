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
	[DataContract(Name="ReservationInformation", Namespace="http://contoso.com/Restaurant")]
	public sealed class CRequestReservationParams
	{
//-------------------------------------------------------------------------------------------------------
		[DataMember(Name="ResDateTime", IsRequired=true, EmitDefaultValue=true, Order=1)]
		private DateTime?										MResDateTime;
		[DataMember(Name="RestaurantName", IsRequired=true, EmitDefaultValue=false, Order=2)]
		private string											MRestuarantName;
		[DataMember(Name="PartyName", IsRequired=true, EmitDefaultValue=false, Order=3)]
		private string											MPartyName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CRequestReservationParams(DateTime? ResDateTime, string RestaurantName, string PartyName)
		{
			MPartyName=PartyName;
			MResDateTime=ResDateTime;
			MRestuarantName=RestaurantName;
		}
//-------------------------------------------------------------------------------------------------------
		public CRequestReservationParams(string RestaurantName, string PartyName)
		{
			MRestuarantName=RestaurantName;
			MPartyName=PartyName;
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
				return(MRestuarantName);
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