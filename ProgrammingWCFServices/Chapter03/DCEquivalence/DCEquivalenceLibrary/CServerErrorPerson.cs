using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract(Namespace="DCEquivalenceLibrary",Name="CErrorPerson")]
	public class CServerErrorPerson : CServerErrorName
	{
//-------------------------------------------------------------------------------------------------------
		protected int											MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CServerErrorPerson(string FirstName, string LastName, int Age)
			: base(FirstName, LastName)
		{
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public int												Age
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
			return(string.Format("CServerErrorPerson - FirstName: {0}, LastName: {1}, Age: {2} !",MFirstName, MLastName, MAge));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------