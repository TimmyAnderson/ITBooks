using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCHierarchyLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CName
	{
//-------------------------------------------------------------------------------------------------------
		protected string										MFirstName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName)
		{
			MFirstName=FirstName;
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CName - FirstName: {0} !",MFirstName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------