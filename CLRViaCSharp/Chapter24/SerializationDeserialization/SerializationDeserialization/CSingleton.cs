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
	public sealed class CSingleton : ISerializable
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly CSingleton						MTheOneObject=new CSingleton();
//-------------------------------------------------------------------------------------------------------
		public string											MName="Jeff";
		public DateTime											MDate=DateTime.Now;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! DESERIALIZATION CONSTRUCTOR NIE JE IMPLEMENTOVANY, pretoze DESERIALIZATION sa robi 
		private CSingleton()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		void ISerializable.GetObjectData(SerializationInfo Info, StreamingContext Context)
		{
			Console.WriteLine("CSingleton.GetObjectData() !");

			// !!!!! Kedze OBJECT CSingleton je SINGLETON a SERIALIZATION sa robi v ramci PROCESS, tak do STREAMU NETREBA ukladat ZIADNE DATA.

			// !!!!! Do STREAM sa zapise ako SERIALIZED TYPE CSingletonSerializationHelper, namiesto CSingleton.
			Info.SetType(typeof(CSingletonSerializationHelper));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static CSingleton GetSingleton()
		{
			return(MTheOneObject);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------