using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace NETSerializeLibrary
{
	// Je serializovana .NET mechanizmom.
	[Serializable]
	public class CNameWithAddress
	{
//-------------------------------------------------------------------------------------------------------
		// Mena a typy premennych musia byt zhodne ako na strane servera tak aj klienta.
		// Na poradi nezalezi.
		private string											MFirstName;
		private string											MLastName;
		private string											MAddress;
		private int												MAddressNumber;
		// Nebude sa prenasat cez hranicu service.
		[NonSerialized]
		private string											MCity;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameWithAddress()
		{
			MFirstName="NOT SERIALIZED";
			MLastName="NOT SERIALIZED";
			MAddress="NOT SERIALIZED";
			MAddressNumber=0;
			MCity="NOT SERIALIZED";
		}
//-------------------------------------------------------------------------------------------------------
		public CNameWithAddress(string FirstName, string LastName, string Address, int AddressNumber, string City)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAddress=Address;
			MAddressNumber=AddressNumber;
			MCity=City;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											FirstName
		{
			get
			{
				return(MFirstName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											LastName
		{
			get
			{
				return(MLastName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											Address
		{
			get
			{
				return(MAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												AddressNumber
		{
			get
			{
				return(MAddressNumber);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											City
		{
			get
			{
				return(MCity);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CNameWithAddress - FirstName: {0}, LastName: {1}, Address: {2}, AddressNumber: {3}, City: {4} !",MFirstName,MLastName,MAddress,MAddressNumber,MCity));
		}
//-------------------------------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------------------------------