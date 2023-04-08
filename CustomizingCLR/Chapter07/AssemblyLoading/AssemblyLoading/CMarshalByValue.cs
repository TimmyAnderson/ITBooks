using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//------------------------------------------------------------------------------------------------------
namespace AssemblyLoading
{
//------------------------------------------------------------------------------------------------------
	[Serializable]
	// !!!!! CLASS NEDEDI MarshalByRefObject a teda bude prenasana ako MARSHAL by VALUE.
	public sealed class CMarshalByValue : ISerializable
	{
//------------------------------------------------------------------------------------------------------
		public CMarshalByValue()
		{
			Console.WriteLine("CONSTRUCTOR - CMarshalByValue.CMarshalByValue() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
		public CMarshalByValue(SerializationInfo Info, StreamingContext Context)
		{
			Console.WriteLine("SERIALIZATION CONSTRUCTOR - CMarshalByValue.CMarshalByValue() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		public void GetObjectData(SerializationInfo Info, StreamingContext Context)
		{
			Console.WriteLine("CMarshalByValue.GetObjectData() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
		public void PrintAppDomain()
		{
			Console.WriteLine("CMarshalByValue.PrintAppDomain() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------
