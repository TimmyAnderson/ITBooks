using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace SerializationDeserialization
{
//-------------------------------------------------------------------------------------------------------
	// CLASS robi DESERIALIZATION CSingleton CLASS.
	[Serializable]
	public class CSingletonSerializationHelper : IObjectReference
	{
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD robi DESERIALIZATION CSingleton CLASS.
        public object GetRealObject(StreamingContext Context)
		{
			Console.WriteLine("CSingletonSerializationHelper.GetRealObject() !");

			// !!! Kedze CLASS CSingleton je SINGLETON, vrati sa referencia na tento SINGLETON.
            return(CSingleton.GetSingleton());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------