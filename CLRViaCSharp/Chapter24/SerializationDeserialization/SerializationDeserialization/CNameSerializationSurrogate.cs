using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace SerializationDeserialization
{
//-------------------------------------------------------------------------------------------------------
	// CLASS reprezentuje SERIALIZATION SURROGATE pre CLASS CName.
	public class CNameSerializationSurrogate : ISerializationSurrogate
	{
//-------------------------------------------------------------------------------------------------------
		public void GetObjectData(object Object, SerializationInfo Info, StreamingContext Context)
		{
			Console.WriteLine("CNameSerializationSurrogate.GetObjectData() CALLED !");

			CNonSerializableName												Name=(CNonSerializableName) Object;

			Info.AddValue("FirstName",Name.FirstName);
			Info.AddValue("LastName",Name.LastName);
			Info.AddValue("Age",Name.Age);
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Do 'Object' je mozne nastavit DESERIALIZOVANE FIELDS, alebo je mozne VYTOVRIT NOVY OBJEKT a ten vratit ako RETURN VALUE.
		public object SetObjectData(object Object, SerializationInfo Info, StreamingContext Context, ISurrogateSelector Selector)
		{
			Console.WriteLine("CNameSerializationSurrogate.SetObjectData() CALLED !");

			string												FirstName=Info.GetString("FirstName");
			string												LastName=Info.GetString("LastName");
			int													Age=Info.GetInt32("Age");
			CNonSerializableName												Name=new CNonSerializableName(FirstName,LastName,Age);

			return(Name);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------