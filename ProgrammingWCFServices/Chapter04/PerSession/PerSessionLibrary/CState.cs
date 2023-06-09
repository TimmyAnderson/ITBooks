using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CState
	{
//-------------------------------------------------------------------------------------------------------
		protected int											MID;
		protected string										MValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState(int ID, string Value)
		{
			MID=ID;
			MValue=Value;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public int												ID
		{
			get
			{
				return(MID);
			}
			internal set
			{
				MID=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											Value
		{
			get
			{
				return(MValue);
			}
			set
			{
				MValue=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("State - ID: {0}, Value: {1} !",MID, MValue));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------