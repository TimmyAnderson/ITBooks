using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceClient
{
//-------------------------------------------------------------------------------------------------------
	//[DataContract(Name="CServerPerson",Namespace="DCEquivalenceLibrary")]
	[DataContract(Namespace="DCEquivalenceLibrary")]
	public class CClientPerson
	{
//-------------------------------------------------------------------------------------------------------
		protected string										MFirstName;
		protected string										MLastName;
		protected int											MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CClientPerson(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember(Name="FirstName",Order=1)]
		public string											ClientFirstName
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
		[DataMember(Name="LastName",Order=2)]
		public string											ClientLastName
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
		// !!! Musim deklarovat aj Name aby to preslo, kedze na servri je [DataMemer] Age a tu ClientAge. Ak to nedam potom bude v Age 0.
		[DataMember(Name="Age",Order=3)]
		//[DataMember(Order=3)]
		public int												ClientAge
		{
			get
			{
				return(MAge);
			}
			internal set
			{
				MAge=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CClientPerson - FirstName: {0}, LastName: {1}, Age: {2} !",MFirstName, MLastName, MAge));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------