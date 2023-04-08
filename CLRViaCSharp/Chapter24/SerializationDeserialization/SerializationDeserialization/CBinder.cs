using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace SerializationDeserialization
{
//-------------------------------------------------------------------------------------------------------
	public class CBinder : SerializationBinder
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly string							ASSEMBLY_NAME="XXX";
		private static readonly string							TYPE_NAME="YYY";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override void BindToName(Type SerializedType, out string AssemblyName, out string TypeName)
		{
			if (SerializedType==typeof(CNameForBinder))
			{
				// !!! Zadam CUSTOM STRINGS ako ASSEMBLY NAME a TYPE NAME.
				AssemblyName=ASSEMBLY_NAME;
				TypeName=TYPE_NAME;

				Console.WriteLine(string.Format("Serialized as [{0},{1}] !",ASSEMBLY_NAME,TYPE_NAME));
			}
			else
			{
				base.BindToName(SerializedType,out AssemblyName,out TypeName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override Type BindToType(string AssemblyName, string TypeName)
		{
			// !!! Ocakavam CUSTOM STRINGS ako ASSEMBLY NAME a TYPE NAME.
			if (AssemblyName==ASSEMBLY_NAME && TypeName==TYPE_NAME)
			{
				Console.WriteLine(string.Format("Deserialized from [{0},{1}] !",ASSEMBLY_NAME,TYPE_NAME));

				return(typeof(CNameForBinder));
			}
			else
			{
				return(Type.GetType(string.Format("{0}, {1}",TypeName,AssemblyName)));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------