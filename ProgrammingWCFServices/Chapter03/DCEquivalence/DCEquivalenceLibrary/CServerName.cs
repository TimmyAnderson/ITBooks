using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract(Namespace="DCEquivalenceLibrary")]
	[KnownType(typeof(CServerPerson))]
	public class CServerName
	{
//-------------------------------------------------------------------------------------------------------
		protected string										MFirstName;
		protected string										MLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CServerName(string FirstName, string LastName)
		{
			MFirstName=FirstName;
			MLastName=LastName;
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CServerName - FirstName: {0}, LastName: {1} !",MFirstName, MLastName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------