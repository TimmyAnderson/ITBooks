using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace DCEventsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CName
	{
//-------------------------------------------------------------------------------------------------------
		private string				MFirstName;
		private string				MLastName;
		private string				MBase;
		private int					MAge;
		private int					MRetireAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CName()
		{
			MFirstName="NOT SERIALIZED";
			MLastName="NOT SERIALIZED";
			MBase="NOT SERIALIZED";
			MAge=-1;
			MRetireAge=-1;
		}
//-------------------------------------------------------------------------------------------------------
		public CName(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MBase="NOT DEFINED";
			MAge=Age;
			MRetireAge=-10;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string				FirstName
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
		public string				LastName
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
		// Nie je [DataMember].
		public string				Base
		{
			get
			{
				return(MBase);
			}
			internal set
			{
				MBase=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public int					Age
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
		// Nie je [DataMember].
		public int					RetireAge
		{
			get
			{
				return(MRetireAge);
			}
			internal set
			{
				MRetireAge=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("CName - FirstName: {0}, LastName: {1}, Base: {2}, Age: {3}, RetireAge: {4} !",MFirstName, MLastName,MBase,MAge,MRetireAge));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Meno metody moze byt lubovolne, ale prototyp musi sediet.
		[OnSerializing]
		public void OnSerializingMethod(StreamingContext SC)
		{
			Console.WriteLine("CName.OnSerializingMethod() called");
		}
//-------------------------------------------------------------------------------------------------------
		// Meno metody moze byt lubovolne, ale prototyp musi sediet.
		[OnSerialized]
		public void OnSerializedMethod(StreamingContext SC)
		{
			Console.WriteLine("CName.OnSerializedMethod() called");
		}
//-------------------------------------------------------------------------------------------------------
		// Meno metody moze byt lubovolne, ale prototyp musi sediet.
		[OnDeserializing]
		public void OnDeserializingMethod(StreamingContext SC)
		{
			Console.WriteLine("CName.OnDeserializingMethod() called");

			// Idealne miesto na inicializaciu NE [DataMember] premennych.
			MBase="1-B";
		}
//-------------------------------------------------------------------------------------------------------
		// Meno metody moze byt lubovolne, ale prototyp musi sediet.
		[OnDeserialized]
		public void OnDeserializedMethod(StreamingContext SC)
		{
			Console.WriteLine("CName.OnDeserializedMethod() called");

			// Idealne miesto na inicializaciu [DataMember] premennych na zaklade uz deserializovanych hodnot.
			MRetireAge=65-MAge;
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------