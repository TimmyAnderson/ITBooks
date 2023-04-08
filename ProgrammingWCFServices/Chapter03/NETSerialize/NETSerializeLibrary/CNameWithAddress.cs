using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace NETSerializeLibrary
{
//-------------------------------------------------------------------------------------------------------
	// Je serializovana .NET mechanizmom.
	[Serializable]
	public class CNameWithAddress
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private string											MAddress;
		private int												MAddressNumber;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameWithAddress()
		{
			MFirstName="NOT SERIALIZED";
			MLastName="NOT SERIALIZED";
			MAddress="NOT SERIALIZED";
			MAddressNumber=0;
		}
//-------------------------------------------------------------------------------------------------------
		public CNameWithAddress(string FirstName, string LastName, string Address, int AddressNumber, string City)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAddress=Address;
			MAddressNumber=AddressNumber;
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CNameWithAddress - FirstName: {0}, LastName: {1}, Address: {2}, AddressNumber: {3} !",MFirstName,MLastName,MAddress,MAddressNumber));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------