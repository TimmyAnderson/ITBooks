using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceClient
{
//-------------------------------------------------------------------------------------------------------
	// NEEKVIVALENTNY CONTRACT.
	// Trieda predstavuje ZLUCENIE DVOCH DATA CONTRACTS zo SERVICE: CServerErrorName a CServerErrorPerson.
	// !!! Kedze som NESTANOVIL SPRAVNY ORDER SERIALIZACIE MEMBERS (je iny ako v pripade SERVICE), tak sice pri prenose NEDOJDE k EXCEPTION, ale vysledkom bude OBJEKT so ZLE SERIALIZOVANYMI/DESERIALIZOVANYMI MEMBERS.
	// !!!!! Poradie serializacie CClientErrorPerson je: Age, FirstName, LastName - podla abecedy.
	// !!!!! Poradie deserializacie CServerErrorName a CServerErrorPerson na SERVICE je: FirstName, LastName, Age.
	// !!!!! Kedze poradnie NESEDI, tak SERIALIZACIA a DESERIALIZACIA NEBUDE SPRAVNE VYKONANA, aj ked sa NEVRATI EXCEPTION.
	[DataContract(Namespace="DCEquivalenceLibrary")]
	public class CClientErrorPerson
	{
//-------------------------------------------------------------------------------------------------------
		protected string										MFirstName;
		protected string										MLastName;
		protected int											MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CClientErrorPerson(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// NEDAM ORDER.
		[DataMember(Name="FirstName")]
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
		// NEDAM ORDER.
		[DataMember(Name="LastName")]
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
		// NEDAM ORDER.
		[DataMember(Name="Age")]
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
			return(string.Format("CClientErrorPerson - FirstName: {0}, LastName: {1}, Age: {2} !",MFirstName, MLastName, MAge));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------