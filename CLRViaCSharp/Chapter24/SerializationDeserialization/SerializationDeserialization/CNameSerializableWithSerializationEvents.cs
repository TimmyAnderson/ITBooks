﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace SerializationDeserialization
{
//-------------------------------------------------------------------------------------------------------
	[Serializable]
	public class CNameSerializableWithSerializationEvents
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
		private int												MAge;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CNameSerializableWithSerializationEvents(string FirstName, string LastName, int Age)
		{
			MFirstName=FirstName;
			MLastName=LastName;
			MAge=Age;
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
		public int												Age
		{
			get
			{
				return(MAge);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OnSerializing]
		private void MyOnSerializing(StreamingContext SC)
		{
			Console.WriteLine(string.Format("MyOnSerializing() CALLED - [{0}] !",ToString()));
		}
//-------------------------------------------------------------------------------------------------------
		[OnSerialized]
		private void MyOnSerialized(StreamingContext SC)
		{
			Console.WriteLine(string.Format("MyOnSerialized() CALLED - [{0}] !",ToString()));
		}
//-------------------------------------------------------------------------------------------------------
		[OnDeserializing]
		private void MyOnDeserializing(StreamingContext SC)
		{
			Console.WriteLine(string.Format("MyOnDeserializing() CALLED - [{0}] !",ToString()));
		}
//-------------------------------------------------------------------------------------------------------
		[OnDeserialized]
		private void MyOnDeserialized(StreamingContext SC)
		{
			Console.WriteLine(string.Format("MyOnDeserialized() CALLED - [{0}] !",ToString()));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("First name: [{0}], Last name: [{1}], Age: [{2}]",MFirstName,MLastName,MAge));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------