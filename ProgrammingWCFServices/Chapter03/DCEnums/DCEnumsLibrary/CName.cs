using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCEnumsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CName
	{
//-------------------------------------------------------------------------------------------------------
		protected string										MFirstName;
		protected string										MLastName;
		protected ESex											MSex;
		protected ERace											MRace;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName, ESex Sex, ERace Race)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MSex=Sex;
			MRace=Race;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
			set
			{
				MFirstName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
			internal set
			{
				MLastName=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public ESex												Sex
		{
			get
			{
				return(MSex);
			}
			internal set
			{
				MSex=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public ERace											Race
		{
			get
			{
				return(MRace);
			}
			internal set
			{
				MRace=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CName - FirstName: {0}, LastName: {1}, Sex: {2}, Race: {3} !",MFirstName, MLastName, MSex, MRace));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------