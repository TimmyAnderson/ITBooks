using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace SerializationDeserialization
{
//-------------------------------------------------------------------------------------------------------
	[Serializable]
	public class CBaseNameISerializable : ISerializable
	{
//-------------------------------------------------------------------------------------------------------
		private string											MFirstName;
		private string											MLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// DESERIALIZACNY KONSTURKTOR.
		protected CBaseNameISerializable(SerializationInfo SI, StreamingContext SC)
		{
			Console.WriteLine("DESERIALIZATION CONSTRUCTOR - CBaseNameISerializable() CALLED, SC.State: [{0}], SC.Context: [{1}] !",SC.State,SC.Context);

			MFirstName=SI.GetString("FirstName");
			MLastName=SI.GetString("LastName");;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CBaseNameISerializable(string FirstName, string LastName)
		{
			MFirstName=FirstName;
			MLastName=LastName;
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// SERIALIZACNA METODA.
		public virtual void GetObjectData(SerializationInfo SI, StreamingContext SC)
		{
			Console.WriteLine("SERIALIZATION METHOD - CBaseNameISerializable.GetObjectData() CALLED, SC.State: [{0}], SC.Context: [{1}] !",SC.State,SC.Context);

			SI.AddValue("FirstName",MFirstName);
			SI.AddValue("LastName",MLastName);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("First name: [{0}], Last name: [{1}]",MFirstName,MLastName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------