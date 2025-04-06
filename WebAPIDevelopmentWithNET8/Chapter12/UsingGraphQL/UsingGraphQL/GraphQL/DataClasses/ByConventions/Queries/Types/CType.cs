using System;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingGraphQL
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CType
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly byte									MValueByte;
		private readonly short									MValueShort;
		private readonly int									MValueInt;
		private readonly long									MValueLong;
		private readonly decimal								MValueDecimal;
		private readonly double									MValueDouble;
		private readonly string									MValueString;
		private readonly DateTime								MValueDateTime;
		private readonly DateTimeOffset							MValueDateTimeOffset;
		private readonly TimeSpan								MValueTimeSpan;
		private readonly Uri									MValueUri;
		private readonly Guid									MValueGuid;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CType(byte ValueByte, short ValueShort, int ValueInt, long ValueLong, decimal ValueDecimal, double ValueDouble, string ValueString, DateTime ValueDateTime, DateTimeOffset ValueDateTimeOffset, TimeSpan ValueTimeSpan, Uri ValueUri, Guid ValueGuid)
		{
			MValueByte=ValueByte;
			MValueShort=ValueShort;
			MValueInt=ValueInt;
			MValueLong=ValueLong;
			MValueDecimal=ValueDecimal;
			MValueDouble=ValueDouble;
			MValueString=ValueString;
			MValueDateTime=ValueDateTime;
			MValueDateTimeOffset=ValueDateTimeOffset;
			MValueTimeSpan=ValueTimeSpan;
			MValueUri=ValueUri;
			MValueGuid=ValueGuid;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public byte												ValueByte
		{
			get
			{
				return(MValueByte);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public short											ValueShort
		{
			get
			{
				return(MValueShort);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												ValueInt
		{
			get
			{
				return(MValueInt);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public long												ValueLong
		{
			get
			{
				return(MValueLong);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public decimal											ValueDecimal
		{
			get
			{
				return(MValueDecimal);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public double											ValueDouble
		{
			get
			{
				return(MValueDouble);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											ValueString
		{
			get
			{
				return(MValueString);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DateTime											ValueDateTime
		{
			get
			{
				return(MValueDateTime);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public DateTimeOffset									ValueDateTimeOffset
		{
			get
			{
				return(MValueDateTimeOffset);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public TimeSpan											ValueTimeSpan
		{
			get
			{
				return(MValueTimeSpan);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public Uri												ValueUri
		{
			get
			{
				return(MValueUri);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public Guid												ValueGuid
		{
			get
			{
				return(MValueGuid);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------